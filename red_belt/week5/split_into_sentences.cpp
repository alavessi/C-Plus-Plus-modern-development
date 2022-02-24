#include "test_runner.h"

#include <vector>

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = std::vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens)
{ 
  // Напишите реализацию функции, не копируя объекты типа Token
  std::vector<Sentence<Token>> sentences;
  Sentence<Token> sentence;
  bool is_prev_end = false;
  for (auto it = tokens.begin(); it != tokens.end(); it++)
  {
    bool is_cur_end = it->IsEndSentencePunctuation();
    if (is_prev_end && !is_cur_end)
    {
      sentences.push_back(std::move(sentence));
    }
    sentence.push_back(std::move(*it));
    is_prev_end = is_cur_end;
  }
  if (!sentence.empty())
  {
    sentences.push_back(std::move(sentence));
  }
  return sentences;
}


struct TestToken
{
  std::string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const
  {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const
  {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

std::ostream& operator<<(std::ostream& stream, const TestToken& token)
{
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting()
{
  ASSERT_EQUAL(
    SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    std::vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    std::vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    std::vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}

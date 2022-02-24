#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <algorithm>

std::vector<std::string> SplitIntoWordsView(const std::string& str)
{
  std::vector<std::string> result;
  auto it = str.begin();
  while (true)
  {
    auto space = find(it, str.end(), ' ');
    result.push_back(std::string(it, space));
    if (space == str.end())
    {
      break;
    }
    else
    {
      it = space + 1;
    }
  }
  return result;
}

struct Stats
{
  std::map<std::string, int> word_frequences;

  void operator += (const Stats& other)
  {
    for (const auto& [word, frequence] : other.word_frequences)
    {
      word_frequences[word] += frequence;
    }
  }
};

Stats ExploreKeyWords(const std::set<std::string>& key_words, std::istream& input)
{
  // Implement this function
  Stats stats;
  for (std::string line; getline(input, line); )
  {
    auto words = SplitIntoWordsView(line);
    for (auto word : words)
    {
      if (key_words.find(word) != key_words.end())
      {
        stats.word_frequences[word]++;
      }
    }
  }
  return stats;
}

void TestBasic()
{
  const std::set<std::string> key_words = {"yangle", "rocks", "sucks", "all"};

  std::stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const std::map<std::string, int> expected = {{"yangle", 6}, {"rocks", 2}, {"sucks", 1}};
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}

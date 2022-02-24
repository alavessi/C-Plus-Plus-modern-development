#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s)
{
  os << "{";
  bool first = true;
  for (const auto& x : s)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s)
{
  os << "{";
  bool first = true;
  for (const auto& x : s)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m)
{
  os << "{";
  bool first = true;
  for (const auto& kv : m)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {})
{
  if (t != u)
  {
    std::ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty())
    {
      os << " hint: " << hint;
    }
    throw std::runtime_error(os.str());
  }
}

inline void Assert(bool b, const std::string& hint)
{
  AssertEqual(b, true, hint);
}

class TestRunner
{
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const std::string& test_name)
  {
    try
    {
      func();
      std::cerr << test_name << " OK" << std::endl;
    }
    catch (std::exception& e)
    {
      ++fail_count;
      std::cerr << test_name << " fail: " << e.what() << std::endl;
    }
    catch (...)
    {
      ++fail_count;
      std::cerr << "Unknown exception caught" << std::endl;
    }
  }

  ~TestRunner()
  {
    if (fail_count > 0)
    {
      std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const std::string& str)
{
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  int n = str.size();
  for (int i = 0; i <= n/2 ; i++)
  {
    if (str[i] != str[n-1-i])
    {
      return false;
    }
  }
  return true;
}

void TestSomething() // функция, что-то тестирующая
{
  AssertEqual (IsPalindrom("madam"), true,  "madam is palindrom)");
  AssertEqual (IsPalindrom("level"), true,  "level is palindrom)");
  AssertEqual (IsPalindrom("wasitacaroracatisaw"), true,  "wasitacaroracatisaw is palindrom)");
  AssertEqual (IsPalindrom("okko"), true,  "okko is palindrom)");
  AssertEqual (IsPalindrom("aa"), true,  "aa is palindrom)");
  AssertEqual (IsPalindrom("a"), true,  "a is palindrom)");
  AssertEqual (IsPalindrom(""), true,  "empty string is palindrom)");
  AssertEqual (IsPalindrom("makskam"), true,  "makskam is palindrom)");
  AssertEqual (IsPalindrom("aba"), true,  "aba is palindrom)");
  AssertEqual (IsPalindrom("ab"), false,  "ab is not palindrom)");
  AssertEqual (IsPalindrom("abcdecba"), false,  "abcdecba is not palindrom)");
  AssertEqual (IsPalindrom("abc ddcba"), false,  "abc ddcba is not palindrom)");
  AssertEqual (IsPalindrom("abcddcbb"), false,  "abcddcbb is not palindrom)");
  AssertEqual (IsPalindrom("ab cdd cba"), false,  "ab cdd cba is not palindrom)");
  AssertEqual (IsPalindrom("abca"), false,  "abca is not palindrom)");
  // выполняем какие-то проверки с помощью AssertEqual
}

int main()
{
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestSomething, "tests");
  return 0;
}

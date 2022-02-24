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

int gcd(int a, int b)
{
    if (b==0)
      return a;
    return gcd(b,a%b);
}

class Rational
{
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

  Rational()
  {
    numerator=0;
    denominator=1;
  }

  Rational(int new_numerator, int new_denominator)
  {
    if (new_numerator==0)
    {
      numerator=0;
      denominator=1;
    }
    else
    {
      int GCD = gcd(abs(new_numerator), abs(new_denominator));
      numerator = ((new_numerator * new_denominator > 0) ? 1 : -1) * abs(new_numerator) / GCD;
      denominator = abs(new_denominator) / GCD;
    }
  }

  int Numerator() const
  {
    return numerator;
  }

  int Denominator() const
  {
    return denominator;
  }

public:
  long numerator, denominator;
};

void TestSomething() // функция, что-то тестирующая
{
  Rational r;
  AssertEqual (r.Numerator(), 0,  "default fraction is 0/1");
  AssertEqual (r.Denominator(), 1,  "default fraction is 0/1");

  Rational r1(12,4);
  AssertEqual (r1.Numerator(), 3,  "AssertEqual(12/4 == 3/1)");
  AssertEqual (r1.Denominator(), 1,  "AssertEqual(12/4 == 3/1)");

  Rational r2(4, -6);
  AssertEqual (r2.Numerator(), -2,  "AssertEqual(4/(-6) == (-2)/3)");
  AssertEqual (r2.Denominator(), 3,  "AssertEqual((4/(-6) == (-2)/3)");

  Rational r3(-15, -25);
  AssertEqual (r3.Numerator(), 3,  "AssertEqual((-15)/(-25) == 3/5)");
  AssertEqual (r3.Denominator(), 5,  "AssertEqual((-15)/(-25) == 3/5)");

  Rational r4(0,7);
  AssertEqual (r4.Numerator(), 0,  "0/7 == 0/1");
  AssertEqual (r4.Denominator(), 1,  "0/7 == 0/1");

  // выполняем какие-то проверки с помощью AssertEqual
}

int main()
{
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestSomething, "tests");
  return 0;
}

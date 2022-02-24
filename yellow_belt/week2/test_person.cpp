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

void TestSomething() // функция, что-то тестирующая
{
  Person person;
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  AssertEqual (person.GetFullName(1900), "Incognito");
  AssertEqual (person.GetFullName(1965), "Polina with unknown last name");
  AssertEqual (person.GetFullName(1990), "Polina Sergeeva");
  person.ChangeFirstName(1970, "Appolinaria");
  AssertEqual (person.GetFullName(1969), "Polina Sergeeva");
  AssertEqual (person.GetFullName(1970), "Appolinaria Sergeeva");
  person.ChangeLastName(1968, "Volkova");
  AssertEqual (person.GetFullName(1969), "Polina Volkova");
  AssertEqual (person.GetFullName(1970), "Appolinaria Volkova");
  // выполняем какие-то проверки с помощью AssertEqual
  Person personn;
  personn.ChangeLastName(1965, "Sergeeva");
  personn.ChangeFirstName(1967, "Polina");
  AssertEqual(personn.GetFullName(1964), "Incognito");
  AssertEqual(personn.GetFullName(1966), "Sergeeva with unknown first name");
  AssertEqual(personn.GetFullName(1968), "Polina Sergeeva");

  Person person1;

  person1.ChangeFirstName(1965, "Polina");
  person1.ChangeLastName(1967, "Sergeeva");

  AssertEqual(person1.GetFullName(1964), "Incognito");
  AssertEqual(person1.GetFullName(1966), "Polina with unknown last name");
  AssertEqual(person1.GetFullName(1968), "Polina Sergeeva");

  person1.ChangeFirstName(1969, "Appolinaria");
  AssertEqual(person1.GetFullName(1968), "Polina Sergeeva");
  AssertEqual(person1.GetFullName(1969), "Appolinaria Sergeeva");
  AssertEqual(person1.GetFullName(1970), "Appolinaria Sergeeva");

  person1.ChangeLastName(1968, "Volkova");
  AssertEqual(person1.GetFullName(1967), "Polina Sergeeva");
  AssertEqual(person1.GetFullName(1968), "Polina Volkova");
  AssertEqual(person1.GetFullName(1969), "Appolinaria Volkova");

}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(TestSomething, "tests");
  return 0;
}

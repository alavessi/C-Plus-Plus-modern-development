#include <iostream>
#include <string>
#include <map>

std::string GetName(const std::map<int, std::string>& names, int year)
{
  auto it = names.upper_bound(year);
  if (it == names.begin())
  {
    return "";
  }
  return std::prev(it)->second;
}

class Person
{
public:
  void ChangeFirstName(int year, const std::string& first_name)
  {
    // добавить факт изменения имени на first_name в год year
    names[year] = first_name;
  }
  void ChangeLastName(int year, const std::string& last_name)
  {
    // добавить факт изменения фамилии на last_name в год year
    surnames[year] = last_name;
  }
  std::string GetFullName(int year)
  {
    // получить имя и фамилию по состоянию на конец года year
    // с помощью двоичного поиска
    std::string first_name = GetName(names, year), last_name = GetName(surnames, year);
    if (first_name.empty() && last_name.empty())
    {
      return "Incognito";
    }
    else if (first_name.empty())
    {
      return last_name + " with unknown first name";
    }
    else if (last_name.empty())
    {
      return first_name + " with unknown last name";
    }
    else
    {
      return first_name + " " + last_name;
    }
  }
private:
  // приватные поля
  std::map<int, std::string> names, surnames;
};

int main()
{
    Person person;
  
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
      std::cout << person.GetFullName(year) << std::endl;
    }
  
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
      std::cout << person.GetFullName(year) << std::endl;
    }
  
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
      std::cout << person.GetFullName(year) << std::endl;
    }
  
    return 0;
}
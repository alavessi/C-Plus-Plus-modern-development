#include <iostream>
#include <algorithm>
#include <vector>

enum class Gender
{
  FEMALE,
  MALE
};

struct Person
{
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end)
{
    if (range_begin == range_end)
    {
        return 0;
    }
    std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(begin(range_copy), middle, end(range_copy), [](const Person& lhs, const Person& rhs) {return lhs.age < rhs.age;});
    return middle->age;
}

void PrintStats(std::vector<Person> persons)
{
    std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << std::endl;

    auto it = std::partition(persons.begin(), persons.end(), [](Person person) {return person.gender == Gender::FEMALE;});
    std::cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << std::endl;
    std::cout << "Median age for males = " << ComputeMedianAge(it, persons.end()) << std::endl;

    auto it1 = std::partition(persons.begin(), it, [](Person person) {return person.is_employed == true;});
    std::cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it1) << std::endl;
    std::cout << "Median age for unemployed females = " << ComputeMedianAge(it1, it) << std::endl;

    auto it2 = std::partition(it, persons.end(), [](Person person) {return person.is_employed == true;});
    std::cout << "Median age for employed males = " << ComputeMedianAge(it, it2) << std::endl;
    std::cout << "Median age for unemployed males = " << ComputeMedianAge(it2, persons.end()) << std::endl;
}

int main()
{
    std::vector<Person> persons =
    {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
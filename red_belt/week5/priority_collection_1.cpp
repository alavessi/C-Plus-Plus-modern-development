#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

template <typename T>
class PriorityCollection
{
public:
  using Id = int; /* тип, используемый для идентификаторов */

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object)
  {
    Id id = data.size();
    existings.insert(id);
    priorities.insert({0, id});
    data.push_back({std::move(object), 0});
    return id;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
  {
    for (auto it = range_begin; it != range_end; it++, ids_begin++)
    {
      *ids_begin = Add(std::move(*it));
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const
  {
    return existings.find(id) != existings.end();
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const
  {
    return data[id].first;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id)
  {
    int& priority = data[id].second;
    priorities.erase({priority, id});
    priorities.insert({++priority, id});
  }

  // Получить объект с максимальным приоритетом и его приоритет
  std::pair<const T&, int> GetMax() const
  {
    return data[std::prev(priorities.end())->second];
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  std::pair<T, int> PopMax()
  {
    auto it = std::prev(priorities.end());
    int id = it->second;    
    existings.erase(it->second);
    priorities.erase(it);
    return std::move(data[id]);
  }

private:
  // Приватные поля и методы
  std::set<std::pair<int, Id>> priorities;
  std::set<Id> existings;
  std::vector<std::pair<T, int>> data;
};


class StringNonCopyable : public std::string
{
public:
  using std::string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy()
{
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i)
  {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}

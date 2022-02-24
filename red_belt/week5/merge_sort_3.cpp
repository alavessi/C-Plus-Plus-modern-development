#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
  // Напишите реализацию функции,
  // не копируя сортируемые элементы
  if (range_end - range_begin > 1)
  {
    std::vector<typename RandomIt::value_type> elements(std::make_move_iterator(range_begin), std::make_move_iterator(range_end));
    auto it1 = elements.begin() + (elements.end() - elements.begin()) / 3;
    auto it2 = it1 + (elements.end() - elements.begin()) / 3;
    MergeSort(elements.begin(), it1);
    MergeSort(it1, it2);
    MergeSort(it2, elements.end());
    std::vector<typename RandomIt::value_type> reserve;
    std::merge(std::make_move_iterator(elements.begin()), std::make_move_iterator(it1), std::make_move_iterator(it1), std::make_move_iterator(it2), std::back_inserter(reserve));
    std::merge(std::make_move_iterator(reserve.begin()), std::make_move_iterator(reserve.end()), std::make_move_iterator(it2), std::make_move_iterator(elements.end()), range_begin);
  }
}

void TestIntVector()
{
  std::vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(std::is_sorted(begin(numbers), end(numbers)));
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}

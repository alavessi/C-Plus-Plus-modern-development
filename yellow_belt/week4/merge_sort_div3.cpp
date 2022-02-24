#include <iostream>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_end - range_begin > 1)
    {
        std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
        auto it1 = elements.begin() + (elements.end() - elements.begin()) / 3;
        auto it2 = it1 + (elements.end() - elements.begin()) / 3;
        MergeSort(elements.begin(), it1);
        MergeSort(it1, it2);
        MergeSort(it2, elements.end());
        std::vector<typename RandomIt::value_type> reserve;
        std::merge(elements.begin(), it1, it1, it2, std::back_inserter(reserve));
        std::merge(reserve.begin(), reserve.end(), it2, elements.end(), range_begin);
    }
}

int main()
{
    std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
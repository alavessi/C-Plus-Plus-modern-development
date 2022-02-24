#include <iostream>
#include <vector>
#include <algorithm>

void PrintVectorPart(const std::vector<int>& numbers)
{
    auto it = std::find_if(numbers.begin(), numbers.end(), [] (int a) {return a < 0;});
    while (it != numbers.begin())
    {
        it--;
        std::cout << *it << " ";
    }    
}

int main()
{
  PrintVectorPart({6, 1, 8, -5, 4});
  std::cout << std::endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  std::cout << std::endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  std::cout << std::endl;
  return 0;
}
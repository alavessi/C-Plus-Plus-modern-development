#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string& s)
{
    std::vector<std::string> result;
    auto beg = s.begin(), it = find(beg, s.end(), ' ');
    while ((it = find(beg, s.end(), ' ')) != s.end())
    {
        result.push_back({beg, it});
        beg = ++it;
    }
    result.push_back({beg, s.end()});
    return result;
}

int main()
{
  std::string s = "C Cpp Java Python";
  std::vector<std::string> words = SplitIntoWords(s);
  std::cout << words.size() << std::endl;
  for (auto it = begin(words); it != end(words); ++it)
  {
    if (it != begin(words))
    {
      std::cout << "/";
    }
    std::cout << *it;
  }
  return 0;
}
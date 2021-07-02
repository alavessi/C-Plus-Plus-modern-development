#include <iostream>
#include <utility>
#include <map>

int main ()
{
    std::pair p(7, "C++"); // в новом стандарте можно и без <int, string>
    // auto p = std::make_pair(7, "C++"); // второй вариант
    std::cout << p.first << " " << p.second << std::endl;

    std::map<int, std::string > digits = {{1, "one"}};
    for (const auto& [key , value] : digits)
    {
        std::cout << key << " " << value << std::endl;
    }
    return 0;
}

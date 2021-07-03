#include <iostream>
#include <map>
#include <vector>
#include <utility>

template <typename T> T Sqr(const T& x);
template <typename First , typename Second> std::pair <First, Second> Sqr(const std::pair <First, Second>& p);
template <typename T> std::vector<T> Sqr(const std::vector <T>& v);
template <typename Key, typename Value> std::map<Key, Value> Sqr(const std::map<Key, Value>& m);

template <typename T>
T Sqr(const T& x)
{
    return x*x;
}

template <typename First, typename Second>
std::pair <First, Second> Sqr(const std::pair <First, Second>& p)
{
    return {Sqr(p.first), Sqr(p.second)};
}

template <typename T>
std::vector<T> Sqr(const std::vector <T>& v)
{
    std::vector<T> res;
    for (const auto& elem: v)
    {
        res.push_back(Sqr(elem));
    }
    return res;
}

template <typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value>& m)
{
    std::map<Key, Value> res;
    for (const auto& [key, value]: m)
    {
        res[key]=Sqr(value);
    }
    return res;
}

int main() // Пример вызова функции
{
    std::vector<int> v = {1, 2, 3};
    std::cout << "vector:";
    for (int x : Sqr(v))
    {
        std::cout << ' ' << x;
    }
    std::cout << std::endl;

    std::map<int, std::pair<int, int>> map_of_pairs = { {4, {2, 2}}, {7, {4, 3}} };
    std::cout << "map of pairs:" << std::endl;
    for (const auto& x : Sqr(map_of_pairs))
    {
        std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
    }

    return 0;
}

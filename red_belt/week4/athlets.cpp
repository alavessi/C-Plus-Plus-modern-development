#include <iostream>
#include <vector>
#include <list>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const size_t MAX_NUMBER = 100000;
    std::list<int> row;
    std::vector<std::list<int>::iterator> iters(MAX_NUMBER + 1, row.end());
    size_t N;
    std::cin >> N;
    for (size_t i = 0; i < N; i++)
    {
        int current, next;
        std::cin >> current >> next;
        iters[current] = row.insert(iters[next], current);
    }
    for (int athlet: row)
    {
        std::cout << athlet << '\n';
    }
    return 0;
}

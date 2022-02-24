#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = n - i;
    }
    do
    {
        for (int a: v)
        {
            std::cout << a << " ";
        }
        std::cout << std:: endl;
    }
    while(std::prev_permutation(v.begin(), v.end()));
    return 0;
}
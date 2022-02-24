#include "profile.h"

#include <iostream>
#include <vector>

int main()
{
    size_t size;
    std::cin >> size;
    {
        LOG_DURATION("fill");
        std::vector<std::pair<size_t,size_t>> v(size);
        std::fill(v.begin(), v.end(), std::make_pair(0,0));
    }
    {
        LOG_DURATION("assign");
        std::vector<std::pair<size_t,size_t>> v(size);
        v.assign(size, {0,0});
        
    }
    {
        LOG_DURATION("v(size)");
        std::vector<std::pair<size_t,size_t>> v;
        v.assign(size, {0,0});
    }
    return 0;
}
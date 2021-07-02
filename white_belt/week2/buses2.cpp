#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::map <std::vector<std::string>,int> routes;
    int k=0,Q;
    std::cin>>Q;
    for (int i=0; i<Q; i++)
    {
        int n;
        std::cin>>n;
        std::vector<std::string> stops(n);
        for (int j=0; j<n; j++)
            std::cin>>stops[j];
        if (routes.count(stops)==0)
        {
            routes[stops]=++k;
            std::cout<<"New bus "<<k<<std::endl;
        }
        else
            std::cout<<"Already exists for "<<routes[stops]<<std::endl;
    }
    return 0;
}

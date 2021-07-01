#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

int main()
{
    std::map <std::set<std::string>,int> routes;
    int k=0,Q;
    std::cin>>Q;
    for (int i=0; i<Q; i++)
    {
        int n;
        std::cin>>n;
        std::set<std::string> stops;
        for (int j=0; j<n; j++)
        {
            std::string s;
            std::cin>>s;
            stops.insert(s);
        }
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

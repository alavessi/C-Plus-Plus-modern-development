#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> buses;
    std::map<std::string, std::vector<std::string> > routes;
    int Q;
    std::cin>>Q;
    for (int i=0; i<Q; i++)
    {
        std::string query;
        std::cin>>query;
        if (query=="NEW_BUS")
        {
            std::string bus;
            int stop_count;
            std::cin>>bus>>stop_count;
            std::vector<std::string> st(stop_count);
            buses.push_back(bus);
            for (int j=0; j<stop_count; j++)
                std::cin>>st[j];
            routes[bus]=st;
        }
        if (query=="BUSES_FOR_STOP")
        {
            std::string stop;
            std::cin>>stop;
            bool no_stop=true;
            for (auto b: buses)
                if (count(routes[b].begin(),routes[b].end(),stop)!=0)
                {
                    std::cout<<b<<" ";
                    no_stop=false;
                }
            if (no_stop)
                std::cout<<"No stop";
            std::cout<<std::endl;
        }
        if (query=="STOPS_FOR_BUS")
        {
            std::string bus;
            std::cin>>bus;
            if (routes.count(bus)==0)
                std::cout<<"No bus\n";
            else
            {
                for (auto st: routes[bus])
                {
                    std::cout<<"Stop "<<st<<": ";
                    bool interchange=false;
                    for (auto b:buses)
                        if (b!=bus && count(routes[b].begin(),routes[b].end(),st))
                        {
                            interchange=true;
                            std::cout<<b<<" ";
                        }
                    if (!interchange)
                        std::cout<<"no interchange";
                    std::cout<<std::endl;
                }
            }
        }
        if (query=="ALL_BUSES")
        {
            if (routes.size()==0)
                std::cout<<"No buses\n";
            else
            {
                for (const auto& route: routes)
                {
                    std::cout<<"Bus "<<route.first<<": ";
                    for (const auto& stop: route.second)
                        std::cout<<stop<<" ";
                    std::cout<<std::endl;
                }
            }
        }
    }
    return 0;
}

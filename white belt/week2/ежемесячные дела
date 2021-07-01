#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<std::vector<std::string> > monthly_cases(31);
    std::vector<int> days_in_month={31,28,31,30,31,30,31,31,30,31,30,31};
    int Q,month=0;
    std::cin>>Q;
    for (int i=0; i<Q; i++)
    {
        std::string command;
        std::cin>>command;
        if (command=="ADD")
        {
            int j;
            std::string s;
            std::cin>>j>>s;
            monthly_cases[j-1].push_back(s);
        }
        if (command=="DUMP")
        {
            int j;
            std::cin>>j;
            std::cout<<monthly_cases[j-1].size();
            for (std::string x: monthly_cases[j-1])
                std::cout<<" "<<x;
            std::cout<<std::endl;
        }
        if (command=="NEXT")
        {
            int next_month=(month+1)%12;
            for (int day=days_in_month[next_month]; day<days_in_month[month]; day++)
            {
                for (auto x: monthly_cases[day])
                    monthly_cases[days_in_month[next_month]-1].push_back(x);
                monthly_cases[day].clear();
            }
            month=next_month;
        }
    }
    return 0;
}

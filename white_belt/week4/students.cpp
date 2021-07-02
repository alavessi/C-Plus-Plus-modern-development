#include <iostream>
#include <vector>

struct Student
{
    std::string name,surname;
    int day,month,year;
};
int main()
{
    std::vector<Student> students;
    int n=0,m=0;
    std::cin>>n;
    for (int i=0; i<n; i++)
    {
        std::string name,surname;
        int day,month,year;
        std::cin>>name>>surname>>day>>month>>year;
        students.push_back({name,surname,day,month,year});
    }
    std::cin>>m;
    for (int i=0; i<m; i++)
    {
        std::string query;
        int k;
        std::cin>>query>>k;
        if (query=="name" && k>=1 && k<=n)
            std::cout<<students[k-1].name<<" "<<students[k-1].surname<<"\n";
        else if (query=="date" && k>=1 && k<=n)
            std::cout<<students[k-1].day<<"."<<students[k-1].month<<"."<<students[k-1].year<<"\n";
        else
            std::cout<<"bad request\n";
    }
    return 0;
}

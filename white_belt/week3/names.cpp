#include <algorithm>
#include <vector>
#include <map>
#include <string>

class Person
{
public:
    Person(const std::string& first_name, const std::string& last_name, const int& year)
    {
        names_in_year[year]=first_name;
        if (count(names.begin(),names.end(),year)==0)
        {
            names.push_back(year);
            std::sort(names.begin(),names.end());
        }
        surnames_in_year[year]=last_name;
        if (count(surnames.begin(),surnames.end(),year)==0)
        {
            surnames.push_back(year);
            std::sort(surnames.begin(),surnames.end());
        }
        born=year;
    }
    void ChangeFirstName(const int& year, const std::string& first_name)
    {
        if (year>=born)
        {
            names_in_year[year]=first_name;
            if (count(names.begin(),names.end(),year)==0)
            {
                names.push_back(year);
                std::sort(names.begin(),names.end());
            }
        }
    }
    void ChangeLastName(const int& year, const std::string& last_name)
    {
        if (year>=born)
        {
            surnames_in_year[year]=last_name;
            if (count(surnames.begin(),surnames.end(),year)==0)
            {
                surnames.push_back(year);
                std::sort(surnames.begin(),surnames.end());
            }
        }
    }
    std::string Getname(const int& year, bool& is_name, const std::vector<int>& names, std::map<int,std::string> names_in_year) const
    {
        std::string name="";
        if (is_name)
        {
            if (year<names[0])
                is_name=false;
            else
            {
                unsigned int i=0;
                while (i<names.size() && names[i]<=year)
                    i++;
                name=names_in_year[names[i-1]];
            }
        }
        return name;
    }
    std::string GetFullName(int year) const
    {
        if (year<born)
            return "No person";
        bool is_name=!names.empty(),is_surname=!surnames.empty();
        std::string first_name=Getname(year, is_name, names, names_in_year);
        std::string last_name=Getname(year, is_surname, surnames, surnames_in_year);
        if (!(is_name || is_surname))
            return "Incognito";
        if (!is_name)
            return last_name+" with unknown first name";
        if (!is_surname)
            return first_name+" with unknown last name";
        return first_name+" "+last_name;
    }
    std::string GetnameWithHistory(const int& year, bool& is_name, const std::vector<int>& names, std::map<int,std::string> names_in_year) const
    {
        std::vector<std::string> Vnames;
        if (is_name)
        {
            if (year<names[0])
                is_name=false;
            else
            {
                unsigned int i=0;
                while (i<names.size() && names[i]<=year)
                    i++;
                std::string curname="";
                for (int j=i-1; j>=0; j--)
                    if (names_in_year[names[j]]!=curname)
                    {
                        Vnames.push_back(names_in_year[names[j]]);
                        curname=names_in_year[names[j]];
                    }
            }
        }
        std::string name="";
        if (is_name)
        {
            name=Vnames[0];
            for (unsigned int i=1; i<Vnames.size(); i++)
            {
                if (i==1)
                    name+=" ("+Vnames[i];
                if (i>1 && i<Vnames.size()-1)
                    name+=", "+Vnames[i];
                if (i==Vnames.size()-1)
                {
                    if (Vnames.size()!=2)
                        name+=", "+Vnames[i];
                    name+=")";
                }
            }
        }
        return name;
    }
    std::string GetFullNameWithHistory(int year) const
    {
        if (year<born)
            return "No person";
        bool is_name=!names.empty(),is_surname=!surnames.empty();
        std::string first_name=GetnameWithHistory(year, is_name, names, names_in_year);
        std::string last_name=GetnameWithHistory(year, is_surname, surnames, surnames_in_year);
        if (!(is_name || is_surname))
            return "Incognito";
        if (!is_name)
            return last_name+" with unknown first name";
        if (!is_surname)
            return first_name+" with unknown last name";
        return first_name+" "+last_name;
    }

private:
    std::map<int,std::string> names_in_year,surnames_in_year;
    std::vector<int> names,surnames;
    int born;
};

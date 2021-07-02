#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <set>
#include <map>
#include <algorithm>

class Date
{
private:
    int year,month,day;
    int get_field(const std::string& s, int& pos)
    {
        int field=1;
        if (s[pos]=='-')
        {
            field=-1;
            pos++;
        }
        else if (s[pos]=='+')
            pos++;
        else if (s[pos]<'0' || s[pos]>'9')
            throw std::runtime_error("Wrong date format: " + s);
        int beg=pos;
        while (s[pos]>='0' && s[pos]<='9')
            pos++;
        if (pos==beg)
            throw std::runtime_error("Wrong date format: " + s);
        return field*stoi(s.substr(beg,pos-beg));
    }

    void Separator(const std::string& s, int& pos)
    {
        if (s[pos++]!='-')
            throw std::runtime_error("Wrong date format: " + s);
    }
public:
    Date(const std::string& s)
    {
        int pos=0;
        year=get_field(s,pos);
        Separator(s,pos);
        month=get_field(s,pos);
        Separator(s,pos);
        day=get_field(s,pos);
        if (pos<s.size())
            throw std::runtime_error("Wrong date format: " + s);
        if (month<1 || month>12)
            throw std::runtime_error("Month value is invalid: " + std::to_string(month));
        if (day<1 || day>31)
            throw std::runtime_error("Day value is invalid: " + std::to_string(day));
    }

    int GetYear() const
    {
        return year;
    }

    int GetMonth() const
    {
        return month;
    }

    int GetDay() const
    {
        return day;
    }
};

std::ostream& operator<<(std::ostream& stream, const Date& date)
{
    stream<<std::fixed<<std::setw(4)<<std::setfill('0')<<date.GetYear()<<'-';
    stream<<std::fixed<<std::setw(2)<<std::setfill('0')<<date.GetMonth()<<'-';
    stream<<std::fixed<<std::setw(2)<<std::setfill('0')<<date.GetDay();
    return stream;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() != rhs.GetYear())
        return lhs.GetYear() < rhs.GetYear();
    if (lhs.GetMonth() != rhs.GetMonth())
        return lhs.GetMonth() < rhs.GetMonth();
    return lhs.GetDay() < rhs.GetDay();
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.GetYear()==rhs.GetYear() && lhs.GetMonth()==rhs.GetMonth() && lhs.GetDay()==rhs.GetDay();
}

class Database
{
private:
    std::map<Date,std::set<std::string>> EventMap;
public:
    void AddEvent(const Date& date, const std::string& event)
    {
        EventMap[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const std::string& event)
    {
        if (EventMap[date].empty())
            return false;
        if (count(EventMap[date].begin(),EventMap[date].end(),event)==0)
            return false;
        EventMap[date].erase(event);
        return true;
    }

    int DeleteDate(const Date& date)
    {
        int k=EventMap[date].size();
        EventMap[date].clear();
        return k;
    }

    void Find(const Date& date) const
    {
        for (std::string event: EventMap.at(date))
            std::cout<<event<<std::endl;
    }

    void Print() const
    {
        for (auto elem: EventMap)
            for (std::string event: elem.second)
                std::cout<<elem.first<<" "<<event<<std::endl;
    }
};

int main()
{
    Database db;
    std::string command;
    while (getline(std::cin, command))
    {
        if (command.empty())
            continue;
        if (command=="Print")
            db.Print();
        else
        {
            int pos1=command.find(' ');
            std::string operation=command.substr(0,pos1);
            command.erase(0,pos1+1);
            try
            {
                if (operation=="Add")
                {
                    int pos2=command.find(' ');
                    db.AddEvent(Date(command.substr(0,pos2)),command.substr(pos2+1,command.size()-pos2-1));
                }
                else if (operation=="Del")
                {
                    int pos2=command.find(' ');
                    if (command.substr(0,command.size()-1).find(' ') == -1)
                    {
                        const int& N=db.DeleteDate(Date(command));
                        std::cout<<"Deleted "<<N<<" events\n";
                    }
                    else
                    {
                        if (db.DeleteEvent(Date(command.substr(0,pos2)),command.substr(pos2+1,command.size()-pos2-1)))
                            std::cout<<"Deleted successfully\n";
                        else
                            std::cout<<"Event not found\n";
                    }
                }
                else if (operation=="Find")
                {
                    try
                    {
                        db.Find(Date(command));
                    }
                    catch(std::out_of_range& ex) {}
                }
                else
                    std::cout<<"Unknown command: "<<operation<<std::endl;
            }
            catch (std::runtime_error& ex)
            {
                std::cout<<ex.what();
                return 0;
            }
        }
    }
    return 0;
}

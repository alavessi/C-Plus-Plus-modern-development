#include "date.h"

#include <iomanip>
#include <vector>

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

int Date::year() const
{
    return year_;
}

int Date::month() const
{
    return month_;
}

int Date::day() const
{
    return day_;
}

Date ParseDate(std::istream& is)
{
    int year, month, day;
    is >> year;
    is.ignore(1);
    is >> month;
    is.ignore(1);
    is >> day;
    return Date(year, month, day);
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return std::vector<int>{lhs.year(), lhs.month(), lhs.day()} < std::vector<int>{rhs.year(), rhs.month(), rhs.day()};
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return std::vector<int>{lhs.year(), lhs.month(), lhs.day()} == std::vector<int>{rhs.year(), rhs.month(), rhs.day()};
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << std::fixed << std::setw(4) << std::setfill('0') << date.year() << '-';
    os << std::fixed << std::setw(2) << std::setfill('0') << date.month() << '-';
    os << std::fixed << std::setw(2) << std::setfill('0') << date.day();
    return os;
}

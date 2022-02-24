#pragma once

#include <sstream>

class Date
{
private:
    int year_, month_, day_;

public:
    Date(int year, int month, int day);
    int year() const;
    int month() const;
    int day() const;
};

Date ParseDate(std::istream& is);

bool operator<(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

std::ostream& operator<<(std::ostream& os, const Date& date);

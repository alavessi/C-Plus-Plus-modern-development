#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const std::string &international_number)
{
    std::stringstream ss;
    ss << international_number;
    char c;
    ss >> c;
    if (c!='+')
        throw std::invalid_argument("no +");
    ss >> c;
    while (!ss.eof() && c!='-')
    {
        country_code_ += c;
        ss >> c;
    }
    if (ss.eof() || country_code_.empty())
        throw std::invalid_argument("empty country code");
    ss >> c;
    while (!ss.eof() && c!='-')
    {
        city_code_ += c;
        ss >> c;
    }
    if (ss.eof() || city_code_.empty())
        throw std::invalid_argument("empty city code");
    ss >> c;
    while (!ss.eof())
    {
        local_number_ += c;
        ss >> c;
    }
    if (local_number_.empty())
        throw std::invalid_argument("empty local number");
}

std::string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}

std::string PhoneNumber::GetCityCode() const
{
    return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const
{
    return "+" + PhoneNumber::GetCountryCode() + "-" + PhoneNumber::GetCityCode() + "-" + PhoneNumber::GetLocalNumber();
}
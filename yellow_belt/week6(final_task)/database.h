#pragma once

#include "date.h"

#include <vector>
#include <set>
#include <map>
#include <string>
#include <functional>
#include <utility>

using Predicate = std::function<bool(const Date&, const std::string&)>;

struct Storage
{
    std::vector<std::string> order_elements;
    std::set<std::string> unique_elements;
};

class Database
{
public:
    void Add(const Date& date, const std::string& event);

    void Print(std::ostream& os) const;

    int RemoveIf(const Predicate& predicate);
    
    std::vector<std::pair<Date, std::string> > FindIf(const Predicate& predicate) const;
    
    std::pair<Date, std::string> Last(const Date& date) const;

private:
    std::map<Date, Storage> database;
};
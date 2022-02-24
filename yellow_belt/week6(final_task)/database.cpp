#include "database.h"

#include <algorithm>

void Database::Add(const Date& date, const std::string& event)
{
    if (database[date].unique_elements.insert(event).second)
    {
        database[date].order_elements.push_back(event);
    }
}

void Database::Print(std::ostream& os) const
{
    for (const auto& item : database)
    {
        for (const std::string& event : item.second.order_elements)
        {
            os << item.first << " " << event << std::endl;
        }
    }
}

int Database::RemoveIf(const Predicate& predicate)
{
    int count = 0;
    for (auto it = database.begin(); it != database.end(); )
    {
        auto& orders = it->second.order_elements;
        auto border = std::stable_partition(orders.begin(), orders.end(), [it, predicate] (std::string& event) { return !predicate(it->first, event); });
        for (auto del_it = border; del_it != orders.end(); del_it = std::next(del_it))
        {
            it->second.unique_elements.erase(*del_it);
        }
        count += orders.end() - border;
        orders.erase(border, orders.end());
        it = (orders.empty()) ? database.erase(it) : std::next(it);
    }
    return count;
}

std::vector<std::pair<Date, std::string> > Database::FindIf(const Predicate& predicate) const
{
    std::vector<std::pair<Date, std::string> > found;
    for (const auto& item : database)
    {
        for (const std::string& event : item.second.order_elements)
        {
            if (predicate(item.first, event))
            {
                found.push_back(std::make_pair(item.first, event));
            }
        }
    }
    return found;
}

std::pair<Date, std::string> Database::Last(const Date& date) const
{
    auto it = database.upper_bound(date);
    if (it == database.begin())
    {
        throw std::invalid_argument("");
    }
    return std::make_pair(std::prev(it)->first, std::prev(it)->second.order_elements[std::prev(it)->second.order_elements.size() - 1]);
}
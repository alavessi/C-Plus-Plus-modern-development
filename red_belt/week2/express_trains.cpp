#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

class RouteManager
{
public:
  void AddRoute(int start, int finish)
  {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }

  int FindNearestFinish(int start, int finish) const
  {
    int result = abs(start - finish);
    if (reachable_lists_.find(start) == reachable_lists_.end() || reachable_lists_.at(start).empty())
    {
      return result;
    }
    const std::set<int>& reachable_stations = reachable_lists_.at(start);
    auto it = reachable_stations.upper_bound(finish);
    if (it == reachable_stations.begin())
    {
      return std::min(result, abs(*it - finish));
    }
    else if (it == reachable_stations.end())
    {
      return std::min(result, abs(*std::prev(it) - finish));
    }
    else
    {
      return std::min(result, std::min(abs(*it - finish), abs(*std::prev(it) - finish)));
    }
  }

private:
  std::map<int, std::set<int>> reachable_lists_;
};


int main()
{
  RouteManager routes;

  int query_count;
  std::cin >> query_count;

  for (int query_id = 0; query_id < query_count; query_id++)
  {
    std::string query_type;
    std::cin >> query_type;
    int start, finish;
    std::cin >> start >> finish;
    if (query_type == "ADD")
    {
      routes.AddRoute(start, finish);
    }
    else if (query_type == "GO")
    {
      std::cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}

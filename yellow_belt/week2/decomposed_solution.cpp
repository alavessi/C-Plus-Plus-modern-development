#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>

enum class QueryType
{
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query
{
  QueryType type;
  std::string bus;
  std::string stop;
  std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q)
{
  std::string type_in_string;
  is >> type_in_string;
  if (type_in_string == "NEW_BUS")
  {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (int i = 0; i < stop_count; i++)
    {
      is >> q.stops[i];
    }
  }
  else if (type_in_string == "BUSES_FOR_STOP")
  {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  }
  else if (type_in_string == "STOPS_FOR_BUS")
  {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  }
  else if (type_in_string == "ALL_BUSES")
  {
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse
{
  bool nostop;
  std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) 
{
  if (r.nostop)
  {
    os << "No stop";
  }
  else
  {
    for (const std::string& bus: r.buses)
    {
      os << bus << " ";
    }
  }
  return os;
}

struct StopsForBusResponse
{
  bool nobus;
  std::string bus;
  std::vector<std::string> stops;
  std::map<std::string, std::vector<std::string> > stops_to_buses;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r)
{
  if (r.nobus)
  {
    os << "No bus";
  }
  else
  {
    for (const std::string& stop : r.stops)
    {
      os << "Stop " << stop << ": ";
      if (r.stops_to_buses.at(stop).size() == 1)
      {
        std::cout << "no interchange";
      }
      else
      {
        for (const std::string& other_bus : r.stops_to_buses.at(stop))
        {
          if (r.bus != other_bus)
          {
            std::cout << other_bus << " ";
          }
        }
      }
      os << std::endl;
    }
  }
  return os;
}

struct AllBusesResponse
{
  bool nobus;
  std::map<std::string, std::vector<std::string> > buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r)
{
  if (r.nobus)
  {
    os << "No buses";
  }
  else
  {
    for (const auto& bus_item : r.buses_to_stops)
    {
      os << "Bus " << bus_item.first << ": ";
      for (const std::string& stop : bus_item.second)
      {
        os << stop << " ";
      }
      os << std::endl;
    }
  }
  return os;
}

class BusManager
{
public:
  void AddBus(const std::string& bus, const std::vector<std::string>& stops)
  {
    buses_to_stops[bus] = stops;
    for (const std::string& stop: stops)
    {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const std::string& stop) const
  {
    if (stops_to_buses.count(stop))
    {
      return {false, stops_to_buses.at(stop)};
    }
    return {true, {}};
  }

  StopsForBusResponse GetStopsForBus(const std::string& bus) const
  {
    if (buses_to_stops.count(bus))
    {
      return {false, bus, buses_to_stops.at(bus), stops_to_buses};
    }
    return {true, bus, {}, {}};
  }

  AllBusesResponse GetAllBuses() const
  {
    if (buses_to_stops.empty())
    {
      return {true, {}};
    }
    return {false, buses_to_stops};
  }
private:
  std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;
};

int main()
{
  int query_count;
  Query q;

  std::cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; i++)
  {
    std::cin >> q;
    switch (q.type)
    {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      std::cout << bm.GetBusesForStop(q.stop) << std::endl;
      break;
    case QueryType::StopsForBus:
      std::cout << bm.GetStopsForBus(q.bus) << std::endl;
      break;
    case QueryType::AllBuses:
      std::cout << bm.GetAllBuses() << std::endl;
      break;
    }
  }

  return 0;
}

#include "query.h"

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
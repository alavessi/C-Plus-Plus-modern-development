#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops)
{
    buses_to_stops[bus] = stops;
    for (const std::string& stop: stops)
    {
      stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const
{
    if (stops_to_buses.count(stop))
    {
      return {false, stops_to_buses.at(stop)};
    }
    return {true, {}};
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const
{
    if (buses_to_stops.count(bus))
    {
      return {false, bus, buses_to_stops.at(bus), stops_to_buses};
    }
    return {true, bus, {}, {}};
}

AllBusesResponse BusManager::GetAllBuses() const
{
    if (buses_to_stops.empty())
    {
      return {true, {}};
    }
    return {false, buses_to_stops};
}

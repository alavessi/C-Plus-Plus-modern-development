#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct BusesForStopResponse
{
  bool nostop;
  std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse
{
  bool nobus;
  std::string bus;
  std::vector<std::string> stops;
  std::map<std::string, std::vector<std::string> > stops_to_buses;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse
{
  bool nobus;
  std::map<std::string, std::vector<std::string> > buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
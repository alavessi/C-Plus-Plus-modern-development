#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{
  int q;
  std::cin >> q;

  std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;

  for (int i = 0; i < q; i++)
  {
    std::string operation_code;
    std::cin >> operation_code;

    if (operation_code == "NEW_BUS")
    {
      std::string bus;
      std::cin >> bus;
      int stop_count;
      std::cin >> stop_count;
      std::vector<std::string>& stops = buses_to_stops[bus];
      stops.resize(stop_count);
      for (std::string& stop : stops)
      {
        std::cin >> stop;
        stops_to_buses[stop].push_back(bus);
      }
    } 

    else if (operation_code == "BUSES_FOR_STOP")
    {
      std::string stop;
      std::cin >> stop;
      if (stops_to_buses.count(stop) == 0)
      {
        std::cout << "No stop" << std::endl;
      }
      else
      {
        for (const std::string& bus : stops_to_buses[stop])
        {
          std::cout << bus << " ";
        }
        std::cout << std::endl;
      }
    }

    else if (operation_code == "STOPS_FOR_BUS")
    {
      std::string bus;
      std::cin >> bus;
      if (buses_to_stops.count(bus) == 0)
      {
        std::cout << "No bus" << std::endl;
      }
      else
      {
        for (const std::string& stop : buses_to_stops[bus])
        {
          std::cout << "Stop " << stop << ": ";
          if (stops_to_buses[stop].size() == 1)
          {
            std::cout << "no interchange";
          }
          else
          {
            for (const std::string& other_bus : stops_to_buses[stop])
            {
              if (bus != other_bus)
              {
                std::cout << other_bus << " ";
              }
            }
          }
          std::cout << std::endl;
        }
      }

    }
    
    else if (operation_code == "ALL_BUSES")
    {
      if (buses_to_stops.empty())
      {
        std::cout << "No buses" << std::endl;
      }
      else
      {
        for (const auto& bus_item : buses_to_stops)
        {
          std::cout << "Bus " << bus_item.first << ": ";
          for (const std::string& stop : bus_item.second)
          {
            std::cout << stop << " ";
          }
          std::cout << std::endl;
        }
      }
    }
  }

  return 0;
}

#include <iostream>
#include <queue>
#include <map>
#include <tuple>
#include <string>

class BookingManager
{
public:
    void book(int64_t time, const std::string& hotel_name, uint32_t client_id, uint32_t room_count)
    {
        while (!current_bookings.empty() && std::get<0>(current_bookings.front()) <= time - 86400)
        {
            auto front = current_bookings.front();
            auto& [clients, rooms] = data[std::get<1>(front)];
            clients[std::get<2>(front)]--;
            if (clients[std::get<2>(front)] == 0)
            {
                clients.erase(std::get<2>(front));
            }
            rooms -= std::get<3>(front);
            current_bookings.pop();
        }
        current_bookings.push(std::tie(time, hotel_name, client_id, room_count));
        auto& [clients, rooms] = data[hotel_name];
        clients[client_id]++;
        rooms += room_count;
    }

    uint32_t clients(const std::string& hotel_name) const
    {
        if (data.find(hotel_name) == data.end())
        {
            return 0;
        }
        return data.at(hotel_name).first.size();
    }

    uint32_t rooms(const std::string& hotel_name) const
    {
        if (data.find(hotel_name) == data.end())
        {
            return 0;
        }
        return data.at(hotel_name).second;
    }

private:
    std::queue<std::tuple<int64_t, std::string, uint32_t, uint32_t>> current_bookings;
    std::map<std::string, std::pair<std::map<uint32_t, uint32_t>, uint32_t>> data;
};


int main()
{
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    BookingManager manager;
    int query_count;
    std::cin >> query_count;
    for (int query_id = 0; query_id < query_count; query_id++)
    {
        std::string query_type, hotel_name;
        std::cin >> query_type;
        if (query_type == "BOOK")
        {
            int64_t time;
            uint32_t client_id, room_count;
            std::cin >> time >> hotel_name >> client_id >> room_count;
            manager.book(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS")
        {
            std::cin >> hotel_name;
            std::cout << manager.clients(hotel_name) << "\n";
        }
        else if (query_type == "ROOMS")
        {
            std::cin >> hotel_name;
            std::cout << manager.rooms(hotel_name) << "\n";
        }
    }
    return 0;
}

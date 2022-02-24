#include <iomanip>
#include <iostream>
#include <vector>
#include <map>

class ReadingManager
{
public:
  ReadingManager() : page_user_counts_(MAX_PAGES_COUNT_ + 1, 0) {}

  void Read(int user_id, int page_count)
  {
    int& pages = user_page_counts_[user_id];
    page_user_counts_[pages] -= page_user_counts_[pages] != 0;
    pages = page_count;
    page_user_counts_[page_count]++;
  }

  double Cheer(int user_id) const
  {
    auto it = user_page_counts_.find(user_id);
    if (it == user_page_counts_.end())
    {
      return 0;
    }
    if (user_page_counts_.size() == 1)
    {
      return 1;
    }
    double result = 0.0;
    for (int i = 0; i < it->second; i++)
    {
      result += page_user_counts_[i];
    }
    return result / (user_page_counts_.size() - 1);
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_PAGES_COUNT_ = 1000;

  std::vector<int> page_user_counts_;
  std::map<int, int> user_page_counts_;
};


int main()
{
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  ReadingManager manager;
  int query_count;
  std::cin >> query_count;
  for (int query_id = 0; query_id < query_count; query_id++)
  {
    std::string query_type;
    std::cin >> query_type;
    int user_id;
    std::cin >> user_id;

    if (query_type == "READ")
    {
      int page_count;
      std::cin >> page_count;
      manager.Read(user_id, page_count);
    }
    else if (query_type == "CHEER")
    {
      std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }
  return 0;
}
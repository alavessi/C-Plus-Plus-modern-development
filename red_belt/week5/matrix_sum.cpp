#include "test_runner.h"
#include <future>
#include <vector>

template <typename Iterator>
class IteratorRange
{
public:
  IteratorRange(Iterator f, Iterator l): first(f), last(l) {}

  Iterator begin() const
  {
    return first;
  }

  Iterator end() const
  {
    return last;
  }

  size_t size() const
  {
    return std::distance(first, last);
  }

private:
  Iterator first, last;
};

template <typename Iterator>
class Paginator
{
public:
  Paginator<Iterator>(Iterator begin, Iterator end, size_t page_size)
  {
    for (auto it = begin; it != end;)
    {
      auto next = std::min(std::next(it, page_size), end);
      pages.push_back({it, next});
      it = next;
    }
  }

  auto begin() const
  {
    return pages.begin();
  }
  
  auto end() const
  {
    return pages.end();
  }

  size_t size() const
  {
    return pages.size();
  }

private:
  std::vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size)
{
  return Paginator(c.begin(), c.end(), page_size);
}

template <typename ContainerOfVectors>
int64_t CalculateSingleThread(const ContainerOfVectors& matrix)
{
  int64_t sum = 0;
  for (const auto& v : matrix)
  {
    for (auto x : v)
    {
      sum += x;
    }
  }
  return sum;
}

int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix)
{
  // Реализуйте эту функцию
  const size_t cores_count = 4;
  int page_size = (matrix.size() > cores_count) ? matrix.size() / cores_count + 1 : matrix.size();
  std::vector<std::future<int64_t>> futures;
  for (auto page : Paginate(matrix, page_size))
  {
    futures.push_back(std::async([page] { return CalculateSingleThread(page); }));
  }
  int64_t sum = 0;
  for (auto& f : futures)
  {
    sum += f.get();
  }
  return sum;
}

void TestCalculateMatrixSum()
{
  const std::vector<std::vector<int>> matrix =
  {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}

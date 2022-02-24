#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

template <class T>
class ObjectPool
{
public:
  T* Allocate()
  {
    T* pt = free.empty() ? new T : free.front();
    if (!free.empty())
    {
      free.pop();
    }
    allocated.insert(pt);
    return pt;
  }

  T* TryAllocate()
  {
    return free.empty() ? nullptr : Allocate();
  }

  void Deallocate(T* object)
  {
    if (allocated.find(object) == allocated.end())
    {
      throw std::invalid_argument("");
    }
    allocated.erase(object);
    free.push(object);
  }

  ~ObjectPool()
  {
    for (T* p : allocated)
    {
      delete p;
    }
    while (!free.empty())
    {
      delete free.front();
      free.pop();
    }
  }

private:
  std::set<T*> allocated;
  std::queue<T*> free;
};

void TestObjectPool()
{
  ObjectPool<std::string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}

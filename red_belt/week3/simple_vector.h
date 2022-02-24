#pragma once

#include <algorithm>

template <typename T>
class SimpleVector
{
public:
  SimpleVector();
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  T* data;
  size_t size, capacity;
};

template <typename T>
SimpleVector<T>::SimpleVector() : data(nullptr), size(0), capacity(0) {}

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) : data(new T[size]), size(size), capacity(size) {}

template <typename T>
SimpleVector<T>::~SimpleVector()
{
  delete [] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index)
{
  return data[index];
}

template <typename T>
T* SimpleVector<T>::begin()
{
  return data;
}

template <typename T>
T* SimpleVector<T>::end()
{
  return data + size;
}

template <typename T>
size_t SimpleVector<T>::Size() const
{
  return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const
{
  return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value)
{
  if (size == capacity)
  {
    capacity = capacity ? 2 * capacity : 1;
    T* new_data = new T[capacity];
    std::copy(begin(), end(), new_data);
    delete [] data;
    data = new_data;
  }
  data[size++] = value;
}
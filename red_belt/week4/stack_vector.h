#pragma once

#include <array>
#include <stdexcept>

template <typename T, size_t N>
class StackVector
{
public:
  explicit StackVector(size_t a_size = 0);

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  auto begin();
  auto end();
  const auto begin() const;
  const auto end() const;

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T& value);
  T PopBack();

private:
  std::array<T, N> data;
  size_t size;
};

template <typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size) : size(a_size)
{
  if (a_size > N)
  {
    throw std::invalid_argument("");
  }
}

template <typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index)
{
  return data[index];
}

template <typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const
{
  return data[index];
}

template <typename T, size_t N>
auto StackVector<T, N>::begin()
{
  return data.begin();
}

template <typename T, size_t N>
auto StackVector<T, N>::end()
{
  return std::next(data.begin(), size);
}

template <typename T, size_t N>
const auto StackVector<T, N>::begin() const
{
  return data.begin();
}

template <typename T, size_t N>
const auto StackVector<T, N>::end() const
{
  return std::next(data.begin(), size);
}

template <typename T, size_t N>
size_t StackVector<T, N>::Size() const
{
  return size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const
{
  return N;
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T& value)
{
  if (size == N)
  {
    throw std::overflow_error("");
  }
  data[size++] = value;
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack()
{
  if (size == 0)
  {
    throw std::underflow_error("");
  }
  return data[--size];
}
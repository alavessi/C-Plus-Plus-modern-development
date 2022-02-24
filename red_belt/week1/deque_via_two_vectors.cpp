#include <vector>
#include <stdexcept>

template<typename T> class Deque
{
public:
    Deque() {}

    bool Empty() const
    {
        return Size() == 0;
    }

    size_t Size() const
    {
        return head.size() + tail.size();
    }

    T& operator[](size_t index)
    {
        return (index < head.size()) ? head[head.size() - 1 - index] : tail[index - head.size()];
    }
    
    const T& operator[](size_t index) const
    {
        return (index < head.size()) ? head[head.size() - 1 - index] : tail[index - head.size()];
    }

    T& At(size_t index)
    {
        if (index >= Size())
        {
            throw std::out_of_range("");
        }
        return (index < head.size()) ? head[head.size() - 1 - index] : tail[index - head.size()];
    }
    
    const T& At(size_t index) const
    {
        if (index >= Size())
        {
            throw std::out_of_range("");
        }
        return (index < head.size()) ? head[head.size() - 1 - index] : tail[index - head.size()];
    }

    T& Front()
    {
        return (head.empty()) ? tail[0] : head[head.size() - 1];
    }

    const T& Front() const
    {
        return (head.empty()) ? tail[0] : head[head.size() - 1];
    }

    T& Back()
    {
        return (tail.empty()) ? head[0] : tail[tail.size() - 1];
    }

    const T& Back() const
    {
        return (tail.empty()) ? head[0] : tail[tail.size() - 1];
    }

    void PushFront(const T& value)
    {
        head.push_back(value);
    }

    void PushBack(const T& value)
    {
        tail.push_back(value);
    }   

private:
    std::vector<T> head, tail;
};
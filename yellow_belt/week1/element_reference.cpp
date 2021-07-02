#include <iostream>
#include <map>
#include <exception>

template <class Key, class Value>
Value& GetRefStrict(std::map<Key,Value>& m, Key k)
{
    try
    {
        return m.at(k);
    }
    catch(std::out_of_range& ex)
    {
        throw std::runtime_error("");
    }
}

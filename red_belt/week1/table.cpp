#include "test_runner.h"

template<typename T> class Table
{
public:
    Table(size_t row, size_t col) : _row(row), _col(col)
    {
        data.resize(row, std::vector<T>(col));
    }

    std::vector<T> operator[] (size_t i) const
    {
        return data[i];
    }

    std::vector<T>& operator[] (size_t i)
    {
        return data[i];
    }

    void Resize(size_t row, size_t col)
    {
        _row = row;
        _col = col;
        data.resize(row);
        for (auto& v: data)
        {
            v.resize(col);
        }
    }

    std::pair<size_t, size_t> Size() const
    {
        if (_row && _col)
        {
            return {_row, _col};
        }
        return {0u, 0u};
    }

private:
    std::vector<std::vector<T>> data;
    size_t _row, _col;
};

void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}

#include <iostream>
#include <numeric>
#include <vector>
#include <future>

int SumTwoVectors(const std::vector<int>& one, const std::vector <int>& two)
{
	std::future<int> f = std::async([&one] { return std::accumulate(begin(one), end(one), 0); });
	int result = std::accumulate(begin(two), end(two), 0);
	return f.get() + result;
}

int main()
{
	std::cout << SumTwoVectors({1, 1, 1, 1}, {3, 3, 3});
	return 0;
}

#include <iostream>
#include <vector>

int main()
{
	int N;
	std::cin>>N;
	std::vector<int> t(N);
	int64_t sum=0;
	for (int i=0; i<N; i++)
	{
		std::cin>>t[i];
		sum+=t[i];
	}
	int64_t average = sum/N;
	std::vector<int> numbers;
	for (int i=0; i<N; i++)
	{
		if(t[i]>average)
		{
			numbers.push_back(i);
		}
	}
	std::cout<<numbers.size()<<std::endl;
	for (int i: numbers)
	{
		std::cout<<i<<" ";
	}
	return 0;
}


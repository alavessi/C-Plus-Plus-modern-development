#include <iostream>
int main()
{
    int N,R;
    std::cin>>N>>R;
    uint64_t W,H,D,result=0;
    for (int i=0; i<N; i++)
    {
        std::cin>>W>>H>>D;
        result += W*H*D;
    }
    std::cout<<result*R;
    return 0;
}

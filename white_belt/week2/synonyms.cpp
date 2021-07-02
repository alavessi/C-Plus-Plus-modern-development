#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

int main()
{
    std::set<std::pair<std::string,std::string> > synonyms;
    std::map<std::string,int> how_many;
    int Q;
    std::cin>>Q;
    for (int i=0; i<Q; i++)
    {
        std::string query;
        std::cin>>query;
        if (query=="ADD")
        {
            std::string word1,word2;
            std::cin>>word1>>word2;
            if (synonyms.count({std::min(word1,word2),std::max(word1,word2)})==0)
            {
                how_many[word1]++;
                how_many[word2]++;
            }
            synonyms.insert({std::min(word1,word2),std::max(word1,word2)});
        }
        if (query=="COUNT")
        {
            std::string word;
            std::cin>>word;
            std::cout<<how_many[word]<<std::endl;
        }
        if (query=="CHECK")
        {
            std::string word1,word2;
            std::cin>>word1>>word2;
            if (synonyms.count({min(word1,word2),max(word1,word2)})!=0)
                std::cout<<"YES\n";
            else
                std::cout<<"NO\n";
        }
    }
    return 0;
}

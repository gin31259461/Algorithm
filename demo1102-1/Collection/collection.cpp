#include "collection.h"

collection::collection()
{
    name2index.insert(std::pair<std::string, int>("2", 0));
    name2index.insert(std::pair<std::string, int>("3", 1));
    name2index.insert(std::pair<std::string, int>("5", 2));
    name2index.insert(std::pair<std::string, int>("6", 3));
    name2index.insert(std::pair<std::string, int>("A1", 4));
    name2index.insert(std::pair<std::string, int>("11", 5));
    name2index.insert(std::pair<std::string, int>("13", 6));
    name2index.insert(std::pair<std::string, int>("B1", 7));
    name2index.insert(std::pair<std::string, int>("20", 8));
    name2index.insert(std::pair<std::string, int>("21", 9));
    name2index.insert(std::pair<std::string, int>("37", 10));
    name2index.insert(std::pair<std::string, int>("38", 11));
    name2index.insert(std::pair<std::string, int>("40", 12));
    name2index.insert(std::pair<std::string, int>("E2", 13));
}

void collection::findBestCombination(std::vector<int> index, int time, std::string type, std::vector<int> &newIndex)
{
    newIndex.clear();
    std::vector<int> type_buffer, dp(time+1), best(time+1, -1);

    if(type == "燃料")
        type_buffer = fuel;
    else if(type == "彈藥")
        type_buffer = ammo;
    else if (type == "鋼鐵")
        type_buffer = fe;
    else if(type == "鋁土")
        type_buffer = al;
    else
        return;

    //dp
    for(int i = 0; i < int(index.size()); i++)
        for(int t = time; t >= times[ index[i] ]; t--)
        {
            if( (dp[ t - times[ index[i] ] ] + type_buffer[ index[i] ] >= dp[t])
                /*(best[t] != -1 && dp[ t - times[ index[i] ] ] + type_buffer[ index[i] ] > dp[t])*/ )
            {
                dp[t] = dp[ t - times[ index[i] ] ] + type_buffer[ index[i] ];
                best[t] = index[i];
            }
        }

    //back trace
    for(int t = time; t - times[best[t]] >= 0;)
    {
        if(best[t] == -1)
            break;

        newIndex.push_back(best[t]);
        t -= times[best[t]];
    }
}

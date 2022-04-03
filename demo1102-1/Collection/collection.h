#ifndef COLLECTION_H
#define COLLECTION_H

#include <map>
#include <string>
#include <vector>

class collection
{
public:
    collection();

    //members
    std::map<std::string, int> name2index;
    std::string names[14] =
    {
        "長距離練習航海",
        "警備任務",
        "海上護衛任務",
        "防空射撃演習",
        "兵站強化任務",
        "ボーキサイト輸送任務",
        "鼠輸送作戦",
        "南西方面航空偵察作戦",
        "潜水艦哨戒任務",
        "北方鼠輸送作戦",
        "東京急行",
        "東京急行(弐)",
        "水上機前線輸送",
        "強行鼠輸送作戦"
    };
    std::vector<int> times =
    {
        30, 20, 90, 40, 25, 300, 240, 35, 120, 140, 165, 175, 410, 185
    };
    std::vector<int> fuel =
    {
        0, 30, 200, 0, 45, 0, 240, 0, 0, 320, 0, 420, 300, 0
    };
    std::vector<int> ammo =
    {
        100, 30, 200, 0, 45, 0, 300, 0, 0, 270, 380, 0, 300, 480
    };
    std::vector<int> fe =
    {
        30, 40, 20, 0, 0, 0, 0, 20, 150, 0, 270, 200, 0, 0
    };
    std::vector<int> al =
    {
        0, 0, 20, 80, 0, 250, 0, 30, 0, 0, 0, 0, 100, 0
    };

    //methods
    void findBestCombination(std::vector<int> index, int time, std::string type, std::vector<int> &newIndex);
};

#endif // COLLECTION_H

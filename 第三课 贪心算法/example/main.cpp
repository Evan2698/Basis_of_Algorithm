#include <iostream>
#include <vector>

#include <algorithm>
#include <map>
#include <climits>

typedef std::map<int, int> CoinMap; // 用来存储硬币面额和数量的映射

CoinMap coinChange(std::vector<int> &coins, int amount)
{

    CoinMap allCoins;
    for (int coin : coins)
    {
        allCoins[coin] = 0; // 初始化每种硬币的数量为0
    }

    // 按面额从大到小排序
    std::sort(coins.begin(), coins.end(), std::greater<int>());
    int count = 0;

    for (int coin : coins)
    {
        while (amount >= coin)
        {
            amount -= coin;
            count++;
            allCoins[coin]++; // 增加对应面额硬币的数量
        }
    }

    return allCoins;
}





std::vector<int> match_children_cookie(std::vector<int>& g, std::vector<int>& s) {
    // 将孩子满足度和饼干大小排序
    sort(g.begin(), g.end()); // 默认升序排序
    sort(s.begin(), s.end());

    std::vector<int> children; // 用来存储满足要求的孩子的索引
    
    int child = 0, cookie = 0;
    while (child < g.size() && cookie < s.size()) {
        if (s[cookie] >= g[child]) {
            children.push_back(child);
            child++;  // 满足一个孩子
        }
        cookie++;  // 尝试下一个饼干
    }
    
    return children;
}

typedef std::pair<int, int> Interval;
typedef std::vector<Interval> Intervals;


Intervals intervals_check(Intervals & intervals) {

    Intervals result;
    // 按照区间结束时间排序
    sort(intervals.begin(), intervals.end(), 
         [](const Interval & a, const Interval & b) {
             return a.second < b.second;
         });
    
    int count = 0;
    int end = INT_MIN; 
    
    for (const auto& interval : intervals) {
        if (interval.first >= end) {
            count++;
            end = interval.second;
            result.push_back(interval); // 记录选择的区间
        }
    }
    
    return result;
}



int main()
{
    std::vector<int> coins = {1, 5, 10, 25};
    int amount = 36;

    auto result = coinChange(coins, amount);
    std::cout << "所需硬币的面额和数量：" << std::endl;
    int count = 0;
    for (const auto &pair : result)
    {
        std::cout << "面额: " << pair.first << ", 数量: " << pair.second << std::endl;
        count += pair.second;
    }

    std::cout << "总共需要 " << count << " 个硬币。" << std::endl;



    std::cout << "------------------------" << std::endl;

    std::vector<int> g = {1, 2, 3};  // 孩子的满足度
    std::vector<int> s = {1, 1, 2};  // 饼干大小
    
    auto children = match_children_cookie(g, s);
    for (int i = 0; i < children.size(); ++i) {
        std::cout << "孩子 " << children[i] << " 满足要求" << std::endl;
    }
    std::cout << "满足要求的孩子个数：" << children.size() << std::endl;  // 输出：2 (第一个和第二个孩子,即索引是0和1的孩子)

    std::cout << "------------------------" << std::endl;

    Intervals intervals = {{1,3}, {2,4}, {3,6}, {5,7}};
    
    auto r = intervals_check(intervals);
 
    for (const auto& interval : r) {
        std::cout << "选择的区间: (" << interval.first << ", " << interval.second << ")" << std::endl;
    }
    std::cout << "选择的区间个数：" << r.size() << std::endl;  // 输出：2 (选择(1,3)和(3,6)   或   (1,3)和(5,7))

    std::cout << "------------------------" << std::endl;

    return 0;
}
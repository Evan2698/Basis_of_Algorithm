#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


int knapsack_01(std::vector<int>& weight, std::vector<int>& value, int backSize) {
    int n = weight.size();
    if (n == 0 || backSize == 0) return 0;

    // 初始化二维 DP 数组
    std::vector<std::vector<int>> dp(n, std::vector<int>(backSize + 1, 0));

    // 初始化第一行（只有第一个物品时）
    for (int j = weight[0]; j <= backSize; ++j) {
        dp[0][j] = value[0];
    }

    // 遍历物品（从第二个开始）
    for (int i = 1; i < n; ++i) {
        // 遍历背包容量
        for (int j = 1; j <= backSize; ++j) {
            if (j < weight[i]) {
                // 当前背包容量装不下物品i
                dp[i][j] = dp[i-1][j];
            } else {
                // 状态转移：取装或不装的最大值
                dp[i][j] = std::max(dp[i-1][j], dp[i-1][j - weight[i]] + value[i]);
            }
        }
    }

    return dp[n-1][backSize];
}


int LCS(std::string text1, std::string  text2) {
    int m = text1.size(), n = text2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;  // 字符匹配，长度+1
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);  // 取左侧或上侧最大值
            }
        }
    }
    return dp[m][n];
}

int main() {
    // 示例输入
    std::vector<int> weight = {2, 3, 4, 5}; // 物品重量
    std::vector<int> value = {3, 4, 5, 6}; // 物品价值
    int backSize = 8; // 背包容量

    int result = knapsack_01(weight, value, backSize);
    std::cout << "最大价值: " << result << std::endl; // 应输出 10


    std::string text1 = "abcde", text2 = "ace";
    std::cout << "最长公共子序列长度: " << LCS(text1, text2) << std::endl; // 应输出 3
    
    return 0;
}

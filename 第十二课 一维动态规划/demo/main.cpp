#include <vector>
#include <algorithm> // 用于 std::max
#include <iostream>

using namespace std;


int max_sub_array_0(const vector<int>& nums) {
    if (nums.empty()) return 0;

    std::vector<int> dp(nums.size());
    std::vector<bool> visited(nums.size(), false);
    dp[0] = nums[0];
    visited[0] = true;
    for (size_t i = 1; i < nums.size(); ++i) {        
        if (dp[i - 1] + nums[i] > nums[i]) {
            dp[i] = dp[i - 1] + nums[i];
        } else {
            dp[i] = nums[i];
            visited[i] = true;
        }  
    }

    std::cout << "dp: " << std::endl;
    for (size_t i = 0; i < dp.size(); ++i) {
        std::cout <<i << "<-->" << dp[i] << "__" << visited[i] <<std::endl;
    }



    std::cout << std::endl;

    return *std::max_element(dp.begin(), dp.end());
}



//option 
int max_sub_array(const vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int max_sum = nums[0];
    int current_max = nums[0];
    
    for (size_t i = 1; i < nums.size(); ++i) {
        current_max = max(current_max + nums[i], nums[i]);
        max_sum = max(max_sum, current_max);
    }
    
    return max_sum;
}


// 没有优化？？？？
int rob(const vector<int>& nums) {
    if (nums.empty()) return 0;
    int n = nums.size();
    if (n == 1) return nums[0];
    
    // 初始化前两个状态
    int prev_max = nums[0];
    int curr_max = max(nums[0], nums[1]);
    
    // 从第三间房屋开始递推（索引 2）
    for (size_t i = 2; i < n; ++i) {
        int new_max = max(curr_max, prev_max + nums[i]);
        prev_max = curr_max;
        curr_max = new_max;
    }
    
    return curr_max;
}

// 示例测试
#include <iostream>
int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << max_sub_array_0(nums) << endl; // 输出: 6

    vector<int> rooms = {2, 7, 9, 3, 1};
    cout << rob(rooms) << endl; // 输出: 12
    return 0;
}

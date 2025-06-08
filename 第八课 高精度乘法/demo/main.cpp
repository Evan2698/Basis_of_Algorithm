
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
std::string times(const std::string &a , const std::string &b ){
    
    std::vector<int> n1, n2;
    for (int i = a.size() - 1; i >= 0; i--) {
        n1.push_back(a[i] - '0');
    }
    for (int i = b.size() - 1; i >= 0; i--) {
        n2.push_back(b[i] - '0');
    }
    
    int m = n1.size(), n = n2.size();
    std::vector<int> res(m + n, 0);

    for (int i = 0; i < m; i++) {      //84    
        for (int j = 0; j < n; j++) {   //72
            res[i + j] += n1[i] * n2[j];
        }
    }
    int carry = 0;
    for (int k = 0; k < res.size(); k++) {
        int total = res[k] + carry;
        res[k] = total % 10;
        carry = total / 10;
    }

    std::string s;
    bool leading_zero = true;
    for (int k = res.size() - 1; k >= 0; k--) {
        if (res[k] == 0 && leading_zero) {
            continue;
        } else {
            leading_zero = false;
            s.push_back(res[k] + '0');
        }
    }
    return s.empty() ? "0" : s;
}


std::string multiply(std::string num1, std::string num2) {
    // 处理特殊情况：任一数为0，结果直接为0
    if (num1 == "0" || num2 == "0") {
        return "0";
    }
    
    int m = num1.size(), n = num2.size();
    // 结果最多有m+n位
    std::vector<int> result(m + n, 0);
    
    // 从个位开始逐位相乘
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            // 当前位的乘积
            int product = (num1[i] - '0') * (num2[j] - '0');
            // 乘积的位置
            int p1 = i + j, p2 = i + j + 1;
            // 当前总和（乘积加上原来的值）
            int sum = product + result[p2];
            
            // 更新结果数组
            result[p2] = sum % 10;
            result[p1] += sum / 10;
        }
    }
    
    // 将结果数组转换为字符串
    std::string res;
    for (int num : result) {
        // 跳过前导零（但至少保留一个数字）
        if (!(res.empty() && num == 0)) {
            res.push_back(num + '0');
        }
    }
    
    return res.empty() ? "0" : res;
}


int main() {
    std::string a = "48000000000000000000000000";
    std::string b = "27000000000000000000000000";
    //                 000000000000000000000000
    //                 000000000000000000000000
 
    
    std::string result = times(a, b);
    
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}
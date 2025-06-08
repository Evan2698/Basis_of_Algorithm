#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::max, std::reverse, std::insert
#include <cmath>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ----------------------------------------------------------------
// 辅助函数：移除前导零
std::string removeLeadingZeros(const std::string& num) {
    size_t pos = num.find_first_not_of('0');
    return (pos == std::string::npos) ? "0" : num.substr(pos);
}

// 字符串表示的大数相加
std::string addStrings(const std::string& a, const std::string& b) {
    std::string result;
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;
    
    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = (i >= 0) ? (a[i--] - '0') : 0;
        int digitB = (j >= 0) ? (b[j--] - '0') : 0;
        int sum = digitA + digitB + carry;
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    
    std::reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// 字符串表示的大数相减（要求a >= b）
std::string subtractStrings(const std::string& a, const std::string& b) {
    std::string result;
    int i = a.length() - 1;
    int j = b.length() - 1;
    int borrow = 0;
    
    while (i >= 0) {
        int digitA = (a[i--] - '0') - borrow;
        int digitB = (j >= 0) ? (b[j--] - '0') : 0;
        borrow = 0;
        
        if (digitA < digitB) {
            digitA += 10;
            borrow = 1;
        }
        result.push_back((digitA - digitB) + '0');
    }
    
    std::reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// Karatsuba乘法核心实现
std::string karatsubaMultiply(const std::string& x, const std::string& y) {
    // 处理小规模乘法直接计算
    if (x.length() <= 2 || y.length() <= 2) {
        return std::to_string(std::stoll(x) * std::stoll(y));
    }
    
    // 补零使位数相同且为偶数位
    size_t m = std::max(x.length(), y.length());
    size_t n = (m / 2) + (m % 2);   // 向上取整
    
    std::string a = x.substr(0, x.length() - n);
    std::string b = x.substr(x.length() - n);
    std::string c = y.substr(0, y.length() - n);
    std::string d = y.substr(y.length() - n);
    
    // 递归计算三个乘积
    std::string ac = karatsubaMultiply(a, c);
    std::string bd = karatsubaMultiply(b, d);

    //[(a+b)(c+d)−ac−bd]
    std::string a_plus_b = addStrings(a, b);
    std::string c_plus_d = addStrings(c, d);
    std::string ad_plus_bc = subtractStrings(
        subtractStrings(karatsubaMultiply(a_plus_b, c_plus_d), ac), bd);
    
    // 合并结果：ac*10^(2n) + (ad+bc)*10^n + bd
    std::string term1 = ac + std::string(2 * n, '0');
    std::string term2 = ad_plus_bc + std::string(n, '0');
    
    return addStrings(addStrings(term1, term2), bd);
}

int main() {
    std::vector<int> arr = {8, 3, 5, 1, 4, 7, 2, 6};
    std::cout << "Original array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array:   ";
    for (int num : arr) std::cout << num << " ";
    std::cout << std::endl;



    std::cout << "-----------------------------------------------" << std::endl;

    std::string s1 = "12345";
    std::string s2 = "6789";
    std::string result_str = karatsubaMultiply(s1, s2);

    std::cout << "Multiplication of " << s1 << " and " << s2 << " is: " << result_str << std::endl;
    



    return 0;
}
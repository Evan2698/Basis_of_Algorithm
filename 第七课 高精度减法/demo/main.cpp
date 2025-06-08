
#include <string>
#include <algorithm>
#include <iostream>

//0-9 ‘0’-‘9’
bool cmp(const std::string & a, const std::string & b) {    
    if (a.size() != b.size()) return a.size() > b.size();
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return true; // 相等
}
// A -B  if A > B   A-B
// if A < B  B-A  给结果加负号

std::string sub(const std::string & a, const std::string & b) {
    std::string res;
    std::string x = a, y = b;
    std::reverse(x.begin(), x.end());
    std::reverse(y.begin(), y.end());
    int borrow = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        int digitA = x[i] - '0';
        int digitB = (i < y.size() ? y[i] - '0' : 0);
        int diff = digitA - digitB - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        res.push_back(diff + '0');
    }

    while (res.size() > 1 && res.back() == '0') {
        res.pop_back();
    }

    std::reverse(res.begin(), res.end());

    return res;
}




int main() {

    std::string a = "41";
    std::string b = "37";

    if (cmp(a, b)) {
        std::cout << sub(a, b) << std::endl;
    } else {
        std::cout << "-" << sub(b, a) << std::endl;
    }

    return 0;
}
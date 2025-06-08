#include <iostream>
#include <string>
#include <algorithm>



std::string add_via_string(const std::string & a, const std::string& b){

    std::string result;
    std::string num1 = a;
    std::string num2 = b;
    if (num1.size() < num2.size()) {
        auto n = num2.size() - num1.size();
        for (int i = 0; i < n; ++i) {
            num1.insert(num1.begin(), '0');
        }

    } else if (num1.size() > num2.size()) {
        auto n = num1.size() - num2.size();
        for (int i = 0; i < n; ++i) {
            num2.insert(num2.begin(), '0');
        }
    }
    int carry = 0;
    for (int i = num1.size() - 1; i >= 0; --i) {
        int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }
    if (carry) {
        result.push_back(carry + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;

}






// Function to perform high-precision addition
std::string highPrecisionAdd(const std::string &num1, const std::string &num2) {
    std::string result;
    int carry = 0, sum = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string num1 = "39399483484884848483984";
    std::string num2 = "39399483484884848483984";
    std::string result = add_via_string(num1, num2);
    std::cout << "Result of addition using string: " << result << std::endl;
    std::string result2 = highPrecisionAdd(num1, num2);
    std::cout << "Result of addition using highPrecisionAdd: " << result2 << std::endl;

    return 0;
}
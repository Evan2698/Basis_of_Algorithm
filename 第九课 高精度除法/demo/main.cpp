#include <iostream>
#include <vector>
#include <algorithm>

bool cmp(std::vector<int> &A, std::vector<int> &B) {
    if (A.size() != B.size()) return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; i--)
        if (A[i] != B[i]) return A[i] > B[i];
    return true;
}

std::vector<int> sub(std::vector<int> &A, std::vector<int> &B) {
    std::vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i++) {
        t = A[i] - t;

        if (i < B.size()) t -= B[i];

        C.push_back((t + 10) % 10);
     
        t = t < 0 ? 1 : 0;       
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

std::string div(std::string &a, std::string &b, std::string &rest) {
    std::vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    std::vector<int> r;
    std::vector<int> C;
    for (int i = A.size() - 1; i >= 0; i--) {
        r.insert(r.begin(), A[i]);
        while (r.size() > 1 && r.back() == 0) r.pop_back();
        
        int k = 0;
        while (cmp(r, B)) {
            r = sub(r, B);
            k++;
        }
        C.push_back(k);
    }
    std::reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();


    std::string result;
    for(int i = r.size() - 1; i >= 0; i--) rest.push_back(r[i] + '0');
    for(int i = C.size() - 1; i >= 0; i--) result.push_back(C[i] + '0');


    return result;
}


int main() {

    std::string a = "4569";
    std::string b = "87";    
    std::string r;
    auto C = div(a, b, r);

    std::cout << "Result: " << C << std::endl;
    std::cout << "Remainder: " << r << std::endl;

    
    return 0;
}
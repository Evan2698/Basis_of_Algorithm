#include <iostream>
#include <vector>


int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    int f0 = 0;
    int f1 = 1;
    for (int i = 2; i <= n; ++i) {
        int f2 = f0 + f1;
        f0 = f1;
        f1 = f2;
    }   

    return f1;
}


typedef std::vector<std::vector<int>> YangHuiTriangle;


void print_yanghui_triangle(int n){
    YangHuiTriangle triangle(n);
    for (int i = 0; i < n; ++i) {
        triangle[i].resize(i + 1);
        triangle[i][0] = triangle[i][i] = 1;
        
        for (int j = 1; j < i; ++j) {
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
        }
    }

    /// Print the triangle
    for (const auto& row : triangle) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

}

int main() {
     int n = 10; 
     for (int i = 0; i <= n; ++i) {
        std::cout << "Fibonacci(" << i << ") = " << fibonacci(i) << std::endl;
    }


    std::cout << "Yang Hui Triangle:" << std::endl;
    print_yanghui_triangle(n);

 
    return 0;
}
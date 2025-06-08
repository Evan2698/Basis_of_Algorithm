#include <iostream>
#include <vector>


// 对一个整数数组中的元素进行累加求和
int sum(const std::vector<int> &v){
    int s = 0;
    for (int i = 0; i < v.size(); i++){
        s += v[i];
    }
    return s;
}

void perfect_number_0(int start, int end){
    for (int i = start; i <= end; i++){
        std::vector<int> divisors;
        for (int j = 1; j < i; j++){
            if (i % j == 0){
                divisors.push_back(j);
            }
        }
        int sum_of_divisors = sum(divisors);
        if (sum_of_divisors == i){
            std::cout << i << " is a perfect number." << std::endl;
        }
    }
}


void perfect_number(int start, int end){
    for (int i = start; i <= end; i++){
        int sum = 0;
        for (int j = 1; j < i; j++){
            if (i % j == 0){
                sum += j;
            }
        }
        if (sum == i){
            std::cout << i << " is a perfect number." << std::endl;
        }
    }
}


// 2. 鸡兔同笼问题
void chicken_rabbit(int heads, int feet){
    for (int i = 0; i <= heads; i++){
        int j = heads - i;
        if (2 * i + 4 * j == feet){
            std::cout << "鸡有" << i << "只，兔有" << j << "只。" << std::endl;
        }
    }    
}   

//345  3,45

//1. 除10取余 5
//2. 345/10 =34, 用第一步方法取余 4
//3. 34/10 =3, 用第一步方法取余 3

//



// 3. 水仙花数
void narcissus_number(int start, int end){
    for (int i = start; i <= end; i++){
        int sum = 0;
        int n = i;
        while (n > 0){
            int digit = n % 10;
            sum += digit * digit * digit;
            n /= 10;
        }
        if (sum == i){
            std::cout << i << " is a narcissistic number." << std::endl;
        }
    }
}


//1 密码破解  //枚举，密码字典
//2. 游戏通关



int main(){

    perfect_number_0(1, 100);
    std::cout << "------------------------" << std::endl;
    perfect_number(1, 100);
    std::cout << "------------------------" << std::endl;
    chicken_rabbit(35, 94);
    std::cout << "------------------------" << std::endl;
    narcissus_number(100, 999);
    return 0;
}

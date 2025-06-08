#include <iostream>
#include <vector>


// 链表，

struct Node {
    int data;
    Node* next;
};


Node* build_loop_ring(int n) {
    Node* head = new Node();
    head->data = 1;
    Node* current = head;

    for (int i = 2; i <= n; ++i) {
        Node* newNode = new Node();
        newNode->data = i;
        current->next = newNode;
        current = newNode;
    }
    current->next = head; // Create a loop

    return head;
}

int Josephus_ring_0(Node* head, int k) {
    Node* current = head;
    Node* prev = nullptr;

    while (current->next != current) {
        for (int i = 1; i < k; ++i) {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        delete current;
        current = prev->next;
    }

    int survivor = current->data;
    delete current; // Clean up the last node
    return survivor;
}

//  1, 2, 3, 4, 5   
//  1, 3, 4, 5      
//  1, 3, 5         
//  3, 5          
//  3            

int Josephus_ring(int n, int k) {
    std::vector<int> people(n);
    for (int i = 0; i < n; ++i) {
        people[i] = i + 1;
    }

    int index = 0;
    while (people.size() > 1) {
        index = (index + k - 1) % people.size();
        people.erase(people.begin() + index);
    }

    return people[0];
}



bool isLeapYear(int year) {
    // 闰年规则：
    // 1. 能被4整除但不能被100整除，或者
    // 2. 能被400整除
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void findDate(int year, int d) {
    // 各月份天数（非闰年）
    int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // 0索引不使用
    
    // 如果是闰年，2月有29天
    if (isLeapYear(year)) {
        months[2] = 29;
    }
    
    int month = 1;  // 从1月开始
    int days_in_month = d;
    for (; month <= 12; ++month) {
        if (days_in_month <= months[month]) {
            break;
        }
        days_in_month -= months[month];
    }
    
    std::cout << year << "年的第" << d << "天是" << month << "月" << days_in_month << "日" << std::endl;

    // 100-31-28-31 = 10 // 4月10日 // 计算万年历也是模拟算法
}



int main(){

    int n=5, k=2;
    int survivor = Josephus_ring_0(build_loop_ring(n), k);
    std::cout << "The last person remaining is (0): " << survivor << std::endl;
    survivor = Josephus_ring(n, k);
    std::cout << "The last person remaining is: " << survivor << std::endl;


    int year = 2025; // 2025年
    int day_of_year = 100; // 第100天
    findDate(year, day_of_year);

    return 0;
}

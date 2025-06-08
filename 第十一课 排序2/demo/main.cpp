#include <iostream>
#include <vector>
#include <algorithm>

void insert_sort(std::vector<int>& vec) {
    for (int i = 1; i < vec.size(); i++) {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}


void sort_counting(std::vector<int>& arr) {
    if (arr.empty()) return;

    // 1. 找出数组中的最大值，确定计数数组的大小
    int max_val = *std::max_element(arr.begin(), arr.end());
    int min_val = *std::min_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;
    
    // 2. 创建计数数组并初始化为0
    std::vector<int> count(range, 0);
    
    // 3. 统计每个元素出现的次数
    for (int element : arr) {
        count[element - min_val]++;
    }

    std::cout << "统计频率数组: ";
    for (int i = 0; i < count.size(); ++i) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;

    
    // 4. 累加计数数组，确定元素的最终位置
    for (int i = 1; i <= range; ++i) {
        count[i] += count[i - 1];
    }

    std::cout << "累加频率数组: ";
    for (int i = 0; i < count.size(); ++i) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;

    
    // 5. 创建临时数组存储排序结果
    std::vector<int> output(arr.size());
    
    // 6. 反向填充输出数组（保证稳定性）
    for (int i = arr.size() - 1; i >= 0; --i) {
        auto idx = arr[i] - min_val;
        output[count[idx] - 1] = arr[i];
        count[idx]--;
    }

    std::cout << "频率使用完毕: ";
    for (int i = 0; i < count.size(); ++i) {
        std::cout << count[i] << " ";
    }
    std::cout << std::endl;
    
    // 7. 将排序结果复制回原数组
    arr = output;
}



int main() {

    std::vector<int> unsortarray = { 4,2,8,0,5,7,1,3,6,9 };    
    std::cout << "Unsorted array: ";
    for (int i = 0; i < unsortarray.size(); ++i) {
        std::cout << unsortarray[i] << " ";
    }
    std::cout << std::endl;
    insert_sort(unsortarray);
    std::cout << "Sorted array: ";
    for (int i = 0; i < unsortarray.size(); ++i) {
        std::cout << unsortarray[i] << " ";
    }   
    std::cout << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::vector<int> unsortarray2 = { 4,34,8,0,5,7,23,3,9,56 };
    sort_counting(unsortarray2);
    std::cout << "sorted array: ";
    for (int i = 0; i < unsortarray2.size(); ++i) {
        std::cout << unsortarray2[i] << " ";
    }
    std::cout << std::endl;











    return 0;
}
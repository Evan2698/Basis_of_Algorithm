#include <iostream>
#include <vector>
#include <algorithm>


void sort_selection(std::vector<int> &vec) {

    for (int i = 0; i < vec.size() - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[min]) {
                min = j;
            }
        }
        if (min != i) {
            std::cout << "Swapping " << vec[i] << " and " << vec[min] << std::endl;
            std::swap(vec[i], vec[min]);
        }
       
    }
}


void sort_bubble(std::vector<int> &vec) {
    bool swapped;
    for (int i = 0; i < vec.size() - 1; ++i) {
        swapped = false;
        for (int j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main() {

    std::vector<int> unsortarray = { 4,2,8,0,5,7,1,3,6,9 };    
    std::cout << "Unsorted array: ";
    for (int i = 0; i < unsortarray.size(); ++i) {
        std::cout << unsortarray[i] << " ";
    }
    std::cout << std::endl;
    sort_selection(unsortarray);
    std::cout << "Sorted array: ";
    for (int i = 0; i < unsortarray.size(); ++i) {
        std::cout << unsortarray[i] << " ";
    }   
    std::cout << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::vector<int> unsortarray2 = { 4,2,8,0,5,7,1,3,9,6 };
    sort_bubble(unsortarray2);
    std::cout << "sorted array: ";
    for (int i = 0; i < unsortarray2.size(); ++i) {
        std::cout << unsortarray2[i] << " ";
    }
    std::cout << std::endl;











    return 0;
}
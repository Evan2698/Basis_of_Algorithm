#include <iostream>
#include <vector>
#include <algorithm>


int binary_search(const std::vector<int>&num, int target) {
    int left = 0;
    int right = num.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (num[mid] == target) {
            return mid; // Target found
        } else if (num[mid] < target) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return -1; // Target not found
}   

int binary_search_recursive(const std::vector<int>& num, int target, int left, int right) {
    if (left > right) {
        return -1; // Target not found
    }

    int mid = left + (right - left) / 2;

    if (num[mid] == target) {
        return mid; // Target found
    } else if (num[mid] < target) {
        return binary_search_recursive(num, target, mid + 1, right); // Search in the right half
    } else {
        return binary_search_recursive(num, target, left, mid - 1); // Search in the left half
    }
}

// example 02 
int first_greater_equal(const std::vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int square_root(int x) {
    if (x <= 1) return x;
    int left = 1, right = x;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid == x / mid) {
            return mid;
        } else if (mid < x / mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}




int main() {
    std::vector<int> num = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 23, 45, 67, 89, 100, 12};
    int target = 12;

    std::sort(num.begin(), num.end()); // Ensure the array is sorted
    for (int i = 0; i < num.size(); i++) {
        std::cout <<"index=" << i << ": "<< num[i] << " " << std::endl;
    }   

    int result = binary_search(num, target);

    if (result != -1) {
        std::cout << "Element found at index: " << result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    std::cout << "--------------------------------------------------------"<<std::endl;
    target =23;
    result = first_greater_equal(num, target);
    if (result != -1) {
        std::cout << "Element found at index: " << result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }
    std::cout << "--------------------------------------------------------"<<std::endl;

    int n = 9;
    result = square_root(n);
    std::cout << "Square root of " << n << " is: " << result << std::endl;

    return 0;
}   
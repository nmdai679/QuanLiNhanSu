#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>

// Định nghĩa hàm template trong file header
template <typename T>
bool binarySearchEmployee(const std::vector<T>& employees, const T& target) {
    int left = 0, right = employees.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (employees[mid] == target)
            return true;
        else if (employees[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

void setColor(int color);

void display();

#endif

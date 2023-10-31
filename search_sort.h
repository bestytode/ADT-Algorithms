#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> sequentialSearch(vector<int>&vec, int target)
{
	if (vec.empty())
		return {};

	vector<int>positions;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == target)
			positions.push_back(i + 1);
	}
	return positions;
}

// Search the target value in an array, then returns the index of it
// return -1 if there's not
int binarySearch(vector<int>&vec, int target)
{
    unsigned int left = 0;
    unsigned int right = vec.size() - 1;

    // Notice the loop termination condition
    while (left <= right) {
        int mid = (vec[left] + vec[right]) / 2;

        if (mid < target)
            left = mid + 1;  
        else if (mid > target)
            right = mid - 1;
        else
            return mid + 1;
    }
    return -1;
}

// Bubble sort from big to small
void bubbleSort(vector<int>& vec)
{
    size_t size = vec.size();
    for (size_t i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (vec[i] > vec[j])
                std::swap(vec[i], vec[j]);
        }
    }
}

// Quick sort, usually starts with quickSort(vector, 0, vector.size() - 1)
void quickSort(vector<int>& vec, int startIndex, int endIndex)
{
    if (startIndex > endIndex)
        return;

    int leftIndex = startIndex, rightIndex = endIndex;
    int pivotElement = vec[leftIndex]; // Set key
    while (leftIndex < rightIndex) {
        // Find one element which is less than key than swap
        while (leftIndex < rightIndex && vec[rightIndex] >= pivotElement) rightIndex--;
        std::swap(vec[leftIndex], vec[rightIndex]);

        // Find one element which is greater than key than swap
        while (leftIndex < rightIndex && vec[leftIndex] < pivotElement) leftIndex++;
        std::swap(vec[leftIndex], vec[rightIndex]);
    }
    // Recursive function
    quickSort(vec, startIndex, leftIndex - 1);
    quickSort(vec, leftIndex + 1, endIndex);
}
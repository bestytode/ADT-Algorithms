#pragma once

#include "ADT_imps/binary_heap.h"

template<typename T>
void heap_sort(std::vector<T>& array)
{
	BinaryHeap<T> heap;
	for (const auto& value : array) {
		heap.insert(value);
	}
	for (int i = array.size() - 1; i >= 0; i--) {
		array[i] = heap.pop();
	}
}

template <typename T>
void quick_sort(std::vector<T>& arr, int low, int high) 
{
    if (low < high) {
        T pivot = arr[high];  // Using last element as pivot
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            // If current element is smaller than the pivot
            if (arr[j] < pivot) {
                i++;    // Increment index of smaller element
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1; // Partition index

        // Recursively sort elements before and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
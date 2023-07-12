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

int binarySearch(vector<int>&vec, int target)
{
    int left = 0;
    int right = vec.size() - 1;

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

void bubbleSort(vector<int>& vec)
{
    int n = vec.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (vec[i] > vec[j])
                std::swap(vec[i], vec[j]);
        }
    }
}

void quickSort(vector<int>& vec, int left, int right)
{
    if (left > right)
        return;

    int i = left, j = right;
    int key = vec[left]; // Set key
    while (i < j) {
        // Find one element which is less than key than swap
        while (i < j && vec[j] >= key) j--;
        std::swap(vec[i], vec[j]);

        // Find one element which is greater than key than swap
        while (i < j && vec[i] < key) i++;
        std::swap(vec[i], vec[j]);
    }
    // Recursive function
    quickSort(vec, left, i - 1);
    quickSort(vec, i + 1, right);
}

vector<vector<int>> myfunc(int n)
{
    if (n == 1) return vector<vector<int>>{ {1}};
    if (n == 2) return vector<vector<int>>{ {1, 2}, { 4,3 }};
    vector<vector<int>>result(n, vector<int>(n, 0));
    int count = 1;
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i; j <= n - 2 - i; j++)
            result[i][j] = count++;
        for (int j = i; j <= n - 2 - i; j++)
            result[j][n - 1 - i] = count++;
        for (int j = n - 1 - i; j >= i + 1; j--)
            result[n - 1 - i][j] = count++;
        for (int j = n - 1 - i; j >= i + 1; j--)
            result[j][i] = count++;
    }
    if (n % 2) result[n / 2][n / 2] = n * n;
    return result;
}
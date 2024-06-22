#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using namespace std;

int pivotIndex(vector<int>& nums) 
{
    int leftSum = 0;
    int acc = accumulate(nums.cbegin(), nums.cend(), 0);
    for (int i = 0; i < nums.size(); i++) {
        if (2 * leftSum + nums[i] == acc) 
            return i;
        leftSum += nums[i];
    }
    return -1;
}

int searchInsert(vector<int>& nums, int target) 
{
	int left = 0, right = nums.size() - 1;

	while (left <= right) {
		int mid = (left + right) / 2;
		if (nums[mid] < target)
            left = mid + 1;
		else
            right = mid - 1;
	}
	return left;
}

vector<vector<int>> merge(vector<vector<int>>& intervals) 
{
	if (intervals.empty()) return {};
	std::sort(intervals.begin(), intervals.end());
	vector<vector<int>>merged;
	merged.push_back(intervals[0]);

	for (int i = 0; i < intervals.size(); i++) {
		int left = intervals[i][0], right = intervals[i][1];
		if (merged.back()[1] < left) merged.push_back({ left,right }); 
		else merged.back()[1] = max(merged.back()[1], right);          
	}
	return merged;
}

void setZeroes(vector<vector<int>>& matrix) 
{
	int m = matrix.size();
	int n = matrix[0].size();
	vector<int> row(m), col(n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == 0) 
				row[i] = col[j] = true;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (row[i] || col[j]) 
				matrix[i][j] = 0;
		}
	}
}

string longestCommonPrefix(vector<string>& strs)
{
	if (strs.empty())
		return " ";
	
	string ret;
	for (int j = 0; j < strs[0].size(); j++) {
		for (int i = 0; i < strs.size(); i++) {
			if (strs[i][j] != strs[0][j])
				return ret;
		}
		ret = ret + strs[0][j];
	}
	return ret;
}

void reverseString(vector<char>& s) 
{
	int left = 0, right = s.size() - 1;
	while (left <= right) {
		std::swap(s[left], s[right]);
		left++;
		right--;
	}
}

vector<int> twoSum(vector<int>& numbers, int target)
{
	int l = 0, r = numbers.size() - 1;
	while (l < r) {
		int sum = numbers[l] + numbers[r];
		if (sum == target)
			return{ l + 1, r + 1 };
		else if (sum < target) l++;
		else r--;
	}
}

int removeElement(vector<int>& nums, int val)
{
	int newSize = 0;
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] == val) 
			continue;
		else
			nums[newSize++] = nums[i];
	}
	return newSize;
}

vector<vector<int>> generate(int numRows) 
{
	vector<vector<int>>ret = { {1},{1,1} };
	if (numRows == 1)
		return { {1} };
	
	if (numRows == 2) 
		return ret;
	
	for (int i = 2; i < numRows; i++) {
		vector<int>cur(i + 1);
		for (int j = 0; j <= i; j++) {
			if (j == 0 || j == i) 
				cur[j] = 1;
			else 
				cur[j] = ret[i - 1][j - 1] + ret[i - 1][j];
		}
		ret.push_back(cur);
	}
	return ret;
}

string reverseWords(string s) 
{
	string ret;
	int length = s.size(), i = 0;

	while (i < length) {
		int start = i;       
		while (i < length && s[i] != ' ') i++; 
		
		for (int p = start; p < i; p++) 
			ret.push_back(s[start + i - 1 - p]);
		
		while (i < length && s[i] == ' ') {
			i++;
			ret.push_back(' ');
		}
	}
	return ret;
}

int removeDuplicates(vector<int>& nums)
{
	if (nums.empty()) 
		return 0;

	int fast = 1, slow = 1;
	while (fast < nums.size()) {
		if (nums[fast] != nums[fast - 1]) {
			nums[slow] = nums[fast];
			++slow;
		}
		++fast;
	}
	return slow;
}

vector<vector<int>> threeSum(vector<int>& nums)
{
	vector<vector<int>>res;
	if (nums.empty() || nums.size() < 3)
		return res;

	std::sort(nums.begin(), nums.end());
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		if (nums[i] > 0)
			return res;

		if (nums[i] == nums[i - 1])
			continue;

		int left = i + 1, right = n - 1;
		while (left < right) {
			if (nums[i] + nums[left] > -nums[right]) right--;
			else if (nums[i] + nums[left] < -nums[right]) left++;
			else  {
				res.emplace_back(nums[i] , nums[left], nums[right]);
				left++;
				right--;

				while (left < right && nums[right] == nums[right + 1]) {
					right--;
				}
				while (left < right && nums[left] == nums[left - 1]) {
					left++;
				}
			}
		}
	}
	return res;
}

int minSubArrayLen(int target, vector<int>& nums) 
{
	int result = INT32_MAX;
	int sum = 0, i = 0;
	int subLength = 0;

	for (int j = 0; j < nums.size(); j++) {
		sum += nums[j];

		// if sum is greater than target
		while (sum >= target) {
			// update sublength
			subLength = (j - i + 1);
			result = result < subLength ? result : subLength;
			sum -= nums[i++]; 
		}
	}
	
	return result == INT32_MAX ? 0 : result;
}

vector<vector<int>>fourSum(vector<int>& nums,int target)
{
	std::vector<std::vector<int>>result;
	std::sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); ++i) {
		if (i > 0 && nums[i] == nums[i - 1]) 
			continue;
		for (int j = i + 1; j < nums.size(); ++j) {
			if (j > i + 1 && nums[j] == nums[j - 1]) 
				continue;
			int left = j + 1, right = nums.size() - 1; 
			while (left < right) {
				if (nums[i] + nums[j] + nums[left] + nums[right] < target) right--;
				else if (nums[i] + nums[j] + nums[left] + nums[right] > target)	left++;
				else {
					result.emplace_back(vector<int>{nums[i] + nums[j] + nums[left] + nums[right]});
					while (left < right && nums[right] == nums[right - 1]) right--; 
					while (left < right && nums[left] == nums[left + 1]) left++;    
					left++, right--;
				}
			}
		}
	}
	return result;
}

vector<int> sortedSquares(vector<int>& nums) 
{
	int n = nums.size() - 1;
	vector<int>result(nums.size(), 0);

	int i = 0, j = nums.size() - 1;
	while (i <= j) {
		if (nums[i] * nums[i] < nums[j] * nums[j]) {
			result[n--] = nums[j] * nums[j];
			j--;
		}
		else {
			result[n--] = nums[i] * nums[i];
			i++;
		}
	}
	return result;
}
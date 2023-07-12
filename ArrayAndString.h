#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

//寻找数组的中心索引
int pivotIndex(vector<int>& nums);

//搜索插入位置
int searchInsert(vector<int>& nums, int target);

//合并区间
vector<vector<int>> merge(vector<vector<int>>& intervals);

//最长公共前缀
string longestCommonPrefix(vector<string>& strs);

//零矩阵
void setZeroes(vector<vector<int>>& matrix);

//反转字符串
void reverseString(vector<char>& s);

//两数之和II - 输入有序数组
vector<int> twoSum(vector<int>& numbers, int target);

//移除元素
int removeElement(vector<int>& nums, int val);

//杨辉三角
vector<vector<int>> generate(int numRows);

//反转字符串中的单词 III
string reverseWords(string s);

//删除排序数组中的重复项
int removeDuplicates(vector<int>& nums);

//三数之和
vector<vector<int>> threeSum(vector<int>& nums);

//长度最小的子数组
int minSubArrayLen(int target, vector<int>& nums);

//四数之和
vector<vector<int>>fourSum(vector<int>& nums, int target);

//有序数组的平方
vector<int> sortedSquares(vector<int>& nums);

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
		int left = intervals[i][0], int right = intervals[i][1];
		if (merged.back()[1] < left) merged.push_back({ left,right }); //若前区间的右端点小于后区间的左端点，则说明整个后区间在前区间右侧
		else merged.back()[1] = max(merged.back()[1], right);          //反之，则前区间的右端点取两个区间的右端点的最大值
	}
	return merged;
}

void setZeroes(vector<vector<int>>& matrix) 
{
	int m = matrix.size();
	int n = matrix[0].size();
	vector<int> row(m), col(n);//辅助矩阵row,col

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
	int length = s.size(), int i = 0;

	while (i < length) {
		int start = i;       
		while (i < length && s[i] != ' ') i++; //遍历至s[i] == ' ';
		
        //添加s[i - 1]到s[start]到ret中(在此过程中实现单词的反转)
		for (int p = start; p < i; p++) 
			ret.push_back(s[start + i - 1 - p]);
		
        //若s[i] == ' '; 移动i至下一位且在新string中添加空格
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

	int fast = 1, int slow = 1;
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

		// 去重第一个数
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

				// 去重第二、三个数
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
			sum -= nums[i++]; // 不断变更i（子序列的起始位置
		}
	}
	// 若result没有被赋值，返回0
	return result == INT32_MAX ? 0 : result;
}

vector<vector<int>>fourSum(vector<int>& nums,int target)
{
	std::vector<std::vector<int>>result;
	std::sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); ++i) {
		if (i > 0 && nums[i] == nums[i - 1]) //去重第一个数，注意边界
			continue;
		for (int j = i + 1; j < nums.size(); ++j) {
			if (j > i + 1 && nums[j] == nums[j - 1]) //去重第二个数
				continue;
			int left = j + 1, right = nums.size() - 1; //left取j + 1
			while (left < right) {
				if (nums[i] + nums[j] + nums[left] + nums[right] < target) right--;
				else if (nums[i] + nums[j] + nums[left] + nums[right] > target)	left++;
				else {
					result.emplace_back(vector<int>{nums[i] + nums[j] + nums[left] + nums[right]});
					while (left < right && nums[right] == nums[right - 1]) right--; //去重第三个数
					while (left < right && nums[left] == nums[left + 1]) left++;    //去重第四个数
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
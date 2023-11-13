#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Function to find all pairs of indices in 'nums' whose values sum up to 'target'.
std::vector<std::pair<int, int>> twoSum(std::vector<int>& nums, int target)
{
    std::unordered_map<int, int> numToIndex; // key: nums[i], value: index i
    std::vector<std::pair<int, int>> result; 
    for (int i = 0; i < nums.size(); ++i) {
        auto itr = numToIndex.find(target - nums[i]); 
        if (itr != numToIndex.end()) // check duplication
            result.emplace_back(itr->second, i); // Add matching pairs to the result

        numToIndex[nums[i]] = i; // adding key-value to hashtable
    }

    return result;
}

bool containsDuplicate(vector<int>&nums) 
{
    unordered_set<int> s;
    for (int x : nums) {
        if (s.find(x) != s.end()) 
            return true;
        s.insert(x);
    }
    return false;
}

int singleNumber(vector<int>& nums) 
{
    unordered_set<int>hash;
    for (auto x : nums) {
        if (hash.find(x) == hash.end())       
            hash.insert(x);   
        else 
            hash.erase(x);
    }
    return *hash.begin();
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
{
    unordered_set<int> result_set; 
    unordered_set<int> nums_set(nums1.begin(), nums1.end());
    for (int num : nums2) {
        if (nums_set.find(num) != nums_set.end()) 
            result_set.insert(num);       
    }
    return vector<int>(result_set.begin(), result_set.end());
}

char firstUniqChar(string s) 
{
    unordered_map<char, int> frequency;

    // count number of s[i], storing in unmap[s[i]]
    for (char ch : s) 
        ++frequency[ch];
    
    for (int i = 0; i < s.size(); ++i) {
        if (frequency[s[i]] == 1)
            return s[i];
    }
    return ' ';
}

// helper function for isHappy()
int getSum(int n) 
{
    int sum = 0;
    while (n) {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) 
{
    unordered_set<int> set;
    while (1) {
        int sum = getSum(n);
        if (sum == 1)
            return true;

        // 若sum已出现过，说明陷入了无限循环
        if (set.find(sum) != set.end())
            return false;
        else
            set.insert(sum);

        n = sum;
    }
}

int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) 
{
    // key: value of a + b，value: show times of a + b
    unordered_map<int, int>unmap;
    for (int a : nums1) {
        for (int b : nums2)
            ++unmap[a + b];
    }

    int count = 0;
    for (int c : nums3) {
        for (int d : nums4) {
            if (unmap.find(0 - c - d) != unmap.end())
                count += unmap[0 - c - d];
        }
    }
    return count;
}
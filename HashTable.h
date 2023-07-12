#pragma once

#include <vector>
#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

//��ƹ�ϣ����
class MyHashSet;

//��ƹ�ϣӳ��
class MyHashMap;

//����֮��
vector<int> twoSum(vector<int>& nums, int target);

//�����ظ�Ԫ��
bool containsDuplicate(vector<int>& nums);

//ֻ����һ�ε�����
int singleNumber(vector<int>& nums);

//��������Ľ���
vector<int> intersection(vector<int>& nums1, vector<int>& nums2);

// ��ָ Offer 50. ��һ��ֻ����һ�ε��ַ�
char firstUniqChar(string s);

// ������
bool isHappy(int n);

// �������II
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4);

class MyHashSet 
{
private:
    vector<list<int>> data;
    static const int base = 769;
    static int hash(int key) {
        return key % base;
    }

public:
    MyHashSet() : data(base) {}

    void add(int key) 
    {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key)           
                return;          
        }
        data[h].push_back(key);
    }

    void remove(int key) 
    {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key) {
                data[h].erase(it);
                return;
            }
        }
    }

    bool contains(int key) 
    {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key)             
                return true;          
        }
        return false;
    }
};

class MyHashMap 
{
private:
    vector<list<pair<int, int>>> data;
    static const int base = 769;
    static int hash(int key) {
        return key % base;
    }
public:
    MyHashMap() : data(base) {}

    void put(int key, int value) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it).first == key) {
                (*it).second = value;
                return;
            }
        }
        data[h].push_back(make_pair(key, value));
    }

    int get(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it).first == key) 
                return (*it).second;
        }
        return -1;
    }

    void remove(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it).first == key) {
                data[h].erase(it);
                return;
            }
        }
    }
};

vector<int> twoSum(vector<int>& nums, int target)
{
    unordered_map<int, int> ret;
    for (int i = 0; i < nums.size(); ++i) {
        auto it = ret.find(target - nums[i]);
        if (it != ret.end())       
            return { it->second, i };

        ret[nums[i]] = i;
    }
}

bool containsDuplicate(vector<int>&nums) 
{
    unordered_set<int> s;
    for (int x : nums) {
        // ����s�е�һ��������x��λ�ò���β���������������
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
    unordered_set<int> result_set;  //��Ž������set�������ȥ��
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

    // ͳ��s[i]�ĸ���,��unmap[s[i]]���洢
    for (char ch : s) 
        ++frequency[ch];
    
    for (int i = 0; i < s.size(); ++i) {
        if (frequency[s[i]] == 1)
            return s[i];
    }
    return ' ';
}

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

        // ��sum�ѳ��ֹ���˵������������ѭ��
        if (set.find(sum) != set.end())
            return false;
        else
            set.insert(sum);

        n = sum;
    }
}

int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) 
{
    // key:a + b����ֵ��value:a + b��ֵ���ֵĴ���
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
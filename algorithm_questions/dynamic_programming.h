#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include <vector>
#include <unordered_map>

std::vector<int> memo(1000, -1); // global variable for dynamic programming

int Fibonacci(int n) 
{
    // If the value has already been computed, return it.
    if (memo[n] != -1) 
        return memo[n];

    // The base cases for the Fibonacci sequence.
    if (n <= 1) 
        return n;

    // Recursively compute the Fibonacci value for n.
    memo[n] = Fibonacci(n - 1) + Fibonacci(n - 2);
    return memo[n];
}

// Returns the best possible price obtainable for a rod of length 'n'
// and a price array that contains prices of smaller pieces of rod.
int cutRod(const std::vector<int>& price, int n) 
{
    std::vector<int> value(n + 1);
    value[0] = 0; // No profit for a rod of length 0.

    // Build the table value[] in a bottom-up manner.
    for (int i = 1; i <= n; ++i) {
        int max_val = -1;
        for (int j = 0; j < i; ++j)
            max_val = std::max(max_val, price[j] + value[i - j - 1]); // this is where we use the previous storing value[n]
        value[i] = max_val; // max for a rod of length i
    }

    return value[n];
}

// We use DP to resolve this problem, so typically we need int numbers.
// If your coins are {0.1, 0.5, 1}, you'd convert them to {1, 5, 10} by multiplying by 10.
// If your amount is 11.6, you'd convert it to 116 by multiplying by 10.
int coinChange(std::vector<int>& coins, int amount)
{
    std::vector<int> dp(amount + 1, std::numeric_limits<int>::max());
    dp[0] = 0;

    // iterate i from 1 to amount
    for (int i = 1; i <= amount; i++) {
        // for any coin in coins that has less value to the current amount
        for (int coin : coins) {
            if (coin <= i) 
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
        }
    }

    // Check if the amount is achievable. If dp[amount] is still 'infinity', return -1.
    return dp[amount] == std::numeric_limits<int>::max() ? -1 : dp[amount];
}

// dp array max_current[i], where i is the size of subarray with max sum.
// Time complexity: O(n), where n is the size of nums
// Space complexity: O(1).
int maxSubArray(std::vector<int>& nums) {
    if (nums.empty()) return -1;
    int max_global = nums[0];
    int max_current = nums[0];

    for (int i = 1; i < nums.size(); i++) {
        max_current = std::max(nums[i], nums[i] + max_current);

        max_global = max_current > max_global ? max_current : max_global;
    }
    return max_global;
}

int lengthOfLongestSubstring(std::string s) {

    std::unordered_map<char, int> charIndexMap; // key: char, value: index
    int maxLength = 0;
    int start = 0;

    for (int end = 1; end < s.length(); end++) {
        char currentChar = s[end];

        // If the character is found in the map and is within the current window
        if (charIndexMap.find(currentChar) != charIndexMap.end() &&
            charIndexMap[currentChar] >= start) {
            // Move the start to the right of the last occurrence
            start = charIndexMap[currentChar] + 1;
        }

        // Update the character's position in the map
        charIndexMap[currentChar] = end;

        // Calculate the current length and update maxLength if needed
        maxLength = std::max(maxLength, end - start + 1);
    }

    return maxLength;
}

int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
    // m * n matrix
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    // If the starting cell has an obstacle, then return 0 as there are no paths
    if (obstacleGrid[0][0] == 1) {
        return 0;
    }

    // init vector<vector<int>> with height of n, width of m.
    std::vector<std::vector<int>> dp(m, std::vector(n, 0));
    dp[0][0] = 1;

    for (int i = 1; i < n; i++) {
        dp[0][i] = (obstacleGrid[0][i] == 1) ? 0 : dp[0][i - 1];
    }

    for (int j = 1; j < m; j++) {
        dp[j][0] = (obstacleGrid[j][0] == 1) ? 0 : dp[j - 1][0];
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[i][j] == 1) {
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
    
    return dp[m - 1][n - 1];
}
#endif
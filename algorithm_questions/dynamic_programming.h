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

#endif
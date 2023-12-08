#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include <vector>

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

#endif
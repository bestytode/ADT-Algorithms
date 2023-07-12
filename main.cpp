#include <vector>
#include <iostream>

using namespace std;

// LeetCode No.59 spiral matrix (mid)
vector<vector<int>> generateMatrix(int n)
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

int main()
{
    int n;
    std::cout << "input number of matrix to generate" << std::endl;
    std::cin >> n;

    vector<vector<int>>res = generateMatrix(n);
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            std::cout << res[i][j] << " ";
        }
        std::cout << std::endl;
    }

	std::cin.get();

    //just a test
    //test 2
}
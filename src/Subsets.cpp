#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int countSubsets(const std::vector<int> &numbers)
{
    const int MOD = 1e9 + 7;
    const int MAX_SUM = 5005;
    const int MULTIPLE = 5;

    int n = numbers.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(MAX_SUM, 0));

    // 初始条件
    dp[0][0] = 1;

    // 动态规划过程
    for (int i = 1; i <= n; ++i)
    {
        int num = numbers[i - 1];
        for (int j = 0; j < MAX_SUM; ++j)
        {
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][(j - num + MULTIPLE * MULTIPLE) % MULTIPLE]) % MOD;
        }
    }

    // 统计和为5的倍数的子集个数
    int result = 0;
    for (int i = 0; i < MAX_SUM; i += MULTIPLE)
    {
        result = (result + dp[n][i]) % MOD;
    }

    return result;
}

void run_subsets_counting()
{
    // 准备数据
    std::vector<int> numbers;
    for (int i = 1; i <= 100000; ++i)
    {
        numbers.push_back(i);
    }

    // 计时开始
    auto start = chrono::high_resolution_clock::now();

    // 运行算法
    int result = countSubsets(numbers);

    // 计时结束
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Subsets Counting Time: " << duration.count() << "ms" << endl;
}

int main()
{
    run_subsets_counting();
    return 0;
}

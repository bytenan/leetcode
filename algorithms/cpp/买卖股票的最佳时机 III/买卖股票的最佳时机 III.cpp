// Source : https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/
// Author : Yanan Wang
// Date   : 2023-05-29

/**
 * 动态规划类题目的一般步骤：
 *   1. 状态表示
 *        设dp[i]表示第i天结束后的最大利润，但状态还不够细，so
 *          设f[i][j]表示第i天结束后，完成了j笔交易后，处于无票状态的最大利润
 *          设g[i][j]表示第i天结束后，完成了j笔交易后，处于有票状态的最大利润
 *   2. 状态转移方程
 *        有票和无票这两种状态是可以随意进行切换的，但要注意一点：每卖出一次票，交易次数+1。so
 *        f[i][j] = max(f[i - 1][j], g[i - 1][j - 1] + prices[i])
 *        g[i][j] = max(g[i - 1][j], f[i - 1][j] - prices[i]);
 *   3. 初始化
 *        看f就知道要初始化第一行和第一列，看g就知道要初始化第一行。那么这里可以稍微修改f的状态转移方程，使得仅初始化第一行即可。
 *        修改为：if (j - 1 >= 0)
 *                   f[i][j] = max(f[i - 1][j], g[i - 1][j - 1] + prices[i]);
 *               else 
 *                   f[i][j] = f[i - 1][j];
 *        然后开始对第一行初始化
 *     f     j                        g       j
 *       |-------|-------|------|       |------------|-------|------|
 *     i |   0   |  -∞   |  -∞  |     i | -prices[0] |   -∞  |  -∞  |
 *       |-------|-------|------|       |------------|-------|------|
 *       |       |       |      |       |            |       |      |
 *       |-------|-------|------|       |------------|-------|------|
 *       |       |       |      |       |            |       |      |
 *       |-------|-------|------|       |------------|-------|------|
 *       |       |       |      |       |            |       |      |
 *       |-------|-------|------|       |------------|-------|------|
 *       |       |       |      |       |            |       |      |
 *       |-------|-------|------|       |------------|-------|------|
 *        还有一点注意：当使用+∞和-∞的时候，是有可能会出现溢出现象的，
 *        所以这里不写-∞，而是根据题目提示的数据范围，写出一个绝对值刚好比最大值大1的数
 *   4. 填表顺序
 *        从上往下填每一行，从左往右填每一列
 *   5. 返回值
 *        最后一行的最大值
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(3, -(1e5 + 1)));
        vector<vector<int>> g(n, vector<int>(3, -(1e5 + 1)));
        f[0][0] = 0;
        g[0][0] = -prices[0];
        for (int i = 1; i < n; ++i) 
        {
            for (int j = 0; j < 3; ++j)
            {
                if (j - 1 >= 0)
                    f[i][j] = max(f[i - 1][j], g[i - 1][j - 1] + prices[i]);
                else 
                    f[i][j] = f[i - 1][j];
                g[i][j] = max(g[i - 1][j], f[i - 1][j] - prices[i]);
            }
        }
        int result = 0;
        for (int i = 1; i < 3; ++i)
            if (result < f[n - 1][i])
                result = f[n - 1][i];
        return result;
    }
};
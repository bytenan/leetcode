// Source : https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/
// Author : Yanan Wang
// Date   : 2023-05-25

/**
 * 动态规划类题目的一般步骤：
 *   1. 状态表示
 *        题目的限制条件: 1、第i天卖出股票后第i+1天变为冷冻期（无法买入股票）
 *                      2、拥有股票时，无法买入股票
 *        设dp[i]表示第i天结束之后的最大利润，那么继续细分状态，
 *            设dp[i][0]表示第i天处于持股状态
 *            设dp[i][1]表示第i天处于不持股&没卖出状态
 *            设dp[i][2]表示第i天处于不持股&卖出状态
 *   2. 状态转移方程
 *
 *          第i-1天状态                            过程                    能否状态转换      第i天状态
 * ------------------------------------------------------------------------------------------------------
 * |       持股状态                       -----第i天什么也不做----->             ✅            
 * |       不持股&没卖出状态               --------第i天买股-------->            ✅          持股状态       
 * |       不持股&卖出状态                 -------第i天冷冻期------>             ❌          
 * ------------------------------------------------------------------------------------------------------
 * |       持股状态                      第i天要么什么也不做，要么卖出             ❌           
 * |       不持股&没卖出状态               -----第i天什么也不做----->             ✅          不持股&没卖出状态     
 * |       不持股&卖出状态                 -------第i天冷冻期------>             ✅     
 * ------------------------------------------------------------------------------------------------------
 * |       持股状态                       --------第i天卖出------->             ✅        
 * |       不持股&没卖出状态               第i天要么什么也不做，要么买股             ❌          不持股&卖出状态          
 * |       不持股&卖出状态                 -------第i天冷冻期------>              ❌          
 * ------------------------------------------------------------------------------------------------------      
 *        即，状态转移方程：dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
 *                       dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]);
 *                       dp[i][2] = dp[i - 1][0] + prices[i];
 *   3. 初始化
 *        dp[0][0] = -prices[i];
 *        dp[0][1] = 0;
 *        dp[0][2] = 0;
 *   4. 填表顺序
 *        一起从左向右填
 *   5. 返回值
 *        max(dp[n - 1][1], dp[n - 2][2])
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = -prices[0];
        for (int i = 1; i < n; ++i)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]);
            dp[i][2] = dp[i - 1][0] + prices[i];
        }
        return max(dp[n - 1][1], dp[n - 1][2]);
    }
};
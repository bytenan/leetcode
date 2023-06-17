// Source : https://leetcode.cn/problems/the-masseuse-lcci/
// Author : Yanan Wang
// Date   : 2023-06-17

class Solution {
    public int massage(int[] nums) {
        int n = nums.length;
        int[] f = new int[n + 1];
        int[] g = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            f[i] = g[i - 1] + nums[i - 1];
            g[i] = Math.max(f[i - 1], g[i - 1]);
        }
        return Math.max(f[n], g[n]);
    }
}
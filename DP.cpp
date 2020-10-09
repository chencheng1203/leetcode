#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>

using std::cout;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 最大子序和
int maxSubArray(vector<int>& nums) {
    if (nums.size() == 0) return -1;
    int res = nums[0];
    int max_num = 0;
    for (int i = 0; i < nums.size(); i++){
        if (max_num < 0){
            max_num = nums[i];
        }else{
            max_num += nums[i];
        }
        res = std::max(max_num, res);
    }
    return res;
}


// 股票的最大利润
int maxProfit(vector<int>& prices) {
    int max_profit = 0;
    if (prices.size() <= 1) return 0;
    int curr_min = prices[0];
    for (int i = 1; i < prices.size(); i++){
        if (prices[i] <= curr_min){
            curr_min = prices[i];
            continue;
        }else{
            max_profit = std::max(max_profit, prices[i] - curr_min);
        }
    }
    return max_profit;
}


// 0-1 背包问题
// 1. 状态定义：dp[i][j] 将前i件物品放入容量为j的背包所能获得的最大价值
// 2. 若当前背包容量W不足以放下重量为w的物品，则背包内物品的价值等于前i-1物品的价值，即 dp[i][j] = dp[i-1][j] // weight[i] > j
// 3. 若当前背包容量足以放下当前的物品，则dp[i][j] = max(dp[i-1][j], dp[i-1][j-wight[i]] + values[i])
int zero_one_package(vector<int>& weights, vector<int>& values, int W){
    int things_k = weights.size();
    vector<vector<int>> dp(things_k+1, vector<int>(W+1, 0));
    for (int i = 1; i < things_k+1; i++){
        for (int j = 1; j < W+1; j++){
            if (weights[i-1] > j){
                dp[i][j] = dp[i-1][j];
            }else{
                dp[i][j] = std::max(dp[i-1][j], dp[i-1][j - weights[i-1]] + values[i-1]);
            }
        }
    }
    for (int i = 0; i < things_k+1; i++){
        for (int j = 0; j < W+1; j++){
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }
    return dp[things_k][W];
}


// 矩阵前缀和
vector<vector<int>> matrix_prefix_sum(vector<vector<int>>& matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> mat_prefix(rows+1, vector<int>(cols+1, 0));
    for (int i = 1; i <= rows; i++){
        for (int j = 1; j <= cols; j++){
            mat_prefix[i][j] = matrix[i-1][j-1] + mat_prefix[i - 1][j] + mat_prefix[i][j - 1] - mat_prefix[i - 1][j - 1];
        }
    }
    return mat_prefix;
}

int maxSideLength(vector<vector<int>>& mat, int threshold) {
    vector<vector<int>> mat_pre = matrix_prefix_sum(mat);
    int rows = mat.size();
    int cols = mat[0].size();
    int curr_cube_size = std::min(rows, cols);
    int ans = 0;
    int curr_sum = 0;
    for (int k = 1; k <= curr_cube_size; k++){
        for (int i = 1; i <= rows; i++){
            for (int j = 1; j <= cols; j++){
                if (i - k < 0 || j - k < 0)
                    continue;
                curr_sum = mat_pre[i][j] - mat_pre[i-k][j] - mat_pre[i][j-k] + mat_pre[i-k][j-k];
                if (curr_sum <= threshold){
                    ans = std::max(k, ans);
                }
            }
        }
    }
    return ans;
}


// 矩阵区域和
vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
    vector<vector<int>> mat_prefit = matrix_prefix_sum(mat);
    vector<vector<int>> res(mat.size(), vector<int>(mat[0].size(), 0));
    int rows = mat.size();
    int cols = mat[0].size();
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int x1 = std::max(i-K, 0);
            int y1 = std::max(j-K, 0);
            int x2 = std::min(i+K+1, rows);
            int y2 = std::min(j+K+1, cols);
            int curr_sum = mat_prefit[x2][y2] - mat_prefit[x1][y2] - mat_prefit[x2][y1] + mat_prefit[x1][y1];
            res[i][j] = curr_sum;
        }
    }
    return res;
}

//零钱兑换
const unsigned int INF_MAX = 99999;
int less_time(vector<int>& coins, vector<int>& amount_store, int curr_acount){
    int res = INF_MAX;
    for (int i = 0; i < coins.size(); i++){
        if (curr_acount - coins[i] >= 0){
            if (amount_store[curr_acount - coins[i]] != -1){
                res = std::min(res, amount_store[curr_acount - coins[i]]);
            }
        }
    }
    return res;
}

int coinChange(vector<int>& coins, int amount) {
    vector<int> amount_store(amount+1, -1);
    amount_store[0] = 0;
    for (int i = 1; i <= amount; i++){
        int less_count = less_time(coins, amount_store, i);
        if (less_count == INF_MAX)
            amount_store[i] = -1;
        else
            amount_store[i] = less_count + 1;
    }
    return amount_store[amount];
}


// 最长上升子序列
// 1. dp[i] 定义为以nums[i]结尾的最长上升子序列
// 2. 状态转移：dp[i] = max(dp[i], dp[j] + 1) , if dp[j] < dp[i] for j in [0, i]
// 3. 返回dp[i]中最大的值
int lengthOfLIS(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    vector<int> dp(nums.size(), 1);
    int res  = 1;
    for (int i = 0; i < nums.size(); i++){
        for (int j = 0; j < i; j++){
            if (nums[j] < nums[i]){
                dp[i] = std::max(dp[i], dp[j]+1);
            }
        }
        if (dp[i] > res){
            res = dp[i];
        }
    }
    return res;
}

// 不同路径
int uniquePaths(int m, int n) {
    vector<vector<int>> path(m, vector<int>(n, 1));
    if (m == 1 || n == 1){
        return path[m-1][n-1];
    }
    for (int i = 1; i < m; i++){
        for (int j = 1; j < n; j++){
            path[i][j] = path[i-1][j] + path[i][j-1];
        }
    }
    return path[m-1][n-1];
}

// 最小路径和
int minPathSum(vector<vector<int>>& grid) {
    vector<vector<int>> path(grid.size(), vector<int>(grid[0].size(), 0));

    // 初始化
    path[0][0] = grid[0][0];
    for (int i = 1; i < grid[0].size(); i++){
        path[0][i] = grid[0][i] + path[0][i-1];
    }
    for (int j = 1; j < grid.size(); j++){
        path[j][0] = grid[j][0] + path[j-1][0];
    }

    for (int i = 1; i < grid.size(); i++){
        for (int j = 1; j < grid[0].size(); j++){
            path[i][j] = grid[i][j] + std::min(path[i-1][j], path[i][j-1]);
        }
    }
    return path[grid.size()-1][grid[0].size()-1];
}


// 编辑距离


// 最长流淌子数组（丑陋的代码）
int maxTurbulenceSize(vector<int>& A) {
    int num_size = A.size();
    if (num_size <= 1) return num_size;
    vector<int> res(num_size, 1);
    vector<int> flags(num_size, 0);
    for (int i = 1; i < num_size; i++){
        if (A[i] < A[i-1]){
            flags[i] = -1;
            continue;
        }
        if (A[i] > A[i-1]){
            flags[i] = 1;
        }else{
            flags[i] = 0;
        }
    }
    if (flags[1] != flags[0]) flags[0] = -flags[1];

    int results = 0;
    int curr_flag = flags[0];
    for (int i = 1; i < num_size; i++){
        if (flags[i] == 0){
            res[i] = 1;
            results = std::max(results, res[i]);
            continue;
        }
        if (flags[i] != curr_flag){
            res[i] = res[i-1] + 1;
            curr_flag = flags[i];
        }else{
            res[i] = 2;
            curr_flag = flags[i];
        }
        results = std::max(results, res[i]);
    }
    return results;
}


// 新21点-爱丽丝抽牌游戏
// 牌的范围[1, W]，得分少于K时，继续取牌，当停止取牌时，手上牌的总和小于等于N的概率
// 定义dp[i]，当前牌面为i时，爱丽丝获胜的概率，又已知，牌面最小值为0，最大值为 K-1+W
// 状态转移方程 dp[i] = (1.0/W) * (dp[i+1] + dp[i+2] + ... + dp[i+W])
// 求牌面为0时，获胜的概率
double new21Game(int N, int K, int W){
    vector<double> dp(K+W, 0);
    double s = 0;
    for (int i = K; i < K+W; i++){
        if (i > N)
            dp[i] = 0;
        else
            dp[i] = 1;
        s += dp[i];
    }
    for (int i = K-1; i > -1; i--){
        dp[i] = (1.0 / W) * s;
        s = s - dp[i+W] + dp[i];
    }
    return dp[0];
}

// 计算各个位数不同的数字个数-动态规划
// 1. 当n=0时，返回1，当n=1时，返回10
// 2. 当n=2时，第一位有9中选择，第二位（个位）有（0-9）10种选择，但是不能选与前一位相同的数字，故只有9种选择
// 3. 当n=3时，第一位有9种，第二位有9种，第三位有8种。。。
int countNumbersWithUniqueDigits(int n){
    if (n == 0){return 1;}
    if (n == 1){return 10;}
    vector<int> dp(n+1, 0);
    dp[0] = 1;
    dp[1] = 10;
    int sum = 81;
    int count = 9;
    for (int i = 2; i <= n; i++){
        dp[i] = sum + dp[i-1];
        sum = sum * (--count);
    }
    return dp[n];
}


// 买卖股票的最佳时机-含手续费


// 打家劫舍
// 1. 对于一个房屋，有两种选择，偷或者不偷。定义状态dp[i] -> 当偷到第i家时候，能获得的最大价值
// 2. 状态转移 dp[i] = max(dp[i-2] + nums[i], dp[i-1]) -> 如果选择偷，则价值为 dp[i-2] + nums[i]，不偷价值为dp[i-1]
// 3. 初始化状态, dp[0] = nums[0], dp[1] = max(nums[0], nums[1])
int rob(vector<int>& nums) {
    int size = nums.size();
    if (size == 0) return 0;
    if (size == 1) return nums[0];
    if (size == 2) return std::max(nums[0], nums[1]);
    vector<int> dp(size, 0);
    dp[0] = nums[0];
    dp[1] = std::max(nums[1], nums[0]);
    for (int i = 2; i < size; i++){
        dp[i] = std::max(nums[i] + dp[i-2], dp[i-1]);
    }
    return dp[size-1];
}

// 打家劫舍-2 房子是环形排列的
// 1. 不偷第一个房子的情况，结果1
// 2. 不偷最后一个房子的情况， 结果2
// 3. max()
int robCore(vector<int>& nums, int start, int end){
    int size = end-start+1;
    if (size == 0) return 0;
    if (size == 1) return nums[start];
    if (size == 2) return std::max(nums[start], nums[start+1]);

    vector<int> dp(size, 0);
    dp[0] = nums[start];
    dp[1] = std::max(nums[start], nums[start+1]);
    for (int i = start + 2; i <= end; i++){
        dp[i-start] = std::max(nums[i] + dp[i-start-2], dp[i-start-1]);
    }
    return dp[end-start];
}

int rob2(vector<int>& nums) {
    int size = nums.size();
    if (size == 0) return 0;
    if (size == 1) return nums[0];
    if (size == 2) return std::max(nums[0], nums[1]);
    int a1 = robCore(nums, 0, size-2);
    int a2 = robCore(nums, 1, size-1);
    return std::max(a1, a2);
}


// 目标和-动态规划
// 题目要求得到的结果是方法的个数，根据dp问题的经验，题目要求什么，就将dp的含义定义成什么
// 根据0-1背包问题的经验，dp[i][j] 表示前i个数组中的数字其目标和为j的方法数
// i, j 范围， i -> [0, nums.size()-1], j -> [-sum(nums), sum(nums)]
// 状态转移 dp[i][j] = dp[i-1][j-nums[i]] + dp[i-1][j+nums[i]]
// 初始化 dp[0][sum-nums[0]] = 1, dp[0][sum+nums[0]] = 1, "if nums[0] == 0, dp[0][sum] = 2"
int findTargetSumWays(vector<int>& nums, int S){
    int numSize = nums.size();
    int sum = 0;
    for (int i = 0; i < numSize; i++){
        sum += nums[i];
    }
    if (sum < S) return 0;
    vector<vector<int>> dp(numSize, vector<int>(2*sum+1, 0));
    // 初始化
    if (nums[0] == 0){
        dp[0][sum] = 2;
    }else{
        dp[0][sum-nums[0]] = 1;
        dp[0][sum+nums[0]] = 1;
    }
    for (int i = 1; i < numSize; i++){
        for (int j = 0; j < sum*2+1; j++){
            int l = std::max(0, j-nums[i]);
            int r = std::min(2*sum, j+nums[i]);
            dp[i][j] = dp[i-1][l] + dp[i-1][r];
        }
    }
    return dp[numSize-1][sum+S];
}


// 分割等和子集
// 思考：将一个数组分割成两部分，使得两部分的和相等，如果可以的话，那么和一定是数组中所有元素和/2，如果是奇数，返回False
// 0-1背包问题
// 状态定义：dp[i][j] -> 前i个数字中，是否有子集和为j
// 状态转移：结果至少是 dp[i-1][j]，表示不用当前nums[i]，前i-1个数字中是否有子集和等于j
// 如果nums[i] == j，则 dp[i][j]=True
// dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]]
// 状态初始化：对第一行，dp[0][nums[0]] = true （背包容量恰好等于第一个数字）
bool canPartition(vector<int>& nums){
    int numSize = nums.size();
    if (numSize < 2) return false;
    int sum = 0;
    for (int num : nums){
        sum += num;
    }
    if (sum & 1) return false;
    int target = sum >> 1;
    vector<vector<bool>> dp(numSize, vector<bool>(target+1, false));
    if (nums[0] < target){
        dp[0][nums[0]] = true;
    }
    for (int i = 1; i < numSize; i++){
        for (int j = 0; j <= target; j++){
            if (nums[i] == j){
                dp[i][j] = true;
                continue;
            }
            int l = std::max(0, j-nums[i]);
            dp[i][j] = dp[i-1][j] || dp[i-1][l];
        }
    }
    return dp[numSize-1][target];
}


// 填充书架
// 遍历每一本书，将该本书与前面的若干本书进行组合，如组合后书的宽度还是小于书架的宽度，说明组合有效
// 有效组合后该层书架中书的高度为最高的那本书的高度
// dp[i] = min(dp[i], dp[j-1]+h) // dp[j-1]表明前一本书所在书架的高度
int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
    const unsigned int MAX_INF = 999999;
    int books_size = books.size();
    vector<int> dp(books_size+1, 0);
    for (int i = 1; i <= books_size; i++){
        int max_h = 0;
        int curr_width = 0;
        for (int j = i; i > 0; i--){
            curr_width += books[j-1][0];
            if (curr_width > shelf_width)
                break;
            max_h = std::max(books[j-1][1], max_h);
            dp[i] = std::min(dp[i], dp[j-1]+max_h);
        }
    }
    return dp[books_size];
}


// 回文子串的个数
// dp[i][j] 子串s[i:j]是否为回文串，注j > i
// dp[i][j] == true if i == j
// dp[i][j] == true if s[i] == s[j] && j-i==1
// dp[i][j] == true if dp[i+1][j-1] == true && s[i] == s[j]
// [注] 遍历dp[i][j]时，需要保证dp[i+1][j-1]被计算过
int countSubstrings(string s){
    int strSize = s.length();
    int res = 0;
    vector<vector<bool>> dp(strSize, vector<bool>(strSize, false));
    for (int i = strSize - 1; i >= 0; i--){
        for (int j = i; j < strSize; j++){
            if (i == j){
                dp[i][j] = true;
            }else{
                if (j - i == 1 && s[i] == s[j]){
                    dp[i][j] = true;
                }else{
                    if (s[i] == s[j] && dp[i+1][j-1] == true){
                        dp[i][j] = true;
                    }
                }
            }
            if (dp[i][j]){
                res++;
            }
        }
    }
    return res;
}


int main(){
    string s = "aaa";
    cout << countSubstrings(s);
}








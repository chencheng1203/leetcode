#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <sstream>
#include <math.h>
#include "utils.h"

using std::cout;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


// 颜色分类
// 1. 双指针， p0表示前 0-p0 都是 0， p2 表示 p2-end 都是 2
// 2. 当遍历到nums[i]时，若 nums[i]==0 与nums[p0]交换 p0++
// 3. 当遍历到nums[i] == 2 时，与nums[p2]交换, p2--，但是交换后的nums[i]仍然可能是2，故需要再次交换，直到不为2为止
void swap(int* num1, int* num2){
    int temp  = *(num1);
    *(num1) = *(num2);
    *(num2) = temp;
}
void sortColors(vector<int>& nums){
    int size = nums.size();
    int p0 = 0, p2 = size-1;
    for (int i = 0; i < size; i++){
        while (nums[i] == 2 && i <= p2){
            swap(&(nums[i]), &(nums[p2]));
            p2--;
        }
        if (nums[i] == 0){
            swap(&(nums[i]), &(nums[p0]));
            p0++;
        }
    }
}


// 最后一块石头的重量
int lastStoneWeight(vector<int>& stones) {
    int size = stones.size();
    if (size == 0) return 0;
    if (size == 1) return stones[0];
    // 寻找最大的两个数并且在vector中将其删除
    while(stones.size() >= 2){
        int first_max_num = 0, second_max_num = 0;
        vector<int>::iterator p;
        for (auto i = stones.begin(); i != stones.end(); i++){
            if (*(i) >= first_max_num){
                first_max_num = *(i);
                p = i;
            }
        }
        stones.erase(p);
        for (auto i = stones.begin(); i != stones.end(); i++){
            if (*(i) >= second_max_num){
                second_max_num = *(i);
                p = i;
            }
        }
        stones.erase(p);
        int diff = std::abs(first_max_num - second_max_num);
        stones.push_back(diff);
    }
    return stones[0];
}

// 查找常用字符串
int charIsInStr(char ch, string s, vector<bool>& used){
    for (int i = 0; i < s.length(); i++)
        if (s[i] == ch && !used[i]){
            used[i] = true;
            return i;
        }
    return -1;
}
vector<string> commonChars(vector<string>& A) {
    string first_str = A.front();
    A.erase(A.begin());
    vector<string> res;
    while(A.size()){
        string second_str = A.front();
        A.erase(A.begin());
        vector<bool> used(second_str.length(), 0);
        for (int i = 0; i < first_str.length(); i++){
            int flag = charIsInStr(first_str[i], second_str, used);
            if (flag != -1){
                string tmp_s = "";
                tmp_s += first_str[i];
                res.push_back(tmp_s);
            }
        }
        if (!A.size()) return res;
        // 构建first_str
        string A_temp = "";
        for (int i = 0; i < res.size(); i++){
            A_temp += res[i];
        }
        first_str = A_temp;
        vector<string>().swap(res); // 清空res
    }
    return res;
}


// 三个数的最大乘积
int maximumProduct(vector<int>& nums){
    int size = nums.size();
    std::sort(nums.begin(), nums.end());
    int p = 0;
    if (nums[p] >= 0){
        return nums[size - 1] * nums[size - 2] * nums[size - 3];
    }else{
        long s1 = nums[size - 1] * nums[size - 2] * nums[size - 3];
        long s2 = nums[0] * nums[1] * nums[size - 1];
        return std::max(s1, s2);
    }
}

// 比较含退格的字符串
string match(string s){
    string res = "";
    for (char ch : s){
        if (ch != '#'){
            res.push_back(ch);
        }else{
            if (res.length()){
                res.pop_back();
            }
        }
    }
    return res;
}
bool backspaceCompare(string S, string T){
    return match(S) == match(T);
}

// 长键按入-双指针
bool isLongPressedName(string name, string typed) {
    int name_size = name.length();
    int typed_size = typed.length();
    int p1 = 0, p2 = 0;
    char pre_ch = name[p1];
    while(p1 != name_size && p2 != typed_size){
        if(name[p1] == typed[p2]){
            pre_ch = name[p1];
            p1++;
            p2++;
            continue;
        }
        if (typed[p2] == pre_ch){
            p2++;
            continue;
        }
        if (typed[p2] != pre_ch && typed[p2] != name[p1]){
            return false;
        }
    }
    if (p1 == name_size && p2 == typed_size)
        return true;
    if (p1 == name_size){
        for (int i = p2; i < typed_size; i++){
            if (typed[i] != pre_ch)
                return false;
        }
        return true;
    }
    return false;
}


// 划分字母区间
vector<int> partitionLabels(string S) {
    vector<int> res;
    int last_pos[26];
    memset(last_pos, -1, sizeof(last_pos));
    for (int i = 0; i < S.size(); i++){
        last_pos[S[i] - 'a'] = i;  // 当前字符最后出现的位置
    }
    int start = 0, end = 0;
    for (int i = 0; i < S.size(); i++){
        end = std::max(end, last_pos[S[i]-'a']);  // 贪心，每次都找最大的位置
        if (i == end){
            res.push_back(i - start + 1);
            start = i + 1;
        }
    }
    return res;
}

// 数组游戏赢家
int getWinner(vector<int>& arr, int k) {
    int arr_size = arr.size();
    int min_num = std::min(arr[0], arr[1]);
    arr.push_back(min_num);
    if (min_num == arr[0]){
        arr.erase(arr.begin());
    }else{
        swap(&arr[0], &arr[1]);
        arr.erase(arr.begin());
    }
    int pre_win_num = arr[0];
    int continus_win = 1;
    int curr_win_num = pre_win_num;
    while(continus_win != k){
        int min_num = std::min(arr[0], arr[1]);
        curr_win_num = std::max(arr[0], arr[1]);
        arr.push_back(min_num);
        if (min_num == arr[0]){
            arr.erase(arr.begin());
        }else{
            swap(&arr[0], &arr[1]);
            arr.erase(arr.begin());
        }
        if (curr_win_num == pre_win_num){
            continus_win++;
        }else{
            pre_win_num = curr_win_num;
            continus_win = 1;
        }
    }
    return curr_win_num;
}

// 1438. 绝对差不超过限制的最长连续子数组
int longestSubarray(vector<int>& nums, int limit) {

}

// 独一无二的出现次数
bool uniqueOccurrences(vector<int>& arr) {
    vector<int> curr_counts(2001, 0);
    vector<bool> if_counts(999, 0);
    for (int i = 0; i < arr.size(); i++){
        curr_counts[1000+arr[i]]++;
    }
    for (int i = 0; i < curr_counts.size(); i++){
        int curr_count = curr_counts[i];
        if (curr_count == 0) continue;
        if (!if_counts[curr_count])
            if_counts[curr_count] = true;
        else
            return false;
    }
    return true;
}

// 岛屿的周长
int islandPerimeter(vector<vector<int>>& grid) {
    int cirle_len = 0;
    int height = grid.size();
    int width = grid[0].size();
    // top
    for (int i = 0; i < width; i++){
        if (grid[0][i]){
            cirle_len++;
            if (i != 0 && !grid[0][i-1]){
                cirle_len++;
            }
            if (i != width-1 && !grid[0][i+1]){
                cirle_len++;
            }
        }
    }
    // right
    for (int i = 0; i < height; i++){
        if (grid[i][width-1]){
            cirle_len++;
            if (i != 0 && !grid[i-1][width-1]){
                cirle_len++;
            }
            if (i != height-1 && !grid[i+1][width-1]){
                cirle_len++;
            }
        }
    }
    // bottom
    for (int i = 0; i < width; i++){
        if (grid[height-1][i]){
            cirle_len++;
            if (i != 0 && !grid[height-1][i-1]){
                cirle_len++;
            }
            if (i != width-1 && !grid[height-1][i+1]){
                cirle_len++;
            }
        }
    }
    // left
    for (int i = 0; i < height; i++){
        if (grid[i][0]){
            cirle_len++;
            if (i != 0 && !grid[i-1][0]){
                cirle_len++;
            }
            if (i != height-1 && !grid[i+1][0]){
                cirle_len++;
            }
        }
    }
    cout << cirle_len;
    for (int i = 1; i < height-1; i++){
        for (int j = 1; j < width-1; j++){
            if (grid[i][j]){
                // top
                if (!grid[i-1][j]){
                    cirle_len++;
                }
                // right
                if (!grid[i][j+1]){
                    cirle_len++;
                }
                // bottom
                if (!grid[i+1][j]){
                    cirle_len++;
                }
                // left
                if (!grid[i][j-1]){
                    cirle_len++;
                }
            }
        }
    }
    return cirle_len;
}

bool validMountainArray(vector<int>& A) {
    int size = A.size();
    if (size < 3) return false;
    int increase_index = 1;
    int down_index = increase_index;
    for (; A[increase_index] > A[increase_index-1] && increase_index < size; increase_index++);
    down_index = increase_index;
    for (; down_index < size; down_index++){
        if (A[down_index] >= A[down_index-1]){
            return false;
        }
    }
    return true;
}


// 973. 最接近原点的 K 个点
vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    std::sort(points.begin(), points.end(),
              [](vector<int>& v1, vector<int>& v2){return (v1[0] * v1[0] + v1[1] * v1[1]) < (v2[0] * v2[0] + v2[1] * v2[1]);});
    return {points.begin(), points.begin() + K};
}

// 优先队列-最小的K个数
vector<int> getLeastNumbers(vector<int>& arr, int k){
    vector<int> res;
    std::priority_queue<int> q;
    for (int i = 0; i < k; i++){
        q.push(arr[i]);
    }
    for (int i = k; i < arr.size(); i++){
        if (q.top() > arr[i]){
            q.pop();
            q.emplace(arr[i]);
        }
    }
    for (int i = 0; i < k; i++){
        res.push_back(q.top());
        q.pop();
    }
    return res;
}

// 数组中重复的数字
// 给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次
// 思路：不使用额外的空间，如何标记该数字被访问过？
// 正在被访问的数字对应的索引为，没次访问后，将其索引位置的数字标为-nums[i]
// 若索引位置为“-”，则说明已经被访问过了
vector<int> findDuplicates(vector<int>& nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); i++){
        if (nums[abs(nums[i]) - 1] < 0){
            res.push_back(abs(nums[i]));
        }else{
            nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];
        }
    }
    return res;
}


// 134. 加油站
bool if_index_i_canCompleteCircuit(vector<int>& gas, vector<int>& cost, int i) {
    int curr_index = 0;
    int last_index = 0;
    int curr_gas = gas[i];
    for (int k = 1; k <= gas.size(); k++){
        curr_index = (k + i) % gas.size();
        last_index = (k + i - 1) % gas.size();
        if (curr_gas < cost[last_index])
            return false;
        curr_gas = curr_gas - cost[last_index] + gas[curr_index];
    }
    return true;
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    for (int i = 0; i < gas.size(); i++){
        if (gas[i] < cost[i]){
            continue;
        }else{
            if (if_index_i_canCompleteCircuit(gas, cost, i)){
                return i;
            }
        }
    }
    return -1;
}

// 283 移动零
void moveZeroes(vector<int>& nums) {
    vector<int>::iterator p = nums.begin();
    int count = 0;
    while(count != nums.size()){
        if (*p == 0){
            nums.erase(p);
            nums.push_back(0);
            count++;
        }else{
            p++;
            count++;
        }
    }
}

// 丑数数列
int getKthMagicNumber(int k) {
    int p3 = 0, p5 = 0, p7 = 0;
    vector<int> dp(k, 0);
    dp[0] = 1;
    for (int i = 1; i < k; i++){
        int temp = std::min(std::min(dp[p3] * 3, dp[p5] * 5), dp[p7] * 7);
        dp[i] = temp;
        if (temp == dp[p3] * 3) p3++;
        if (temp == dp[p5] * 5) p5++;
        if (temp == dp[p7] * 7) p7++;
    }
    return dp[k - 1];
}

// 最小K个数
// 找出数组中最小的k个数。以任意顺序返回这k个数均可
// 思路：使用最大堆排序，优先队列
vector<int> smallestK(vector<int>& arr, int k) {
    vector<int> res;
    int size = arr.size();
    if (size < 1 || k == 0 || k > size) return res;
    std::priority_queue<int> p_queue;
    for (int i = 0; i < k; i++){
        p_queue.push(arr[i]);
    }
    for (int i = k; i < size; i++){
        if (p_queue.top() > arr[i]){
            p_queue.pop();
            p_queue.push(arr[i]);
        }
    }
    while (!p_queue.empty()){
        res.push_back(p_queue.top());
        p_queue.pop();
    }
    return res;
}

// 杨辉三角
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res(numRows);
    if (numRows < 1) return res;
    res[0].push_back(1);
    int left_val = 1;
    int right_val = 1;
    for (int i = 1; i < numRows; i++){
        for (int j = 0; j < i; j++){
            if (j == 0 || j == i - 1)
                res[i][j] = 1;
            else{
                left_val = res[i - 1][j-1];
                right_val = res[i - 1][j];
                res[i][j] = left_val + right_val;
            }
        }
    }
    return res;
}

int wiggleMaxLength(vector<int>& nums) {

}

// 只出现1次的数字，其余的出现3次
int singleNumber(vector<int>& nums) {
    int num_size =  nums.size();
    vector<int> bit_counts(32, 0);
    for (int i = 0; i < num_size; i++){
        if (nums[i] < 0){
            nums[i] = ~nums[i] + 1;
        }
        for (int j = 0; j < 32; j++){
            int bit_flag = ((nums[i] >> j) & 1);
            bit_counts[j] += bit_flag;
        }
    }
    for (int i = 0; i < 32; i++){
        bit_counts[i] %= 3;
    }
    int res = 0;
    for (int i = 0; i < 31; i++){
        if (bit_counts[i] == 1)
            res += (std::pow(2, i));
    }
    if (bit_counts[31] == 1)
        res = -res;
    return res;
}

// 二分查找-返回左边界值
int binary_search_left_bound(vector<int>& nums, int target){
    int left = 0, right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if (nums[mid] < target){
            left = mid + 1;
        }
        if(nums[mid] > target){
            right = mid - 1;
        }
        if (nums[mid] == target){
            right = mid - 1;
        }
    }
    return left;
}

// 二分查找-返回右边界值
int binary_search_right_bound(vector<int>& nums, int target){
    int left = 0, right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if (nums[mid] < target){
            left = mid + 1;
        }
        if(nums[mid] > target){
            right = mid - 1;
        }
        if (nums[mid] == target){
            left = mid + 1;
        }
    }
    return right;
}

// 275. H指数
int hIndex(vector<int>& citations) {
    int left = citations.size();
    int i = 0;
    while(citations[i] <= left){
        i++;
        left--;
    }
    return citations[--i];
}

// 有序数组中唯一的元素
int singleNonDuplicate(vector<int>& nums) {
    int p1 = 0, p2 = nums.size() - 1;
    int res = 0;
    bool flag = true;
    while(p1 < p2){
        if (flag){
            res += (nums[p1] + nums[p2]);
            p1++;
            p2--;
        }
        if (!flag){
            res -= (nums[p1] + nums[p2]);
            p1++;
            p2--;
        }
        flag = !flag;
    }
    if (flag) res += nums[p1];
    else res -= nums[p1];
    return res;
}

// 排序矩阵中查找元素
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    if (rows == 0) return false;
    int cols = matrix[0].size();
    int row = 0;
    int col = cols - 1;
    while(row < rows && col >= 0){
        if (matrix[row][col] == target)
            return true;
        if (matrix[row][col] > target){
            col--;
            continue;
        }
        if (matrix[row][col] < target)
            row++;
    }
    return false;
}


//int main() {
//    vector<vector<int>> v = {{-5}};
//    bool res = searchMatrix(v, -19);
//    cout << res;
//}


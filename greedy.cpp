#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <math.h>
#include <algorithm>

using std::cout;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 任务调度器

// 翻转矩阵的最高得分
// 1. 若每一行的第一个元素不为1，则翻转这一行，确保第一列的所有元素都为1
// 2. 对于除了每一列的元素，若该列中0的个数大于1的个数，则翻转这一列
int matrixScore(vector<vector<int>>& A){
    int rows = A.size(), cols = A[0].size();
    // 第一步
    for (int i = 0; i < rows; i++){
        if (A[i][0] == 1) continue;
        else{
            for (int j = 0; j < cols; j++){
                A[i][j] = 1 - A[i][j];
            }
        }
    }
    // 第二步
    for (int j = 1; j < cols; j++){
        // 统计1的数量
        int one_counts = 0;
        int zero_counts = 0;
        for (int i = 0; i < rows; i++){
            if (A[i][j] == 1)
                one_counts++;
            else
                zero_counts++;
        }
        // 若1的数量小于0的数量，则翻转
        if (one_counts < zero_counts){
            for (int k = 0; k < rows; k++){
                A[k][j] = 1 - A[k][j];
            }
        }
    }
    // 统计
    int sum = 0;
    for (int i = 0; i < rows; i++){
        int row_sum = 0;
        for (int j = 0; j < cols; j++){
            if (A[i][j] == 1)
                row_sum += std::pow(2, cols - j - 1);
        }
    }
    return sum;
}

// 分发糖果
int candy(vector<int>& ratings) {
    int num_size = ratings.size();
    vector<int> dp(num_size, 1);
    int res = 0;
    for (int i = 1; i < num_size; i++){
        if (ratings[i] < ratings[i - 1] && dp[i - 1] == 1){
            // 将当前位置 置1
            dp[i] = 1;
            dp[i - 1] += 1;
            int j = i - 2;
            for (; j >= 0 && dp[j] != 1; j--){
                dp[j] += 1;
            }
        }
        if (ratings[i] <= ratings[i - 1] && dp[i - 1] > 1){
            dp[i] = 1;
        }
        if (ratings[i] > ratings[i - 1]){
            dp[i] = dp[i - 1] + 1;
        }

    }
    for (int num : dp){
        cout << num << ' ';
        res += num;
    }
    cout << endl;
    return res;
}


/*int main(){
    vector<int> v = {29,51,87,87,72,12};
    int sum = candy(v);
    cout << sum;
}*/


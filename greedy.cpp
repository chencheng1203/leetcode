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

/*int main(){
    vector<vector<int>> v = {{0,0,1,1},{1,0,1,0},{1,1,0,0}};
    int sum = matrixScore(v);
    cout << sum;
}*/


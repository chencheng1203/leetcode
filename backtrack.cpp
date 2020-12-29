#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>
#include "utils.h"

using std::cout;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 函数声明
// void print_2D_vector(const vector<vector<int>>& matrix);

// 全排列
// 深度优先遍历，首先画出树形图
void dfs(vector<int>& nums, int size, int dep, vector<bool>& used, vector<int>& path, vector<vector<int>>& res){
    if (dep == size){
        res.push_back(path);
        return;
    }
    for (int i = 0; i < size; i++){
        if (!used[i]){
            path.push_back(nums[i]);
            used[i] = true;
            dfs(nums, size, dep+1, used, path, res);
            used[i] = false;
            path.pop_back();
        }
    }
}
vector<vector<int>> permute(vector<int>& nums){
    int size = nums.size();
    vector<bool> used(size, 0);
    vector<int> path;
    vector<vector<int>> res;
    dfs(nums, size, 0, used, path, res);
    print_2D_vector(res);
    return res;
}

// 矩阵中的路径
bool existPathCore(vector<vector<char>>& board, string& word, int rows, int cols, int curr_x, int curr_y,
                   vector<vector<bool>>& used, int curr_inx){
    if (curr_inx == word.size()){
        return true;
    }
    bool flag = 0;
    if (curr_x < rows && curr_x >= 0 && curr_y < cols && curr_y >= 0 &&
        board[curr_x][curr_y] == word[curr_inx] && !used[curr_x][curr_y]){
        used[curr_x][curr_y] = true;
        // curr_inx++;
        flag = existPathCore(board, word, rows, cols, curr_x, curr_y-1, used, curr_inx+1)||
               existPathCore(board, word, rows, cols, curr_x, curr_y+1, used, curr_inx+1)||
               existPathCore(board, word, rows, cols, curr_x-1, curr_y, used, curr_inx+1)||
               existPathCore(board, word, rows, cols, curr_x+1, curr_y, used, curr_inx+1);
        if (!flag){
            used[curr_x][curr_y] = false;
        }
    }
    return flag;
}
bool exist(vector<vector<char>>& board, string word){
    int rows = board.size();
    int cols = board[0].size();
    vector<vector<bool>> used(rows, vector<bool>(cols, false));
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (existPathCore(board, word, rows, cols, i, j, used, 0)){
                return true;
            }
        }
    }
    return false;
}

// 三角形最小路径和
void minimumTotalCore(vector<vector<int>>& triangle, int dep, int curr_dep, int curr_idx, int sum, int& res){
    if (curr_dep == dep){
        res = std::min(sum, res);
        return;
    }
    for (int i = curr_idx; i < curr_idx+2; i++){
        if (curr_idx == 0 && i == 1 && curr_dep == 0) return;
        int curr_node = triangle[curr_dep][i];
        sum += curr_node;
        minimumTotalCore(triangle, dep, curr_dep+1, i, sum, res);
        sum -= curr_node;
    }
}
int minimumTotal(vector<vector<int>>& triangle) {
    if (triangle.size() == 0) return 0;
    if (triangle.size() == 1) return triangle[0][0];
    const int MAX_INF = 999999;
    int res = MAX_INF;
    minimumTotalCore(triangle, triangle.size(), 0, 0, 0, res);
    return res;
}

// 将数组拆分成斐波那契数列
// 给定一个数字字符串 S，比如 S = "123456579"，我们可以将它分成斐波那契式的序列 [123, 456, 579]

// N皇后
// board[row][col]中放置皇后是否合法
bool NQueueIsValid(vector<string>& board, int row, int col){
    int cols = board.size();
    // 判断在该列上放置皇后是否合法
    for (int i = 0; i < row; i++){
        if (board[i][col] == 'Q')
            return false;
    }
    // 判断右上角放置皇后是否合法
    for (int i = row - 1, j = col + 1; i >= 0 &&  j < cols; i--, j++){
        if (board[i][j] == 'Q')
            return false;
    }
    // 判断左上角放置皇后是否合法
    for (int i = row - 1, j = col - 1; i >= 0 && j >=0; i--, j--){
        if (board[i][j] == 'Q')
            return false;
    }
    return true;
}
void NQueue_dfs(vector<string> board, int row, vector<vector<string>>& res){
    if (row == board.size()){
        res.push_back(board);
        return;
    }
    // 在该行的每一列上尝试放置皇后
    int n = board[row].size();
    for (int i = 0; i < n; i++){
        // 若不合法，则继续判断下一列
        if (!NQueueIsValid(board, row, i))
            continue;
        // 若是合法的，则填充该列[进行选择]，并且进入下一行
        board[row][i] = 'Q';
        NQueue_dfs(board, row+1, res);
        // 撤销选择
        board[row][i] = '.';
    }
}

vector<vector<string>> solveNQueens(int n){
    vector<string> board(n, string(n, '.'));
    vector<vector<string>> res;
    NQueue_dfs(board, 0, res);
    return res;
}


// 0-1矩阵
void updateMatrix_dfs(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int& steps, int curr_step, int rows, int cols, int i, int j){
    if (i >= 0 && i < rows && j >= 0 && j < cols && !visited[i][j]){
        if (matrix[i][j] == 0){
            steps = std::min(steps, curr_step);
            return;
        }
        curr_step++;
        visited[i][j] = true;
        updateMatrix_dfs(matrix, visited, steps, curr_step, rows, cols, i+1, j);
        updateMatrix_dfs(matrix, visited, steps, curr_step, rows, cols, i-1, j);
        updateMatrix_dfs(matrix, visited, steps, curr_step, rows, cols, i, j-1);
        updateMatrix_dfs(matrix, visited, steps, curr_step, rows, cols, i, j+1);
        visited[i][j] = false;
    }
}
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    vector<vector<int>> res(rows, vector<int>(cols, 0));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int steps = 9999;
            updateMatrix_dfs(matrix, visited, steps, 0, rows, cols, i, j);
            res[i][j] = steps;
        }
    }
    return res;
}

/*int main(){
    vector<vector<int>> matrix = {{0,0,0},
                                  {0,1,0},
                                  {1,1,1}};
    vector<vector<int>> res = updateMatrix(matrix);
    print_2D_vector(res);
}*/

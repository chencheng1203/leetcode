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

// 2D-vector打印
void print_2D_vector(const vector<vector<int>>& matrix){
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

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


int main(){
    vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    string S = "ABCCED";
    cout << exist(board, S);
}

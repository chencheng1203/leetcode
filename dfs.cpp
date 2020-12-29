#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include "utils.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 水域的大小
void pondSizes_dfs(vector<vector<int>>& land, int& size, int rows, int cols, int i, int j, vector<vector<bool>>& visited, vector<int>& res){
    if (i >= 0 && i < rows && j >= 0 && j < cols && !visited[i][j]){
        if (land[i][j] == 0){
            visited[i][j] = true;
            // 搜索
            size++;
            pondSizes_dfs(land, size, rows, cols, i + 1, j, visited, res);
            pondSizes_dfs(land, size, rows, cols, i - 1, j, visited, res);
            pondSizes_dfs(land, size, rows, cols, i, j + 1, visited, res);
            pondSizes_dfs(land, size, rows, cols, i, j - 1, visited, res);
            pondSizes_dfs(land, size, rows, cols, i - 1, j - 1, visited, res);
            pondSizes_dfs(land, size, rows, cols, i + 1, j - 1, visited, res);
            pondSizes_dfs(land, size, rows, cols, i + 1, j + 1, visited, res);
            pondSizes_dfs(land, size, rows, cols, i + 1, j - 1, visited, res);
        }
    }
}

std::vector<int> pondSizes(vector<vector<int>>& land) {
    int rows = land.size();
    int cols = land[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    std::vector<int> res;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int size = 0;
            pondSizes_dfs(land, size, rows, cols, i, j, visited, res);
            res.push_back(size);
            size = 0;
        }
    }
    return res;
}


/*int main(){
    vector<vector<int>> land = {
            {0, 2, 1, 0},
            {0, 1, 0, 1},
            {1, 1, 0, 1},
            {0, 1, 0, 1}
    };
    std::vector<int> res = pondSizes(land);

    for (int num : res){
        cout << num << ' ';
    }
}*/


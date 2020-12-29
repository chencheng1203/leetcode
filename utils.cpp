#ifndef LEETCODE_CLASSIFY_UTILS_H
#define LEETCODE_CLASSIFY_UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>
# include "utils.h"

using std::cout;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 交换元素
void swap(int& num1, int& num2){
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

// 1D-vectordayin
void print_1D_vector(const vector<int>& vec){
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << ' ';
    }
}

// 2D-vector打印
void print_2D_vector(const vector<vector<int>>& matrix){
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}


#endif //LEETCODE_CLASSIFY_UTILS_H



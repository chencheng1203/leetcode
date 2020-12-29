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
//void swap(int& num1, int& num2);
//void print_1D_vector(const vector<int>& vec);
//void print_2D_vector(const vector<vector<int>>& matrix);

// 快速排序
void quick_sort(vector<int>& nums, int start, int end){
    if (start >= end)
        return;
    int base = nums[end];
    int index = start;
    for (int i = start; i < end; i++){
        if (nums[i] < base){
            swap(nums[i], nums[index]);
            index++;
        }
    }
    swap(nums[end], nums[index]);
    quick_sort(nums, start, index - 1);
    quick_sort(nums, index + 1, end);
}

// 插入排序
void insert_sort(vector<int>& nums){
    int size = nums.size();
    for (int i = 1; i < size; i++){
        int curr_num = nums[i];
        int j = i - 1;
        for (; j >= 0 && nums[j] > curr_num; j--){
            nums[j+1] = nums[j];
        }
        nums[j + 1] = curr_num;
    }
}

// 冒泡排序
void bubbleSort(vector<int>& nums){
    int num_size = nums.size();
    for (int i = 0; i < num_size; i++){
        for (int j = 0; j < num_size - i - 1; j++){
            if (nums[j] >= nums[j + 1]){
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

// 归并排序
void merge(vector<int>& nums, int left, int mid, int right){
    int left_size = mid - left + 1;
    int right_size = right - mid;
    vector<int> left_part(left_size, 0);
    for (int i = 0; i < left_size; i++){
        left_part[i] = nums[i + left];
    }
    vector<int> right_part(right_size, 0);
    for (int i = 0; i < right_size; i++){
        right_part[i] = nums[i + mid + 1];
    }
    int p1 = 0, p2 = 0, k = left;
    while(p1 < left_size && p2 < right_size){
        if (left_part[p1] <= right_part[p2]){
            nums[k] = left_part[p1];
            p1++;
        }else{
            nums[k] = right_part[p2];
            p2++;
        }
        k++;
    }
    while(p1 < left_size){
        nums[k] = left_part[p1];
        p1++;
        k++;
    }
    while(p2 < right_size){
        nums[k] = right_part[p2];
        p2++;
        k++;
    }
}

void merge_sort(vector<int>& nums, int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        merge_sort(nums, left, mid);
        merge_sort(nums, mid+1, right);
        merge(nums, left, mid, right);
    }
}


/*int main(){
    vector<int> nums = {3, 4, 2, 6, 7, 5, 1, 3};
    merge_sort(nums, 0, nums.size()-1);
    print_1D_vector(nums);
}*/

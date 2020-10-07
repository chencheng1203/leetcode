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

/*int main(){
    vector<int> nums = {10,4,2,10};
    int res = lastStoneWeight(nums);
    cout << res;
}*/


#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>
#include <memory.h>

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


/*int main() {
    string S = "ababcbacadefegdehijhklij";
    vector<int> res = partitionLabels(S);
    cout << ' ' << endl;
}*/


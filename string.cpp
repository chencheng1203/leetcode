#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>
#include <math.h>
#include <memory.h>
#include "utils.h"

using std::cout;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 翻转字符串
string reverseWords(string s) {
    ;
}

// 最小覆盖子串
bool is_all_include(std::map<char, int>& char_hash, std::map<char, int>& satisfied){
    for (std::pair<char, int> hash_pair : char_hash){
        if (hash_pair.second < satisfied[hash_pair.first]){
            return false;
        }
    }
    return true;
}
string minWindow(string s, string t){
    // 创建hash映射
    std::map<char, int> char_hash;
    std::map<char, int> satisfied;
    for (int i = 0; i < t.size(); i++){
        char_hash[t[i]] = 0;
        satisfied[t[i]]++;
    }
    int p1 = 0, p2 = 0;
    string Mask = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    string res = Mask;
    while(p2 <= s.size()) {
        // 判断hash中是否包含所有的字符
        bool include_all = is_all_include(char_hash, satisfied);
        if (!include_all){
            if (char_hash.count(s[p2]))
                char_hash[s[p2]]++;
            p2++;
        }else{
            while(is_all_include(char_hash, satisfied)){
                string curr_str = s.substr(p1, p2 - p1);
                res = (curr_str.size() < res.size() ? curr_str : res);
                if (char_hash.count(s[p1]))
                    char_hash[s[p1]]--;
                p1++;
            }
        }
    }
    return res == Mask ? "" : res;
}

// 双指针滑动窗口方法使用套路
/*int fuction(){
 *  定义hash，一般包含两个，分别是需要满足的条件和当前窗口内的值
 *  int left = 0, right = 0;
 *  while(right < end_size){
 *      // 扩大窗口
 *      获取当前值
 *      将当前值加入到窗口中
 *      right++
 *
 *      // 收缩窗口
 *      while(窗口收缩条件){
 *          更新结果
 *          获取left位置的值
 *          left++;
 *          判断该值是否在需要满足的条件中
 *              更新窗口内的值
 *      }
 *    }
 * }
 * */

//3. 无重复字符的最长子串
int lengthOfLongestSubstring(string& s){
    std::map<char, int> windows;
    int p1 = 0, p2 = 0;
    int res = 0;
    while(p2 < s.size()){
        char curr_char = s[p2];
        windows[curr_char]++;
        p2++;
        while(windows[curr_char] > 1){
            char p1_char = s[p1];
            windows[p1_char]--;
            p1++;
        }
        res = std::max(res, p2 - p1);
    }
    return res;
}

// 字符串的排列-判断一个字符串中是否包含另一个字符串的其中一个全排列
// 判断字符串s2中是否存在s1排列的子串
bool checkInclusion(string s1, string s2) {
    // 定义hash
    std::map<char, int> need, windows;
    // 初始化need
    for (char ch : s1){
        need[ch]++;
    }
    // 定义指针
    int left = 0, right = 0;
    int satisfied = 0;
    while(right < s2.size()){
        char right_ch = s2[right];
        right++;
        if (need.count(right_ch)){
            windows[right_ch]++;
            if (need.count(right_ch) == windows.count(right_ch))
                satisfied++;
        }
        // 收缩窗口
        while(right - left > s2.size()){
            // 判断是否成功匹配
            if (satisfied == need.size())
                return true;
            char left_ch = s2[left];
            left++;
            if (need.count(left_ch)){
                if (need.count(left_ch) == windows.count(left_ch))
                    satisfied--;
                windows[left_ch]--;
            }
        }
    }
    return false;
}


/*int main(){

}*/


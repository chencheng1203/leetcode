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


struct ListNode
{
    int val;
    ListNode* next;
    ListNode():val(-1), next(NULL){}
    ListNode(int value):val(value), next(NULL){}
};

// 复杂链表的节点
class CompletedNode {
public:
    int val;
    CompletedNode* next;
    CompletedNode* random;
    CompletedNode(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


// 创建ListNode
ListNode* createListNode(std::vector<int>& nums){
    ListNode* root;
    ListNode* p;
    if (!nums.size()) return new ListNode(-1);
    for (int i = 0; i < nums.size(); i++){
        if (i == 0) {
            root = new ListNode(nums[0]);
            p = root;
        }else{
            p->next = new ListNode(nums[i]);
            p = p->next;
        }
    }
    return root;
}

// 打印链表
void print_List(ListNode* root){
    ListNode* p = root;
    while(p){
        cout << p->val << ' ';
        p = p->next;
    }
}


// 反转链表
ListNode* reverseList(ListNode* head){
    ListNode* pre_node = NULL;
    ListNode* curr_node = head;
    ListNode* next_node = curr_node->next;
    ListNode* reversedNode;
    if (!curr_node) return head;
    while(curr_node){
        curr_node->next = pre_node;
        pre_node = curr_node;
        curr_node = next_node;
        if (curr_node)
            reversedNode = curr_node;
        if (curr_node)
            next_node = curr_node->next;
    }
    return reversedNode;
}


// 删除链表中的节点
ListNode* deleteNode(ListNode* head, int val){
    if (!head) return head;
    ListNode* nextNode = head->next;
    ListNode* p = head;
    if (p->val == val){
        head = p->next;
        return head;
    }
    while(nextNode){
        if (nextNode->val == val){
            p->next = nextNode->next;
            return head;
        }else{
            p = p->next;
            if (p)
                nextNode = p->next;
        }
    }
    cout << "No such value to delete!" << endl;
    return head;
}


// 合并两个排序链表
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
    ListNode* head;
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val < l2->val){
        ListNode* curr_node = new ListNode(l1->val);
        head = curr_node;
        head->next = mergeTwoLists(l1->next, l2);
    }
    else{
        ListNode* curr_node = new ListNode(l2->val);
        head = curr_node;
        head->next = mergeTwoLists(l1, l2->next);
    }
    return head;
}


// 链表中倒数第k个节点
ListNode* getKthFromEnd(ListNode* head, int k){
    ListNode* p1 = head;
    ListNode* p2 = head;
    for (int i = 0; i < k; i++){
        p2 = p2->next;
    }
    while(p2 != NULL){
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}


// 环形链表
bool hasCycle(ListNode *head){
    if (!head) return false;
    ListNode* p1 = head;
    ListNode* p2 = p1->next;
    const int MAX_ITERS = 1000;
    int curr_iter = 1;
    while(curr_iter <= MAX_ITERS && (!p1 && !p2)){
        if (p1 == p2) return true;
        p1 = p1->next;
        if (!p2->next) return false;
        else p2 = p2->next->next;
        curr_iter++;
    }
    return false;
}


// 两个链表的第一个公共节点
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){
    if (!headA || !headB) return NULL;
    std::stack<ListNode*> listStackA;
    std::stack<ListNode*> listStackB;
    ListNode *p1 = headA;
    ListNode *p2 = headB;
    while(p1){
        listStackA.push(p1);
        p1 = p1->next;
    }
    while(p2){
        listStackB.push(p2);
        p2 = p2->next;
    }

    ListNode* pre_node;
    p1 = listStackA.top();
    listStackA.pop();
    p2 = listStackB.top();
    listStackB.pop();
    if (p1 != p2){
        cout << "No common node existed!" << endl;
        return new ListNode(-1);
    }else{
        pre_node = p1;
    }
    while(listStackA.size() && listStackB.size()){
        p1 = listStackA.top();
        listStackA.pop();
        p2 = listStackB.top();
        listStackB.pop();
        if (p1 == p2){
            pre_node = p1;
        }else{
            return pre_node;
        }
    }
    return pre_node;
}


// 递归实现从尾到头打印链表
void reversePrint(ListNode* head){
    if (head == NULL){
        return;
    }
    reversePrint(head->next);
    cout << head->val << endl;
}


// 回文链表
bool isPalindrome(ListNode* head) {
    std::stack<int> node_stack;
    ListNode* p = head;
    while(p){
        node_stack.push(p->val);
        p = p->next;
    }
    p = head;
    while(node_stack.size()){
        int curr_val = node_stack.top();
        node_stack.pop();
        if (p->val != curr_val)
            return false;
        p = p->next;
    }
    return true;
}


// 链表排序


// 奇偶链表
ListNode* oddEvenList(ListNode* head){
    if (!head) return head;
    ListNode* curr_odd;
    ListNode* curr_even;
    ListNode* next_odd;
    ListNode* next_even;
    curr_odd = head;

    if (!curr_odd->next)
        return curr_odd;
    else
        curr_even = curr_odd->next;

    ListNode* odd_head = curr_odd;
    ListNode* even_head = curr_even;

    if (curr_even->next)
        next_odd = curr_even->next;
    while(next_odd){
        curr_odd->next = next_odd;
        curr_odd = curr_odd->next;
        if (curr_odd->next)
            next_even = curr_odd->next;
        else
            break;
        curr_even->next = next_even;
        curr_even = curr_even->next;
        next_odd = curr_even->next;
    }
    curr_even->next = NULL;
    curr_odd->next = even_head;
    return odd_head;
}


// 两两交换链表中的节点
ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* curr_p = head;
    ListNode* p_next = curr_p->next;
    ListNode* p_next_next = p_next->next;
    ListNode* pre_p;

    // exchange first 2 node
    curr_p->next = p_next_next;
    p_next->next = curr_p;
    ListNode* res_p = p_next;
    pre_p = curr_p;
    curr_p = p_next_next;

    while(curr_p && curr_p->next){
        p_next = curr_p->next;
        p_next_next = p_next->next;
        curr_p->next = p_next_next;
        p_next->next = curr_p;
        pre_p->next = p_next;
        pre_p = curr_p;
        curr_p = p_next_next;
    }
    return res_p;
}

// 复杂链表的复制
CompletedNode* copyRandomList(CompletedNode* head){
    if (!head) return head;
    CompletedNode* p = head;
    while(p){
        CompletedNode* p_next = p->next;
        CompletedNode* tmp_node = new CompletedNode(p->val);
        p->next = tmp_node;
        tmp_node->next = p_next;
        p = tmp_node->next;
    }
    p = head;
    while(p){
        CompletedNode* p_next = p->next;
        if (p->random)
            p_next->random = p->random->next;
        else
            p_next->random = NULL;
        p = p_next->next;
    }
    p = head->next;
    CompletedNode* pre_node = head;
    CompletedNode* res = head->next;
    while(p->next){
        pre_node->next = pre_node->next->next;
        p->next = p->next->next;
        pre_node = pre_node->next;
        p = p->next;
    }
    pre_node->next = NULL;
    return res;
}

// 链表中两数相加
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (!l1  && !l2) return NULL;
    std::stack<int> l1_stack;
    std::stack<int> l2_stack;
    ListNode* p = l1;
    while(p){
        l1_stack.push(p->val);
        p = p->next;
    }
    p = l2;
    while(p){
        l2_stack.push(p->val);
        p = p->next;
    }
    std::stack<int> res_stack;
    int add_bit = 0;
    int add_res = 0;
    while(l1_stack.size() && l2_stack.size()){
        int add_sum = l1_stack.top() + l2_stack.top() + add_bit;
        add_res = add_sum % 10;
        add_bit = add_sum / 10;
        l1_stack.pop();
        l2_stack.pop();
        res_stack.push(add_res);
    }
    while(l1_stack.size()){
        int add_sum = l1_stack.top() + add_bit;
        add_res = add_sum % 10;
        add_bit = add_sum / 10;
        l1_stack.pop();
        res_stack.push(add_res);
    }
    while(l2_stack.size()){
        int add_sum = l2_stack.top() + add_bit;
        add_res = add_sum % 10;
        add_bit = add_sum / 10;
        l2_stack.pop();
        res_stack.push(add_res);
    }
    if (add_bit != 0) res_stack.push(add_bit);
    ListNode* top_node = new ListNode(res_stack.top());
    res_stack.pop();
    p = top_node;
    while(!res_stack.empty()){
        p->next = new ListNode(res_stack.top());
        res_stack.pop();
        p = p->next;
    }
    return top_node;
}

// 判断链表中是否有环，若存在，则返回环的入口，否则返回null
// 1. 判断是否有环-快慢指针
// 2. 若有环，返回一个环中的节点
// 3. 计算环的长度 len
// 4. 头节点处设置两个指针，p1先走len步，然后两个指针一起走，当p1 == p2时，此处即为环的入口
ListNode* if_has_circle(ListNode* head){
    if (!head || !head->next) return NULL;
    ListNode* p1 = head;
    ListNode* p2 = p1->next;
    while(p1 != p2 && p2 != NULL && p1 != NULL){
        p1 = p1->next;
        if (!p2->next) return NULL;
        p2 = p2->next->next;
    }
    if (p1 == p2) return p1;
    if (p1 == NULL || p2 == NULL) return NULL;
    return NULL;
}
ListNode* detectCycle(ListNode *head) {
    ListNode* cir_p = if_has_circle(head);
    if (!cir_p) return NULL;
    int circle_len = 0;
    ListNode* p1 = cir_p;
    p1 = p1->next;
    circle_len++;
    while(p1 != cir_p){
        p1 = p1->next;
        circle_len++;
    }
    p1 = head;
    ListNode* p2 = head;
    for (int i = 0; i < circle_len; i++){
        p1 = p1->next;
    }
    while(p1 != p2){
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

// 链表的排序
ListNode* sortList(ListNode* head) {
    if (!head) return head;
    ListNode* p1 = head->next;
    ListNode* res_head = head;
    res_head->next = NULL;
    while(p1){
        ListNode* res_p = res_head;
        ListNode* pre_p  = NULL;
        while(res_p != NULL && res_p->val <= p1->val){
            pre_p = res_p;
            res_p = res_p->next;
        }
        if (pre_p){
            ListNode* tmp_node = p1;
            p1 = p1->next;
            pre_p->next = tmp_node;
            tmp_node->next = res_p;
        }else{
            ListNode* tmp_node = p1;
            p1 = p1->next;
            tmp_node->next = res_head;
            res_head = tmp_node;
        }
    }
    return res_head;
}

/*int main(){
	std::vector<int> arrays = {5, 1, 6, 3, 2};
    ListNode* head = createListNode(arrays);
    ListNode* res = sortList(head);

    ListNode* p = res;
    print_List(p);
}*/



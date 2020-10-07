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
    ListNode(int value):val(value), next(NULL){}
};


// 创建ListNode
ListNode* createListNode(std::vector<int> nums){
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


/*int main(){
	std::vector<int> arrays = {1, 3, 5, 6, 8, 9, 14, 15};
	ListNode* root = createListNode(arrays);
	reversePrint(root);
}*/


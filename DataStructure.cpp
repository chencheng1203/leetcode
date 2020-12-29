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

// 实现LRU（Least Recently Used）
// 双链表节点
class Node{
public:
    int key = 0, val = 0;
    Node* pre, *next;
    Node(int k, int v){
        key = k;
        val = v;
        pre = NULL;
        next = NULL;
    }
};

// 双链表
class DoubleList{
private:
    // 头节点与尾节点
    Node* head;
    Node* tail;
    int size = 0;  // 动态记录链表的大小

public:
    // 构造函数
    DoubleList(){
        // 虚头节点和尾节点
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->pre = head;
    }
    // 在链表尾部添加元素
    void addLst(Node* x){
        x->pre = tail->pre;
        x->next = tail;
        tail->pre->next = x;
        tail->pre = x;
        size++;
    }
    // 删除链表中的节点
    void remove(Node* x){
        x->pre->next = x->next;
        x->next->pre = x->pre;
        size--;
    }
    // 删除链表中第一个节点，并且返回链表的值
    Node* removeFirst(){
        if (head->next == tail){
            return NULL;
        }
        Node* firstNode = head->next;
        head->next = firstNode->next;
        firstNode->next->pre = head;
        size--;
        return  firstNode;
    }
    // 返回链表长度
    int getSize(){
        return size;
    }
};

class LRUCache{
private:
    std::map<int, Node*> key2Node;
    DoubleList* cache;
    int cap;
public:
    // 构造函数
    LRUCache(int capacity){
        this->cap = capacity;
        cache = new DoubleList();
    }
    // 将某个key提升为最近使用
    void makeRecenty(int key){
        Node* x = key2Node[key];
        cache->remove(x);
        cache->addLst(x);
        key2Node[key] = x;
    }
    // 添加最近使用的元素
    void addRencenty(int key, int val){
        Node* x = new Node(key, val);
        cache->addLst(x);
        key2Node[key] = x;
    }
    // 删除某一个key
    void deleteKey(int key){
        Node* x = key2Node[key];
        cache->remove(x);
        key2Node.erase(key);
    }
    // 删除最久未使用的元素
    void removeLeastRecenty(){
        Node* deleteNode = cache->removeFirst();
        int deleteKey = deleteNode->key;
        key2Node.erase(deleteKey);
    }
    // 得到某个元素
    int get(int key){
        if (!key2Node.count(key)){
            return -1;
        }
        makeRecenty(key);
        return key2Node[key]->val;
    }
    // 插入元素
    void put(int key, int val){
        if (key2Node.count(key)){ // 已经存在，提升到最近使用
            deleteKey(key);
            addRencenty(key, val);
            return;
        }
        int cache_size = cache->getSize();
        if (cache_size >= cap){
            removeLeastRecenty();
        }
        addRencenty(key, val);
    }
};

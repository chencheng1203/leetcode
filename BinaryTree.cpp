#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

// 按照层次创建二叉树-队列的使用
TreeNode* createBTree(vector<int> arrays){
    TreeNode* root;
    std::queue<TreeNode*> TreeNodeQueue;
    int curr_index = 0;
    int curr_val = arrays[curr_index];
    curr_index++;
    // create root node
    if (curr_val == -1) return root;
    else{
        root = new TreeNode(curr_val);
        TreeNodeQueue.push(root);
    }
    while(TreeNodeQueue.size() && curr_index != arrays.size()){
        TreeNode* curr_node = TreeNodeQueue.front();
        TreeNodeQueue.pop();
        if (arrays[curr_index] == -1){
            curr_node->left = NULL;
            curr_index++;
        }else{
            curr_node->left = new TreeNode(arrays[curr_index]);
            TreeNodeQueue.push(curr_node->left);
            curr_index++;
        }
        if (arrays[curr_index] == -1){
            curr_node->right = NULL;
            curr_index++;
        }else{
            curr_node->right = new TreeNode(arrays[curr_index]);
            TreeNodeQueue.push(curr_node->right);
            curr_index++;
        }
    }
    return root;
}

// 打印二叉树


// 中序遍历
void inorder(TreeNode* root, vector<int>& res){
    if (root){
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
}

// 二叉树的深度-分治、递归
int maxDepth(TreeNode* root){
    if (root == NULL) return 0;
    int n_left = 1 + maxDepth(root->left);
    int n_right = 1 + maxDepth(root->right);
    return std::max(n_left, n_right);
}


// 对称的二叉树
bool isSymmetricTreeCore(TreeNode* root1, TreeNode* root2){
    if (!root1 && !root2) return true;
    if (root1->val != root2->val) return false;
    if ((root1 && !root2) || (root2 && !root1)) return false;
    return isSymmetricTreeCore(root1->left, root2->left) && isSymmetricTreeCore(root1->right, root2->right);
}
bool isSymmetricTree(TreeNode* root){
    return isSymmetricTreeCore(root, root);
}


// 二叉树的镜像
void exchangeTNode(TreeNode* root){
    TreeNode* tempNode = root->left;
    root->left = root->right;
    root->right = tempNode;
}
TreeNode* mirrorTree(TreeNode* root){
    exchangeTNode(root);
    if (root->left) mirrorTree(root->left);
    if (root->right) mirrorTree(root->right);
    return root;
}


// 合并二叉树
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2){
    if (!t1) return t2;
    if (!t2) return t1;
    t1->val = t1->val + t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    return t1;
}


// 二叉树中和为某一个值的路径
void pathSumCore(TreeNode* root, int sum, int curr_sum, std::vector<int>& path, std::vector<std::vector<int>>& res){
    curr_sum += root->val;
    path.push_back(root->val);

    bool is_leaf = (!root->left && !root->right);
    if (is_leaf && curr_sum == sum){
        res.push_back(path);
        return;
    }
    if (root->left){
        pathSumCore(root->left, sum, curr_sum, path, res);
    }
    if (root->right){
        pathSumCore(root->right, sum, curr_sum, path, res);
    }
    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int sum){
    std::vector<int> path;
    std::vector<std::vector<int>> res;
    pathSumCore(root, sum, 0, path, res);
    return res;
}


// 二叉搜索树的后续遍历序列
bool verifyPostorderCore(std::vector<int>& postorder, int beg, int end){
    if (postorder.size() < 0) return false;
    int end_point = postorder[end];
    int i = beg;
    for (; postorder[i] <= end_point; i++);
    int j = i;
    for(; j < end; j++){
        if (postorder[j] < end_point){
            return false;
        }
    }
    bool left = true;
    if (i < end)
        left = verifyPostorderCore(postorder, beg, i-1);
    bool right = true;
    if (i > beg)
        right = verifyPostorderCore(postorder, i, end);
    return left & right;
}

bool verifyPostorder(std::vector<int>& postorder){
    return verifyPostorderCore(postorder, 0, postorder.size()-1);
}


// 二叉搜索树的最近公共祖先
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
    if (p->val < root->val && q->val < root->val){
        return lowestCommonAncestor(root->left, p, q);
    }
    if (p->val > root->val && q->val > root->val){
        return lowestCommonAncestor(root->right, p, q);
    }
    return root;
}


// 二叉树的宽度优先遍历
void levelOrderCore(TreeNode* root, std::vector<int>& res){
    if (!root) return;
    std::queue<TreeNode*> treeNodeQueue;
    treeNodeQueue.push(root);
    while(treeNodeQueue.size()){
        TreeNode* curr_node = treeNodeQueue.front();
        treeNodeQueue.pop();
        res.push_back(curr_node->val);
        if (curr_node->left) treeNodeQueue.push(curr_node->left);
        if (curr_node->right) treeNodeQueue.push(curr_node->right);
    }
}

std::vector<int> levelOrder(TreeNode* root){
    std::vector<int> res;
    levelOrderCore(root, res);
    return res;
}


// 返回二叉树每一层中的元素
void returnLevelOrderCore(TreeNode* root, std::vector<std::vector<int>>& res){
    std::vector<int> level_res;
    if (!root) return;
    std::queue<TreeNode*> treeNodeQueue;
    treeNodeQueue.push(root);
    while(treeNodeQueue.size()){
        int queueSize = treeNodeQueue.size();
        for (int i = 0; i < queueSize; i++){
            TreeNode* curr_node = treeNodeQueue.front();
            treeNodeQueue.pop();
            level_res.push_back(curr_node->val);
            if (curr_node->left) treeNodeQueue.push(curr_node->left);
            if (curr_node->right) treeNodeQueue.push(curr_node->right);
        }
        res.push_back(level_res);
        level_res.clear();
    }
}

std::vector<std::vector<int>> returnLevelOrder(TreeNode* root){
    std::vector<std::vector<int>> res;
    returnLevelOrderCore(root, res);
    return res;
}


// 二叉树中的插入操作
void insertIntoBST(TreeNode* root, int val){
    if (!root->left && !root->right){
        if (root->val > val){
            root->left = new TreeNode(val);
        }else{
            root->right = new TreeNode(val);
        }
        return;
    }

    if (root->val < val){
        if (!root->right){
            root->right = new TreeNode(val);
            return;
        }else{
            insertIntoBST(root->right, val);
        }
    }
    else{
        if (!root->left){
            root->left = new TreeNode(val);
            return;
        }else{
            insertIntoBST(root->left, val);
        }
    }
}


// 填充每个节点的下一个右侧节点
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

Node* connect(Node* root) {
    if (!root) return root;
    vector<Node*> node_queue;
    node_queue.push_back(root);
    while(node_queue.size()){
        int curr_size = node_queue.size();
        for (int i = 0; i < curr_size; i++){
            Node* curr_node = node_queue.front();
            node_queue.erase(node_queue.begin());
            if (curr_node->left){
                node_queue.push_back(curr_node->left);
            }
            if (curr_node->right){
                node_queue.push_back(curr_node->right);
            }
            if (i == curr_size - 1){
                curr_node->next = NULL;
            }else{
                curr_node->next = node_queue[0];
            }
        }
    }
    return root;
}

// 根据中序遍历与后续遍历构建二叉树
TreeNode* buildTreeCore(std::map<int, int>& index_map, vector<int>& inorder, int inorder_front, int inorder_end,
                        vector<int>& postorder, int poster_front, int poster_end){
    if (inorder_front > inorder_end || poster_front > poster_end) return NULL;
    int curr_root_val = postorder[poster_end];
    TreeNode* root = new TreeNode(curr_root_val);
    // 左子树
    int lis = inorder_front;
    int lie = index_map[curr_root_val] - 1;
    int lps = poster_front;
    int lpe = poster_front + index_map[curr_root_val] - inorder_front - 1;

    // 右子树
    int ris = index_map[curr_root_val] + 1;
    int rie = inorder_end;
    int rps = poster_front + index_map[curr_root_val] - inorder_front;
    int rpe = poster_end - 1;

    root->left = buildTreeCore(index_map, inorder, lis, lie, postorder, lps, lpe);
    root->right = buildTreeCore(index_map, inorder, ris, rie, postorder, rps, rpe);
    return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder){
    std::map<int, int> index_map;
    for (int i = 0; i < inorder.size(); i++){
        index_map[inorder[i]] = i;
    }
    TreeNode* root = buildTreeCore(index_map, inorder, 0, inorder.size()-1,
                                   postorder, 0, postorder.size()-1);
    return root;
}

// 非递归树的中序遍历
vector<int> inorderTraversal_not_recu(TreeNode* root){
    vector<int> res;
    std::stack<TreeNode*> stk;
    while(root != NULL || stk.size()){
        while(root != NULL){
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}

// 二叉树的剪纸
TreeNode* pruneTreeCore(TreeNode* root) {
    if (root->left){
        root->left = pruneTreeCore(root->left);
    }
    if (root->right){
        root->right = pruneTreeCore(root->right);
    }
    if (root->left)
        if (!root->left->left && !root->left->right && root->left->val == 0){
            root->left = NULL;
        }
    if (root->right)
        if (!root->right->left && !root->right->right && root->right->val == 0){
            root->right = NULL;
        }
    return root;
}
TreeNode* pruneTree(TreeNode* root) {
    TreeNode* res = pruneTreeCore(root);
    if (!res->left && !res->right && res->val == 0)
        return NULL;
    return res;
}

// 包含所有最深节点的最小子树
TreeNode* subtreeWithAllDeepest(TreeNode* root) {
    if (!root) return root;
    int left_depth = maxDepth(root->left);
    int right_depth = maxDepth(root->right);
    if (left_depth == right_depth){
        return root;
    }else{
        if (left_depth > right_depth) return subtreeWithAllDeepest(root->left);
        else return subtreeWithAllDeepest(root->right);
    }
}

// 合法的二叉搜索树
// 合法的二叉搜索树其中序遍历是递增的
bool isValidBST(TreeNode* root) {
    if (!root) return true;
    vector<int> inorder_res;
    inorder(root, inorder_res);
    for (int i = 1; i < inorder_res.size(); i++){
        if (inorder_res[i] <= inorder_res[i - 1])
            return false;
    }
    return true;
}

// 求和路径
int pathSum_res = 0;
void pathSumCore(TreeNode* root, int sum , int curr_sum, int& res){
    if (root)
        curr_sum += root->val;
    else
        return;
    if (curr_sum == sum){
        res++;
    }
    if (root->left){
        pathSumCore(root->left, sum , curr_sum, res);
    }
    if (root->right){
        pathSumCore(root->right, sum , curr_sum, res);
    }
}
int pathSum_2(TreeNode* root, int sum) {
    if (!root) return 0;
    pathSumCore(root, sum, 0, pathSum_res);
    if (root->left)
        pathSum_2(root->left, sum);
    if (root->right)
        pathSum_2(root->right, sum);
    return pathSum_res;
}


// 删点成林
bool isInDeleteList(int val, vector<int>& to_delete){
    for (int i = 0; i < to_delete.size(); i++){
        if (val == to_delete[i])
            return true;
    }
    return false;
}

void delNodesCore(TreeNode*& node, vector<int>& to_delete, vector<TreeNode*>& res) {
    if (node == NULL) return;
    delNodesCore(node->left, to_delete, res);
    delNodesCore(node->right, to_delete, res);
    if (isInDeleteList(node->val, to_delete)){
        if (node->left) res.push_back(node->left);
        if (node->right) res.push_back(node->right);
        node = NULL;
    }
}

vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    vector<TreeNode*> res;
    delNodesCore(root, to_delete, res);
    if (root) res.push_back(root);
    return res;
}


/*int main(){
    vector<int> tree_val = {1, 2, 3, -1, -1, -1, 4};
    vector<int> to_delete = {2, 1};
    TreeNode* root = createBTree(tree_val);
    vector<TreeNode*> res = delNodes(root, to_delete);
    for (TreeNode* node : res){
        cout << node->val << ' ';
    }
}*/



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

/*int main(){
	std::vector<int> v = {3,9,20,-1,-1,15,7};
	TreeNode* root = createBTree(v);
	std::vector<std::vector<int>> res = returnLevelOrder(root);
	for (int i = 0; i < res.size(); i++){
		for (int j = 0; j < res[i].size(); j++){
			cout << res[i][j] << ' ';
		}
		cout << endl;
	}
}*/



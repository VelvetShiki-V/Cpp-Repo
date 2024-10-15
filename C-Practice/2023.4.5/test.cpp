#define CRT_NOWARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//////////////////////////////////////////// 2023.4.5

// 1. 剑指 Offer 53 - I. 在排序数组中查找数字 Ihttps://leetcode.cn/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int count = 0;
        for (auto& it : nums) {
            if (it == target) count++;
        }
        return count;
    }
};

// 2. 剑指 Offer 58 - II. 左旋转字符串https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        s.append(s.substr(0, n));
        s.erase(0, n);
        return s;
    }
};

// 3. 剑指 Offer 53 - II. 0～n-1中缺失的数字https://leetcode.cn/problems/que-shi-de-shu-zi-lcof/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0, total = 0;
        for (auto& it : nums) sum += it;
        for (int i = 0; i < nums.size() + 1; ++i) {
            total += i;
        }
        return total - sum;
    }
};

// 4.剑指 Offer 54. 二叉搜索树的第k大节点https://leetcode.cn/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/
class Solution {
public:
    void Traversal(set<int, greater<int>>& s, TreeNode* root) {
        if (nullptr == root) return;
        s.insert(root->val);
        Traversal(s, root->left);
        Traversal(s, root->right);
    }
    int kthLargest(TreeNode* root, int k) {
        set<int, greater<int>> s;
        Traversal(s, root);
        int ret = 0;
        for (auto& it : s) {
            --k;
            if (k == 0) ret = it;
        }
        return ret;
    }
};

// 5. 剑指 Offer 65. 不用加减乘除做加法https://leetcode.cn/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/
class Solution {
public:
    int add(int a, int b) {     // 非进位和：异或   进位和：与运算+左移
        while (b) {
            unsigned int carry = (unsigned int)(a & b) << 1;  // 无符号防止最高32位为1      
            a ^= b;     // 非进位和更新给a
            b = carry;  // 今为何更新给b
        }
        return a;
    }
};

// 6. 剑指 Offer 55 - II. 平衡二叉树https://leetcode.cn/problems/ping-heng-er-cha-shu-lcof/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // 1. 计算每棵子树深度，左子树-右子树绝对值判断是否 > 1
    // 2. 平衡三条件：每个根左右平衡；每个根的左子树平衡；每个根的右子树平衡
    // 3. 空树是平衡的
    int depth(TreeNode* root) {
        if (nullptr == root) return 0;
        return max(depth(root->left), depth(root->right)) + 1;
    }
    bool isBalanced(TreeNode* root) {
        if (nullptr == root) return true;
        return abs(depth(root->left) - depth(root->right)) <= 1 &&
            isBalanced(root->left) && isBalanced(root->right);
    }
};

// 7. 剑指 Offer 62. 圆圈中最后剩下的数字https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/
// 法1：哈希桶  时度ON^2
class Solution {
public:
    int lastRemaining(int n, int m) {
        unordered_map<int, bool> um;
        for (int i = 0; i < n; ++i) {
            um[i] = true;
        }
        int index = 0, cap = n;
        while (cap != 1) {
            for (int i = 0; i < m - 1; ++i) {
                index = (index + 1) % n;
                while (um[index] == false) index = (index + 1) % n;
            }
            um[index] = false;
            index = (index + 1) % n;
            while (um[index] == false) index = (index + 1) % n;
            --cap;
        }
        return index;
    }
};
// 法2：递推公式——每次循环右移m，再将超出的部分取模归到内部
// f(8,3)=[f(7,3)＋3]%8
// f (n, m) =[f(n — 1, m)+m]%n
class Solution {
public:
    int lastRemaining(int n, int m) {
        int pos = 0;
        for (int i = 2; i <= n; ++i) {
            pos = (pos + m) % i;
        }
        return pos;
    }
};

// 8. 
// 法1：两次遍历记录祖先结点，找分叉点即为最近
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void find(TreeNode* root, TreeNode* target, vector<TreeNode*>& v) {
        while (root) {
            v.push_back(root);
            if (root->val < target->val) {
                root = root->right;
            }
            else if (root->val > target->val) {
                root = root->left;
            }
            else break;
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (nullptr == root) return nullptr;
        vector<TreeNode*> vp;
        vector<TreeNode*> vq;
        find(root, p, vp);
        find(root, q, vq);
        int i = 0;
        while (i < vp.size() && i < vq.size() && vp[i] == vq[i]) ++i;
        return vp[i - 1];
    }
};
// 法2：一次遍历，两个值一起对比
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (true) {
            if (root->val > p->val && root->val > q->val) root = root->left;
            else if (root->val < p->val && root->val < q->val) root = root->right;
            else break;
        }
        return root;
    }
};

//剑指 Offer 68 - II. 二叉树的最近公共祖先https://leetcode.cn/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/
// 法1：递归遍历左右子树，若存在返回true，否则返回假，若位于同一侧，则递归进入左子树或右子树
class Solution {
public:
    bool find(TreeNode* root, TreeNode* target) {
        if (nullptr == root) return false;
        if (root->val == target->val) return true;
        return find(root->left, target) || find(root->right, target);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (nullptr == root) return nullptr;
        if (root == p || root == q) return root;
        bool pInLeft, pInRight, qInLeft, qInRight;
        pInLeft = find(root->left, p);
        pInRight = !pInLeft;
        qInLeft = find(root->left, q);
        qInRight = !qInLeft;
        if (pInLeft && qInRight || pInRight && qInLeft) return root;
        else if (pInLeft && qInLeft) return lowestCommonAncestor(root->left, p, q);
        else if (pInRight && qInRight) return lowestCommonAncestor(root->right, p, q);
        return nullptr;
    }
};

// 法2：哈希桶记录父节点，从p或q结点根据哈希父节点向上遍历找true
class Solution {
public:
    void Traversal(TreeNode* root, unordered_map<int, TreeNode*>& m) {
        if (nullptr == root) return;
        if (root->left) {
            m[root->left->val] = root;      // 哈希桶子结点值映射父节点地址，方便后续子结点可以依据桶下标找到对应父节点，并向上迭代
            Traversal(root->left, m);
        }
        if (root->right) {
            m[root->right->val] = root;
            Traversal(root->right, m);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (nullptr == root) return nullptr;
        unordered_map<int, TreeNode*> record;       // 因为值唯一，可以将结点数值作为key映射对应结点地址
        unordered_map<int, bool> flag;
        record[root->val] = nullptr;
        Traversal(root, record);
        while (p) {
            flag[p->val] = true;
            p = record[p->val];
        }
        while (q) {
            if (flag[q->val]) return q;
            q = record[q->val];
        }
        return nullptr;
    }
};
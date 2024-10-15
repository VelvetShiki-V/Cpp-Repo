#define CRT_NOWARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//////////////////////////////////////////// 2023.4.5

// 1. ��ָ Offer 53 - I. �����������в������� Ihttps://leetcode.cn/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/
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

// 2. ��ָ Offer 58 - II. ����ת�ַ���https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        s.append(s.substr(0, n));
        s.erase(0, n);
        return s;
    }
};

// 3. ��ָ Offer 53 - II. 0��n-1��ȱʧ������https://leetcode.cn/problems/que-shi-de-shu-zi-lcof/
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

// 4.��ָ Offer 54. �����������ĵ�k��ڵ�https://leetcode.cn/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/
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

// 5. ��ָ Offer 65. ���üӼ��˳����ӷ�https://leetcode.cn/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/
class Solution {
public:
    int add(int a, int b) {     // �ǽ�λ�ͣ����   ��λ�ͣ�������+����
        while (b) {
            unsigned int carry = (unsigned int)(a & b) << 1;  // �޷��ŷ�ֹ���32λΪ1      
            a ^= b;     // �ǽ�λ�͸��¸�a
            b = carry;  // ��Ϊ�θ��¸�b
        }
        return a;
    }
};

// 6. ��ָ Offer 55 - II. ƽ�������https://leetcode.cn/problems/ping-heng-er-cha-shu-lcof/
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
    // 1. ����ÿ��������ȣ�������-����������ֵ�ж��Ƿ� > 1
    // 2. ƽ����������ÿ��������ƽ�⣻ÿ������������ƽ�⣻ÿ������������ƽ��
    // 3. ������ƽ���
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

// 7. ��ָ Offer 62. ԲȦ�����ʣ�µ�����https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/
// ��1����ϣͰ  ʱ��ON^2
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
// ��2�����ƹ�ʽ����ÿ��ѭ������m���ٽ������Ĳ���ȡģ�鵽�ڲ�
// f(8,3)=[f(7,3)��3]%8
// f (n, m) =[f(n �� 1, m)+m]%n
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
// ��1�����α�����¼���Ƚ�㣬�ҷֲ�㼴Ϊ���
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
// ��2��һ�α���������ֵһ��Ա�
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

//��ָ Offer 68 - II. �������������������https://leetcode.cn/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/
// ��1���ݹ�������������������ڷ���true�����򷵻ؼ٣���λ��ͬһ�࣬��ݹ������������������
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

// ��2����ϣͰ��¼���ڵ㣬��p��q�����ݹ�ϣ���ڵ����ϱ�����true
class Solution {
public:
    void Traversal(TreeNode* root, unordered_map<int, TreeNode*>& m) {
        if (nullptr == root) return;
        if (root->left) {
            m[root->left->val] = root;      // ��ϣͰ�ӽ��ֵӳ�丸�ڵ��ַ����������ӽ���������Ͱ�±��ҵ���Ӧ���ڵ㣬�����ϵ���
            Traversal(root->left, m);
        }
        if (root->right) {
            m[root->right->val] = root;
            Traversal(root->right, m);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (nullptr == root) return nullptr;
        unordered_map<int, TreeNode*> record;       // ��ΪֵΨһ�����Խ������ֵ��Ϊkeyӳ���Ӧ����ַ
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
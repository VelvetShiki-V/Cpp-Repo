#define CRT_NOWARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//////////////////////////////////////////// 2023.4.2
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


// 1. 剑指 Offer 06. 从尾到头打印链表https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        ListNode* p = head;
        vector<int> v;
        while (p) {
            v.push_back(p->val);
            p = p->next;
        }
        reverse(v.begin(), v.end());
        return v;
    }
};

// 2. 剑指 Offer 25. 合并两个排序的链表https://leetcode.cn/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(0);     // 头哨兵结点，改指向法
        ListNode* cur = head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 == nullptr ? l2 : l1;
        return head->next;
    }
};

// 3. 剑指 Offer 27. 二叉树的镜像https://leetcode.cn/problems/er-cha-shu-de-jing-xiang-lcof/
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (nullptr == root) return root;
        TreeNode* left = mirrorTree(root->left);
        TreeNode* right = mirrorTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};

// 4. 剑指 Offer 05. 替换空格https://leetcode.cn/problems/ti-huan-kong-ge-lcof/
class Solution {
public:
    string replaceSpace(string s) {
        size_t i = 0;
        for (i; i < s.size(); ++i) {
            if (s[i] == ' ') {
                s.replace(i, 1, "%20");
            }
        }
        return s;
    }
};

// 5. 剑指 Offer 11. 旋转数组的最小数字https://leetcode.cn/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/
class Solution {
public:
    int minArray(vector<int>& numbers) {
        sort(numbers.begin(), numbers.end());
        return numbers[0];
    }
};

// 6. 剑指 Offer 10- II. 青蛙跳台阶问题https://leetcode.cn/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/
class Solution {
public:
    int numWays(int n) {
        if (n < 2) return 1;
        int base1 = 1;
        int base2 = 1;
        int fib = 0;
        while (n != 1) {
            fib = (base1 + base2) % 1000000007;
            base1 = base2;
            base2 = fib;
            --n;
        }
        return fib;
    }
};

// 7. 剑指 Offer 03. 数组中重复的数字https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        map<int, int> statistic;
        for (auto& it : nums) {
            if (++statistic[it] > 1) {
                return it;
            }
        }
        return 0;
    }
};

// 8. 剑指 Offer 10- I. 斐波那契数列https://leetcode.cn/problems/fei-bo-na-qi-shu-lie-lcof/
class Solution {
public:
    int fib(int n) {
        if (0 == n) return 0;
        else if (n == 1) return 1;
        int base1 = 0;
        int base2 = 1;
        int fib = 0;
        while (n != 1) {
            fib = (base1 + base2) % 1000000007;
            base1 = base2;
            base2 = fib;
            --n;
        }
        return fib;
    }
};

// 9. 剑指 Offer 09. 用两个栈实现队列https://leetcode.cn/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/
class CQueue {
public:
    CQueue() {

    }

    void appendTail(int value) {
        st_push.push(value);
    }

    int deleteHead() {
        if (!st_pop.empty()) {
            int get = st_pop.top();
            st_pop.pop();
            return get;
        }
        else if (!st_push.empty()) {
            while (!st_push.empty()) {
                int put = st_push.top();
                st_push.pop();
                st_pop.push(put);
            }
            int get = st_pop.top();
            st_pop.pop();
            return get;
        }
        return -1;
    }
private:
    stack<int> st_push;
    stack<int> st_pop;
};


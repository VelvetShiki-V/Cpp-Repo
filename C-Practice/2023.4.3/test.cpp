#define CRT_NOWARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//////////////////////////////////////////// 2023.4.2

// 1. 剑指 Offer 28. 对称的二叉树
class Solution {
public:
    bool check(TreeNode* left, TreeNode* right) {
        if (!left && !right) return true;        // 同时到尾
        if (!left || !right) return false;       // 不对称
        return left->val == right->val &&       // 值相同，结点相同
            check(left->left, right->right) &&
            check(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) {
        return check(root, root);
    }
};

// 2. 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面https://leetcode.cn/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int begin = 0, end = nums.size() - 1;       // 注意size_t负数会变无穷大数
        while (begin < end) {
            while (nums[begin] % 2 == 1 && begin < end) {        // 左找偶
                ++begin;
            }
            while (nums[end] % 2 == 0 && begin < end) {          // 右找奇
                --end;
            }
            if (begin < end) {
                swap(nums[begin], nums[end]);
                ++begin;
                --end;
            }
        }
        return nums;
    }
};

// 3. 剑指 Offer 15. 二进制中1的个数https://leetcode.cn/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int move = 32, count = 0;
        while (move) {
            if (n % 2 == 1) count++;
            n >>= 1;
            --move;
        }
        return count;
    }
};

// 4. 剑指 Offer 29. 顺时针打印矩阵https://leetcode.cn/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int rows = matrix.size(), columns = matrix[0].size();
        int left = 0, right = columns - 1;
        int top = 0, bottom = rows - 1;
        vector<int> result;
        while (left <= right && top <= bottom) {
            // 顶层
            for (int i = left; i <= right; ++i) {
                result.push_back(matrix[top][i]);
            }
            // 右侧
            for (int j = top + 1; j <= bottom; ++j) {
                result.push_back(matrix[j][right]);
            }
            // 底层和中间
            if (left < right && top < bottom) {
                for (int i = right - 1; i >= left; --i) {
                    result.push_back(matrix[bottom][i]);
                }
                for (int j = bottom - 1; j >= top + 1; --j) {
                    result.push_back(matrix[j][left]);
                }
            }
            left++;
            right--;
            bottom--;
            top++;
        }
        return result;
    }
};

// 5. 剑指 Offer 22. 链表中倒数第k个节点https://leetcode.cn/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        int size = 0;
        ListNode* cur = head;
        while (cur) {
            cur = cur->next;
            size++;
        }
        int steps = size - k;
        cur = head;
        while (steps--) {
            cur = cur->next;
        }
        return cur;
    }
};

// 6. 剑指 Offer 17. 打印从1到最大的n位数https://leetcode.cn/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/
class Solution {
public:
    vector<int> printNumbers(int n) {
        int limit = 9;
        for (int i = 1; i < n; ++i) {
            limit *= 10;
            limit += 9;
        }
        vector<int> ret;
        for (int i = 1; i <= limit; ++i) {
            ret.push_back(i);
        }
        return ret;
    }
};

// 7. 剑指 Offer 24. 反转链表https://leetcode.cn/problems/fan-zhuan-lian-biao-lcof/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return nullptr;
        ListNode* cur = head, * prev = nullptr;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

// 8. 剑指 Offer 18. 删除链表的节点https://leetcode.cn/problems/shan-chu-lian-biao-de-jie-dian-lcof/
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if (!head) return nullptr;
        ListNode* cur = head, * prev = head;
        while (cur->val != val) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == head) head = head->next;
        ListNode* next = cur->next;     // 题目要求不用delete
        prev->next = next;
        return head;
    }
};

// 9. 剑指 Offer 40. 最小的k个数https://leetcode.cn/problems/zui-xiao-de-kge-shu-lcof/
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        vector<int> ret;
        for (int i = 0; i < k; ++i) {
            ret.push_back(arr[i]);
        }
        return ret;
    }
};

// 10. 剑指 Offer 30. 包含min函数的栈https://leetcode.cn/problems/bao-han-minhan-shu-de-zhan-lcof/
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        s.push(x);
        if (mins.empty()) mins.push(x);
        else if (x <= mins.top()) mins.push(x);
    }

    void pop() {
        if (!mins.empty() && s.top() == mins.top()) mins.pop();
        s.pop();
    }

    int top() {
        return s.top();
    }

    int min() {
        return mins.top();
    }
private:
    stack<int> s;
    stack<int> mins;
};

// 11. 剑指 Offer 42. 连续子数组的最大和https://leetcode.cn/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0, maxNum = nums[0];
        for (auto& it : nums) {
            sum = max(sum + it, it);
            maxNum = max(maxNum, sum);
        }
        return maxNum;
    }
};

// 12. 剑指 Offer 39. 数组中出现次数超过一半的数字https://leetcode.cn/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> m;
        for (auto& it : nums) {
            m[it]++;
        }
        for (auto& it : m) {
            if (it.second > nums.size() / 2) return it.first;
        }
        return 0;
    }
};

// 13. 剑指 Offer 32 - II. 从上到下打印二叉树 IIhttps://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (nullptr == root) return vector<vector<int>> {};
        vector<vector<int>> vv;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            vector<int> v;
            size_t sz = q.size();
            while (sz--) {
                if (q.front()->left) {
                    q.push(q.front()->left);
                }
                if (q.front()->right) {
                    q.push(q.front()->right);
                }
                v.push_back(q.front()->val);
                q.pop();
            }
            vv.push_back(v);
        }
        return vv;
    }
};

// 14. 剑指 Offer 50. 第一个只出现一次的字符https://leetcode.cn/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/
// SPACE O(N)  TIME O(N)
class Solution {
public:
    char firstUniqChar(string s) {
        map<char, int> m;
        for (auto& it : s) {
            m[it]++;
        }
        vector<char> v;
        for (auto& it : m) {
            if (it.second == 1) {
                cout << it.first << ": " << it.second << endl;
                v.push_back(it.first);
            }
        }
        if (!v.empty()) {
            size_t min = s.size() - 1;
            for (auto& it : v) {
                size_t pos = s.find(it);
                if (pos < min) min = pos;
            }
            return s[min];
        }
        return ' ';
    }
};

// 15. 剑指 Offer 55 - I. 二叉树的深度https://leetcode.cn/problems/er-cha-shu-de-shen-du-lcof/
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (nullptr == root) return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return max(left, right) + 1;
    }
};

// 16. 剑指 Offer 57. 和为s的两个数字https://leetcode.cn/problems/he-wei-sde-liang-ge-shu-zi-lcof/
// 对撞指针
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        vector<int> v;
        while (left < right) {
            if (nums[left] + nums[right] > target) right--;
            else if (nums[left] + nums[right] < target) left++;
            else {
                v.push_back(nums[left]);
                v.push_back(nums[right]);
                break;
            }
        }
        return v;
    }
};
#define CRT_NOWARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//////////////////////////////////////////// 2023.4.4

// 1. 剑指 Offer 57 - II. 和为s的连续正数序列https://leetcode.cn/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> vv;
        if (target <= 2) return vv;
        int begin = 1, bound = target / 2;
        // 滑动窗口算法
        while (begin <= bound) {
            int left = begin, right = left + 1;
            int sum = left + right;
            vector<int> v;
            while (sum < target) {       // 滑动窗口累计值更小，右边界右移
                right++;
                sum += right;
            }
            while (sum > target) {       // 滑动窗口累计值更大，左边界右移
                sum -= left;
                left++;
            }
            if (sum == target) {         // 相同就插入
                for (int i = left; i <= right; ++i) {
                    v.push_back(i);
                }
            }
            if (!v.empty()) {
                vv.push_back(v);
            }
            begin++;
        }
        // 去重
        set<vector<int>> s{ vv.begin(), vv.end() };
        vv = vector<vector<int>>{ s.begin(), s.end() };
        return vv;
    }
};

// 2. 剑指 Offer 52. 两个链表的第一个公共节点https://leetcode.cn/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/
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
    ListNode* getCommon(ListNode* headA, ListNode* headB) {
        while (headA) {
            if (headA == headB) return headA;
            headA = headA->next;
            headB = headB->next;
        }
        return nullptr;
    }
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (headA == headB) return getCommon(headA, headB);
        if (nullptr == headA || nullptr == headB) return nullptr;
        int aSize = 0, bSize = 0;
        ListNode* aCur = headA, * bCur = headB, * longer = nullptr, * shorter = nullptr;
        while (aCur) {
            ++aSize;
            aCur = aCur->next;
        }
        while (bCur) {
            ++bSize;
            bCur = bCur->next;
        }
        int steps = aSize - bSize;
        if (steps >= 0) {
            longer = headA;
            shorter = headB;
            while (steps--) longer = longer->next;
        }
        else {
            longer = headB;
            shorter = headA;
            while (steps++) longer = longer->next;
        }
        return getCommon(longer, shorter);
    }
};

// 3. 剑指 Offer 58 - I. 翻转单词顺序https://leetcode.cn/problems/fan-zhuan-dan-ci-shun-xu-lcof/
class Solution {
public:
    string reverseWords(string s) {
        int right = s.size() - 1;
        string result;
        while (right >= 0) {
            while (right >= 0 && s[right] == ' ') right--;          // 右边去空格
            if (right == -1) break;
            int left = right;
            while (left >= 0 && s[left] != ' ') left--;             // 插入字符和空格，并以当前left为右边界
            result.append(s, left + 1, right - left);
            result += ' ';
            right = left;
        }
        result.pop_back();
        return result;
    }
};
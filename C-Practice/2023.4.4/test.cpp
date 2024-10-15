#define CRT_NOWARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//////////////////////////////////////////// 2023.4.4

// 1. ��ָ Offer 57 - II. ��Ϊs��������������https://leetcode.cn/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> vv;
        if (target <= 2) return vv;
        int begin = 1, bound = target / 2;
        // ���������㷨
        while (begin <= bound) {
            int left = begin, right = left + 1;
            int sum = left + right;
            vector<int> v;
            while (sum < target) {       // ���������ۼ�ֵ��С���ұ߽�����
                right++;
                sum += right;
            }
            while (sum > target) {       // ���������ۼ�ֵ������߽�����
                sum -= left;
                left++;
            }
            if (sum == target) {         // ��ͬ�Ͳ���
                for (int i = left; i <= right; ++i) {
                    v.push_back(i);
                }
            }
            if (!v.empty()) {
                vv.push_back(v);
            }
            begin++;
        }
        // ȥ��
        set<vector<int>> s{ vv.begin(), vv.end() };
        vv = vector<vector<int>>{ s.begin(), s.end() };
        return vv;
    }
};

// 2. ��ָ Offer 52. ��������ĵ�һ�������ڵ�https://leetcode.cn/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/
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

// 3. ��ָ Offer 58 - I. ��ת����˳��https://leetcode.cn/problems/fan-zhuan-dan-ci-shun-xu-lcof/
class Solution {
public:
    string reverseWords(string s) {
        int right = s.size() - 1;
        string result;
        while (right >= 0) {
            while (right >= 0 && s[right] == ' ') right--;          // �ұ�ȥ�ո�
            if (right == -1) break;
            int left = right;
            while (left >= 0 && s[left] != ' ') left--;             // �����ַ��Ϳո񣬲��Ե�ǰleftΪ�ұ߽�
            result.append(s, left + 1, right - left);
            result += ' ';
            right = left;
        }
        result.pop_back();
        return result;
    }
};
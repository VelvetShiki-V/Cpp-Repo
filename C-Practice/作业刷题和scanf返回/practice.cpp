// 1. 回文链表  https://leetcode.cn/problems/aMhZSa/solution/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
//class Solution {
//public:
//    bool isPalindrome(ListNode* head) {
//        if (nullptr == head) return false;
//        ListNode* left = head, * right = head;
//        std::vector<int> v;
//        while (right) {
//            v.emplace_back(right->val);
//            right = right->next;
//        }
//        for (size_t i = 0; i < v.size() / 2; ++i) {
//            if (v[i] != v[v.size() - i - 1]) return false;
//        }
//        return true;
//    }
//};


// 2. 有效的变位词     https://leetcode.cn/problems/dKk3P7/
//class Solution {
//public:
//    bool isAnagram(string s, string t) {
//        std::map<char, int> m1, m2;
//        for (auto e : s) m1[e]++;
//        for (auto f : t) m2[f]++;
//        if (m1.size() != m2.size()) return false;       // 判断长度一致
//        else {
//            for (int i = 0; i < m1.size(); ++i) {       // 判断两个map的字符个数一致
//                if (m1[i] != m2[i]) return false;
//            }
//        }
//        for (int i = 0; i < s.size(); ++i) {            // 判断是否是变位词
//            if (s[i] != t[i]) return true;
//        }
//        return false;
//    }
//};

// 3. 
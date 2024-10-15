#define CRT_NOWARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//////////////////////////////////////////// 2023.4.6

// 1. 剑指 Offer II 003. 前 n 个数字二进制中 1 的个数https://leetcode.cn/problems/w3tCBm/
class Solution {
public:
    void count1(vector<int>& v, int i) {
        int count = 0;
        for (int j = 0; j < 31; ++j) {
            if (i % 2 == 1) ++count;
            i /= 2;
        }
        v.push_back(count);
    }
    vector<int> countBits(int n) {
        vector<int> v;
        for (int i = 0; i <= n; ++i) {
            count1(v, i);
        }
        return v;
    }
};

// 2. 
// 法1：对于不是bigint的处理
class Solution {
public:
    unsigned long long string_to_val(const string& s) {
        unsigned long long val = 0;
        unsigned long long multi = 1;
        for (int i = s.size() - 1; i >= 0; --i) {
            val += (s[i] - 48) * multi;
            multi *= 2;
        }
        return val;
    }
    string convert(unsigned long long& c) {
        if (c == 0) return {};
        string s;
        while (c) {
            s += (c % 2) + 48;
            c /= 2;
        }
        unsigned long long i = 0;
        reverse(s.begin(), s.end());
        for (auto& it : s) {
            if (it == 49) break;
            ++i;
        }
        if (i == 31) i = 30;
        //cout << "i: " << i << endl;
        string s2(s.begin() + i, s.end());
        //cout << "s2: " << s2 << endl;
        return s2;
    }
    string addBinary(string a, string b) {
        unsigned long long c = string_to_val(a) + string_to_val(b);
        return convert(c);
    }
};

// 3. 剑指 Offer II 012. 左右两边子数组的和相等https://leetcode.cn/problems/tvdfij/
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int total = 0;
        for (int i = 0; i < nums.size(); ++i) {
            total += nums[i];
        }
        if (!nums.empty()) {
            int leftSum = 0, rightSum = total - nums[0];
            if (leftSum == rightSum) return 0;
            for (int i = 1; i < nums.size(); ++i) {
                leftSum += nums[i - 1];
                rightSum -= nums[i];
                if (leftSum == rightSum) return i;
                //cout << leftSum << "--" << rightSum <<endl;
            }
        }
        return -1;
    }
};

// 4. 剑指 Offer II 006. 排序数组中两个数字之和https://leetcode.cn/problems/kLl5u1/
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        vector<int> rst_pair;
        while (i < j) {
            if (numbers[i] + numbers[j] == target) {
                rst_pair.emplace_back(i);
                rst_pair.emplace_back(j);
            }
            if (numbers[i] + numbers[j] < target) ++i;
            else --j;
        }
        return rst_pair;
    }
};

// 5. 剑指 Offer II 018. 有效的回文https://leetcode.cn/problems/XltzEq/
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.empty())return true;
        string str;
        for (int i = 0; i < s.size(); ++i) {
            if (!isalpha(s[i])) {
                if (s[i] >= '0' && s[i] <= '9');
                else continue;
            }
            if (s[i] <= 'Z' && s[i] >= 'A') s[i] += 32;
            str += s[i];
        }
        cout << str << endl;
        for (int i = 0, j = str.size() - 1; i <= j; ++i, --j) {
            if (str[i] != str[j]) return false;
        }
        return true;
    }
};

// 6. 剑指 Offer II 019. 最多删除一个字符得到回文https://leetcode.cn/problems/RQku0D/
class Solution {
public:
    bool validPalindrome(string s) {
        bool left = true, right = true;
        bool flag = true;
        for (int i = 0, j = s.size() - 1; i <= j; ++i) {
            if (s[i] != s[j]) {
                if (flag) {
                    --j;
                    if (i <= j && s[j] != s[i]) right = false;
                    flag = false;
                }
                else right = false;
            }
            --j;
        }
        flag = true;
        for (int i = 0, j = s.size() - 1; i <= j; --j) {
            if (s[i] != s[j]) {
                if (flag) {
                    ++i;
                    if (i <= j && s[j] != s[i]) left = false;
                    flag = false;
                }
                else left = false;
            }
            ++i;
        }
        return left || right;
    }
};

// 7. 剑指 Offer II 023. 两个链表的第一个重合节点https://leetcode.cn/problems/3u1WK4/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// 法1：哈希桶映射
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        unordered_set<ListNode*> nodeMap;
        ListNode* cur = headA;
        while (cur) {
            nodeMap.insert(cur);
            cur = cur->next;
        }
        cur = headB;
        while (cur) {
            if (nodeMap.find(cur) != nodeMap.end()) return cur;
            cur = cur->next;
        }
        return nullptr;
    }
};
// 法2：双指针指向同一节点
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* curA = headA, * curB = headB;
        while (curA != curB) {
            curA = curA == nullptr ? headB : curA->next;
            curB = curB == nullptr ? headA : curB->next;
        }
        return curA;
    }
};

// 8. 剑指 Offer II 024. 反转链表https://leetcode.cn/problems/UHnkqh/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr, * cur = head;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};
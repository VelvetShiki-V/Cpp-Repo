#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
using namespace std;

namespace HashBucket {
	template<class K>				// 取哈希值计算哈希表下标，默认将可模运算数值转换为无符号数
	struct HashKey {
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};

	template<>						// string字符存储的模板特化，计算string的ASCII值之和取模计算下标
	struct HashKey<string> {
		size_t operator()(const string& s) {
			size_t asc = 0;
			for (auto& e : s) {
				asc += e;
			}
			return asc;
		}
	};

	// 哈希结点类
	template<class K, class V>
	struct HashNode {		// 哈希表中每个成员存储的是单链表，无需排序，模运算结果相同的存储于同一下标中
		pair<K, V> m_data;
		HashNode* next;
		HashNode(const pair<K, V>& kv)
			:m_data(kv)
			,next(nullptr)
		{}
	};

	template<class K, class V, class Hash = HashKey<K>>
	class HashTable {
	public:
		typedef HashNode<K, V> Node;
		~HashTable() {			// 必须有析构函数，默认析构只会处理vector本身而不会对成员桶结点析构处理
			for (auto& e : buckets) {
				if (e) {
					Node* cur = e;
					while (cur) {		// 遍历vector，依次释放每个桶中插入的结点，并将m_size减至0
						Node* next = cur->next;
						free(cur);
						cur = next;
						--m_size;
					}
					}
			}
		}
		bool insert(const pair<K, V>& kv) {
			// 去重——冗余值不插入
			if (find(kv.first)) return false;
			// 扩容——空哈希表或负载因子到1扩容（空间利用率较高）
			Hash type;
			if (buckets.size() == 0 || m_size == buckets.size()) {		
				size_t new_size = buckets.size() == 0 ? 10 : buckets.size() * 2;	// 初始给10，后续依次为前一次m_size两倍
				vector<Node*> new_buckets;
				new_buckets.resize(new_size);
				for (size_t i = 0; i < buckets.size(); ++i) {		// 将原表结点转移至新表（避免重复new开销浪费）
					Node* cur = buckets[i];
					while (cur) {
						Node* next = cur->next;		// 备份原表当前结点的后一结点，防止当前结点头插到新表后，后续结点地址丢失
						size_t new_subcript = type(cur->m_data.first) % new_buckets.size();
						cur->next = new_buckets[new_subcript];
						new_buckets[new_subcript] = cur;
						cur = next;		// 每个桶中的结点依次头插移至新表中
					}
					buckets[i] = nullptr;
				}
				buckets.swap(new_buckets);		// 新旧表交换
			}
			// 新值头插到取模的下标中，链接到单链表头部
			size_t subscript = type(kv.first) % buckets.size();
			Node* newnode = new Node(kv);
			newnode->next = buckets[subscript];
			buckets[subscript] = newnode;
			m_size++;
			return true;
		}

		// 查找表中特定值，返回结点地址
		Node* find(const K& key) {
			if (buckets.size() == 0) return nullptr;
			Hash type;
			size_t subscript = type(key) % buckets.size();		// 取模找到对应下标，再遍历单链表，查找时间复杂度近似O(1)
			Node* cur = buckets[subscript];
			while (cur && cur->m_data.first != key) {
				cur = cur->next;
			}
			return cur;
		}

		// 删除表中已存在特定值
		bool erase(const K& key) {
			Node* del = find(key);
			if (!del) return false;		// 找不到待删值则删除失败
			else {
				Hash type;
				size_t subscript = type(key) % buckets.size();
				Node* cur = buckets[subscript];
				if (cur == del) {		// 找到分两种情况，仅一个结点或链表串
					free(del);
					buckets[subscript] = nullptr;
				}
				else {
					while (cur->next != del) {		// 将该结点前后链接
						cur = cur->next;
					}
					cur->next = del->next;
					free(del);
				}
				m_size--;
			}
			return true;
		}

		// 打印哈希表(中的每个桶结点数据)
		void print() {
			for (size_t i = 0; i < buckets.size(); ++i) {
				if (Node * cur = buckets[i]) {
					cout << i << ": ";
					while (cur) {
						cout << cur->m_data.first << " ";
						cur = cur->next;
					 }
					cout << endl;
				}
				else {
					cout << i << ": NULL" << endl;
				}
			}
		}

		size_t size() {		// 获取哈希表中的总有效数据个数
			return m_size;
		}

	private:
		vector<Node*> buckets;		// 哈希表底层是vector，其中每个下标对应数据类型为单链表
		size_t m_size = 0;			// 记录表中有效数据个数
	};
}
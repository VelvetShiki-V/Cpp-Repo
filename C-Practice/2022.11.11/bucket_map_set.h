#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
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
	template<class T>
	struct HashNode {		// 哈希表中每个成员存储的是单链表，无需排序，模运算结果相同的存储于同一下标中
		T m_data;
		HashNode<T>* next;
		HashNode(const T& data)
			:m_data(data)
			,next(nullptr)
		{}
	};

	// 使用哈希类前置声明
	template<class K, class T, class Hash, class KeyInT>
	class HashTable;
	// 哈希表迭代器类
	template<class K, class T, class Ref, class Ptr, class Hash, class KeyInT>
	struct __hash_iterator {
		typedef HashNode<T> Node;
		typedef __hash_iterator<K, T, Ref, Ptr, Hash, KeyInT> iterator;
		typedef HashTable<K, T, Hash, KeyInT> HT;
		Node* m_node;
		HT* m_table;
		__hash_iterator(Node* node = nullptr, HT* table = nullptr)
			:m_node(node)
			,m_table(table)
		{}
		// 单向迭代器仅支持自增，没有自减
		iterator& operator++() {
			Node* cur = m_node;
			cur = cur->next;
			if (cur) {			// 当前桶迭代
				m_node = cur;
				return this;
			}
			else {				// 找下一个桶
				KeyInT type;
				size_t location = m_table->bucket(type(m_node->m_data));
				++location;
				while (location < m_table->max_size() && !m_table->m_buckets[location])
					++location;
				if (location == m_table->max_size()) {
					m_node = nullptr;
					return *this;
				}
				m_node = m_table->m_buckets[location];
				return *this;
			}
		}
		Ref operator*() {
			return m_node->m_data;
		}
		Ptr operator->() {
			return &m_node->m_data;
		}
		bool operator!=(const iterator& obj) const {
			return m_node != obj.m_node;
		}
		bool operator==(const iterator& obj) const {
			return m_node == obj.m_node;
		}
	};

	template<class K, class T, class Hash, class KeyInT>
	class HashTable {
	public:
		typedef HashNode<T> Node;
		typedef __hash_iterator<K, T, T&, T*, Hash, KeyInT> iterator;
		typedef __hash_iterator<K, T, const T&, const T*, Hash, KeyInT> const_iterator;
		friend iterator;
		~HashTable() {			// 必须有析构函数，默认析构只会处理vector本身而不会对成员桶结点析构处理
			for (auto& e : m_buckets) {
				if (e) {
					Node* cur = e;
					while (cur) {		// 遍历vector，依次释放每个桶中插入的结点，并将m_size减至0
						Node* next = cur->next;
						delete cur;
						cur = next;
						--m_size;
					}
				}
			}
		}

		// 迭代器函数
		iterator begin() {
			size_t location = 0;
			while (location < max_size() && !m_buckets[location]) ++location;
			return iterator(m_buckets[location], this);
		}
		const_iterator cbegin() {
			return begin();
		}
		iterator end() {
			return iterator(nullptr);
		}
		const_iterator cend() {
			return iterator(nullptr);
		}

		pair<iterator, bool> insert(const T& data) {
			Hash transfer;
			KeyInT type;
			// 去重——冗余值不插入
			if (find(type(data)) != iterator(nullptr)) {
				return make_pair(iterator(nullptr), false);
			}
			// 扩容——空哈希表或负载因子到1扩容（空间利用率较高）
			if (m_buckets.size() == 0 || m_size == m_buckets.size()) {
				size_t new_size = m_buckets.size() == 0 ? 10 : m_buckets.size() * 2;	// 初始给10，后续依次为前一次m_size两倍
				vector<Node*> new_buckets;
				new_buckets.resize(new_size);
				for (size_t i = 0; i < m_buckets.size(); ++i) {		// 将原表结点转移至新表（避免重复new开销浪费）
					Node* cur = m_buckets[i];
					while (cur) {
						Node* next = cur->next;		// 备份原表当前结点的后一结点，防止当前结点头插到新表后，后续结点地址丢失
						size_t new_subcript = transfer(type(cur->m_data)) % new_buckets.size();
						cur->next = new_buckets[new_subcript];
						new_buckets[new_subcript] = cur;
						cur = next;		// 每个桶中的结点依次头插移至新表中
					}
					m_buckets[i] = nullptr;
				}
				m_buckets.swap(new_buckets);		// 新旧表交换
			}
			// 新值头插到取模的下标中，链接到单链表头部
			size_t subscript = transfer(type(data)) % m_buckets.size();
			Node* newnode = new Node(data);
			newnode->next = m_buckets[subscript];
			m_buckets[subscript] = newnode;
			m_size++;
			return make_pair(iterator(newnode), true);
		}

		// 查找表中特定值，返回结点地址
		iterator find(const K& key) {
			if (m_buckets.size() == 0) return iterator(nullptr);
			Hash transfer;
			KeyInT type;
			size_t subscript = transfer(key) % m_buckets.size();		// 取模找到对应下标，再遍历单链表，查找时间复杂度近似O(1)
			Node* cur = m_buckets[subscript];
			while (cur && type(cur->m_data) != key) {
				cur = cur->next;
			}
			return iterator(cur);
		}

		// 删除表中已存在特定值
		size_t erase(const K& key) {
			Node* del = find(key);
			if (!del) return 0;		// 找不到待删值则删除失败
			else {
				Hash transfer;
				size_t subscript = transfer(key) % m_buckets.size();
				Node* cur = m_buckets[subscript];
				if (cur == del) {		// 找到分两种情况，仅一个结点或链表串
					delete del;
					m_buckets[subscript] = nullptr;
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
			return 1;
		}

		// 获取哈希表中的总有效数据个数
		size_t size() {	
			return m_size;
		}
		// 哈希表总大小
		size_t max_size() const {
			return m_buckets.size();
		}
		// 判空
		bool empty() {
			return !size();
		}
		// 统计当前哈希表桶个数
		size_t bucket_count() const {
			int bucketNums = 0;
			for (size_t i = 0; i < m_buckets.size(); ++i) {
				if (Node* cur = m_buckets[i]) {
					bucketNums++;
				}
			}
			return bucketNums;
		}

		// 统计哈希表最大容纳桶容量
		size_t max_bucket_count() const {
			return m_buckets.size();
		}

		// 统计某个桶中的结点个数
		size_t bucket_size(size_t n) const {
			assert(n < m_buckets.size());
			int cnt = 0;
			Node* cur = m_buckets[n];
			while (cur) {
				cnt++;
				cur = cur->next;
			}
			return cnt;
		}

		// 根据所给key值定位桶编号（从0开始）
		size_t bucket(const K& k)  {
			iterator val = find(k);
			assert(val != iterator(nullptr));
			KeyInT type;
			Hash transfer;
			size_t location = transfer(type(val.m_node->m_data)) % m_buckets.size();
			return location;
		}

		// 得到负载因子
		float load_factor() const {
			return (float)m_size / (float)m_buckets.size();
		}

		// 手动扩容
		void rehash(size_t n) {
			if (n > m_buckets.size()) {
				Hash transfer;
				KeyInT type;
				vector<Node*> new_buckets;
				new_buckets.resize(n);
				for (size_t i = 0; i < m_buckets.size(); ++i) {		// 将原表结点转移至新表（避免重复new开销浪费）
					Node* cur = m_buckets[i];
					while (cur) {
						Node* next = cur->next;		// 备份原表当前结点的后一结点，防止当前结点头插到新表后，后续结点地址丢失
						size_t new_subcript = transfer(type(cur->m_data)) % new_buckets.size();
						cur->next = new_buckets[new_subcript];
						new_buckets[new_subcript] = cur;
						cur = next;		// 每个桶中的结点依次头插移至新表中
					}
					m_buckets[i] = nullptr;
				}
				m_buckets.swap(new_buckets);		// 新旧表交换
			}
		}

	private:
		vector<Node*> m_buckets;		// 哈希表底层是vector，其中每个下标对应数据类型为单链表
		size_t m_size = 0;			// 记录表中有效数据个数
	};
}
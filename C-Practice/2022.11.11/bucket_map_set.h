#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

namespace HashBucket {
	template<class K>				// ȡ��ϣֵ�����ϣ���±꣬Ĭ�Ͻ���ģ������ֵת��Ϊ�޷�����
	struct HashKey {
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};

	template<>						// string�ַ��洢��ģ���ػ�������string��ASCIIֵ֮��ȡģ�����±�
	struct HashKey<string> {
		size_t operator()(const string& s) {
			size_t asc = 0;
			for (auto& e : s) {
				asc += e;
			}
			return asc;
		}
	};

	// ��ϣ�����
	template<class T>
	struct HashNode {		// ��ϣ����ÿ����Ա�洢���ǵ�������������ģ��������ͬ�Ĵ洢��ͬһ�±���
		T m_data;
		HashNode<T>* next;
		HashNode(const T& data)
			:m_data(data)
			,next(nullptr)
		{}
	};

	// ʹ�ù�ϣ��ǰ������
	template<class K, class T, class Hash, class KeyInT>
	class HashTable;
	// ��ϣ���������
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
		// �����������֧��������û���Լ�
		iterator& operator++() {
			Node* cur = m_node;
			cur = cur->next;
			if (cur) {			// ��ǰͰ����
				m_node = cur;
				return this;
			}
			else {				// ����һ��Ͱ
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
		~HashTable() {			// ����������������Ĭ������ֻ�ᴦ��vector���������Գ�ԱͰ�����������
			for (auto& e : m_buckets) {
				if (e) {
					Node* cur = e;
					while (cur) {		// ����vector�������ͷ�ÿ��Ͱ�в���Ľ�㣬����m_size����0
						Node* next = cur->next;
						delete cur;
						cur = next;
						--m_size;
					}
				}
			}
		}

		// ����������
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
			// ȥ�ء�������ֵ������
			if (find(type(data)) != iterator(nullptr)) {
				return make_pair(iterator(nullptr), false);
			}
			// ���ݡ����չ�ϣ��������ӵ�1���ݣ��ռ������ʽϸߣ�
			if (m_buckets.size() == 0 || m_size == m_buckets.size()) {
				size_t new_size = m_buckets.size() == 0 ? 10 : m_buckets.size() * 2;	// ��ʼ��10����������Ϊǰһ��m_size����
				vector<Node*> new_buckets;
				new_buckets.resize(new_size);
				for (size_t i = 0; i < m_buckets.size(); ++i) {		// ��ԭ����ת�����±������ظ�new�����˷ѣ�
					Node* cur = m_buckets[i];
					while (cur) {
						Node* next = cur->next;		// ����ԭ��ǰ���ĺ�һ��㣬��ֹ��ǰ���ͷ�嵽�±�󣬺�������ַ��ʧ
						size_t new_subcript = transfer(type(cur->m_data)) % new_buckets.size();
						cur->next = new_buckets[new_subcript];
						new_buckets[new_subcript] = cur;
						cur = next;		// ÿ��Ͱ�еĽ������ͷ�������±���
					}
					m_buckets[i] = nullptr;
				}
				m_buckets.swap(new_buckets);		// �¾ɱ���
			}
			// ��ֵͷ�嵽ȡģ���±��У����ӵ�������ͷ��
			size_t subscript = transfer(type(data)) % m_buckets.size();
			Node* newnode = new Node(data);
			newnode->next = m_buckets[subscript];
			m_buckets[subscript] = newnode;
			m_size++;
			return make_pair(iterator(newnode), true);
		}

		// ���ұ����ض�ֵ�����ؽ���ַ
		iterator find(const K& key) {
			if (m_buckets.size() == 0) return iterator(nullptr);
			Hash transfer;
			KeyInT type;
			size_t subscript = transfer(key) % m_buckets.size();		// ȡģ�ҵ���Ӧ�±꣬�ٱ�������������ʱ�临�ӶȽ���O(1)
			Node* cur = m_buckets[subscript];
			while (cur && type(cur->m_data) != key) {
				cur = cur->next;
			}
			return iterator(cur);
		}

		// ɾ�������Ѵ����ض�ֵ
		size_t erase(const K& key) {
			Node* del = find(key);
			if (!del) return 0;		// �Ҳ�����ɾֵ��ɾ��ʧ��
			else {
				Hash transfer;
				size_t subscript = transfer(key) % m_buckets.size();
				Node* cur = m_buckets[subscript];
				if (cur == del) {		// �ҵ��������������һ����������
					delete del;
					m_buckets[subscript] = nullptr;
				}
				else {
					while (cur->next != del) {		// ���ý��ǰ������
						cur = cur->next;
					}
					cur->next = del->next;
					free(del);
				}
				m_size--;
			}
			return 1;
		}

		// ��ȡ��ϣ���е�����Ч���ݸ���
		size_t size() {	
			return m_size;
		}
		// ��ϣ���ܴ�С
		size_t max_size() const {
			return m_buckets.size();
		}
		// �п�
		bool empty() {
			return !size();
		}
		// ͳ�Ƶ�ǰ��ϣ��Ͱ����
		size_t bucket_count() const {
			int bucketNums = 0;
			for (size_t i = 0; i < m_buckets.size(); ++i) {
				if (Node* cur = m_buckets[i]) {
					bucketNums++;
				}
			}
			return bucketNums;
		}

		// ͳ�ƹ�ϣ���������Ͱ����
		size_t max_bucket_count() const {
			return m_buckets.size();
		}

		// ͳ��ĳ��Ͱ�еĽ�����
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

		// ��������keyֵ��λͰ��ţ���0��ʼ��
		size_t bucket(const K& k)  {
			iterator val = find(k);
			assert(val != iterator(nullptr));
			KeyInT type;
			Hash transfer;
			size_t location = transfer(type(val.m_node->m_data)) % m_buckets.size();
			return location;
		}

		// �õ���������
		float load_factor() const {
			return (float)m_size / (float)m_buckets.size();
		}

		// �ֶ�����
		void rehash(size_t n) {
			if (n > m_buckets.size()) {
				Hash transfer;
				KeyInT type;
				vector<Node*> new_buckets;
				new_buckets.resize(n);
				for (size_t i = 0; i < m_buckets.size(); ++i) {		// ��ԭ����ת�����±������ظ�new�����˷ѣ�
					Node* cur = m_buckets[i];
					while (cur) {
						Node* next = cur->next;		// ����ԭ��ǰ���ĺ�һ��㣬��ֹ��ǰ���ͷ�嵽�±�󣬺�������ַ��ʧ
						size_t new_subcript = transfer(type(cur->m_data)) % new_buckets.size();
						cur->next = new_buckets[new_subcript];
						new_buckets[new_subcript] = cur;
						cur = next;		// ÿ��Ͱ�еĽ������ͷ�������±���
					}
					m_buckets[i] = nullptr;
				}
				m_buckets.swap(new_buckets);		// �¾ɱ���
			}
		}

	private:
		vector<Node*> m_buckets;		// ��ϣ��ײ���vector������ÿ���±��Ӧ��������Ϊ������
		size_t m_size = 0;			// ��¼������Ч���ݸ���
	};
}
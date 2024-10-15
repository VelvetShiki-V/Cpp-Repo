#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
using namespace std;

namespace HashBucket1 {
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
	template<class K, class V>
	struct HashNode {		// ��ϣ����ÿ����Ա�洢���ǵ�������������ģ��������ͬ�Ĵ洢��ͬһ�±���
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
		bool insert(const pair<K, V>& kv) {
			// ȥ�ء�������ֵ������
			if (find(kv.first)) return false;
			// ���ݡ����չ�ϣ��������ӵ�1���ݣ��ռ������ʽϸߣ�
			Hash type;
			if (m_buckets.size() == 0 || m_size == m_buckets.size()) {		
				size_t new_size = m_buckets.size() == 0 ? 10 : m_buckets.size() * 2;	// ��ʼ��10����������Ϊǰһ��m_size����
				vector<Node*> new_buckets;
				new_buckets.resize(new_size);
				for (size_t i = 0; i < m_buckets.size(); ++i) {		// ��ԭ����ת�����±������ظ�new�����˷ѣ�
					Node* cur = m_buckets[i];
					while (cur) {
						Node* next = cur->next;		// ����ԭ��ǰ���ĺ�һ��㣬��ֹ��ǰ���ͷ�嵽�±�󣬺�������ַ��ʧ
						size_t new_subcript = type(cur->m_data.first) % new_buckets.size();
						cur->next = new_buckets[new_subcript];
						new_buckets[new_subcript] = cur;
						cur = next;		// ÿ��Ͱ�еĽ������ͷ�������±���
					}
					m_buckets[i] = nullptr;
				}
				m_buckets.swap(new_buckets);		// �¾ɱ���
			}
			// ��ֵͷ�嵽ȡģ���±��У����ӵ�������ͷ��
			size_t subscript = type(kv.first) % m_buckets.size();
			Node* newnode = new Node(kv);
			newnode->next = m_buckets[subscript];
			m_buckets[subscript] = newnode;
			m_size++;
			return true;
		}

		// ���ұ����ض�ֵ�����ؽ���ַ
		Node* find(const K& key) {
			if (m_buckets.size() == 0) return nullptr;
			Hash type;
			size_t subscript = type(key) % m_buckets.size();		// ȡģ�ҵ���Ӧ�±꣬�ٱ�������������ʱ�临�ӶȽ���O(1)
			Node* cur = m_buckets[subscript];
			while (cur && cur->m_data.first != key) {
				cur = cur->next;
			}
			return cur;
		}

		// ɾ�������Ѵ����ض�ֵ
		bool erase(const K& key) {
			Node* del = find(key);
			if (!del) return false;		// �Ҳ�����ɾֵ��ɾ��ʧ��
			else {
				Hash type;
				size_t subscript = type(key) % m_buckets.size();
				Node* cur = m_buckets[subscript];
				if (cur == del) {		// �ҵ��������������һ����������
					free(del);
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
			return true;
		}

		// ��ӡ��ϣ��(�е�ÿ��Ͱ�������)
		void print() {
			int bucket = 0;
			pair<int, int> max, tmp;	// ÿ��ͰԪ�ظ����뵱ǰ�Ͱ�Ƚ�
			for (size_t i = 0; i < m_buckets.size(); ++i) {
				if (Node * cur = m_buckets[i]) {
					cout << i << ": ";
					tmp.first = i;
					while (cur) {
						cout << cur->m_data.first << " ";
						cur = cur->next;
						tmp.second++;
					 }
					bucket++;
					cout << endl;
				}
				//else {
				//	cout << i << ": NULL" << endl;
				//}
				if (tmp.second >= max.second) {
					max.first = tmp.first;
					max.second = tmp.second;
				}
				tmp = make_pair(0, 0);
			}
			cout << "��" << bucket << "��Ͱ" << endl;
			cout << "���һ���Ͱ�±�Ϊ: " << max.first << "����Ϊ: " << max.second << endl;
			cout << "Ͱƽ������: " << (double)size() / (double)bucket << endl;
			cout << "��������: " << (double)size() / (double)m_buckets.size() << endl;
		}

		size_t size() {		// ��ȡ��ϣ���е�����Ч���ݸ���
			return m_size;
		}

	private:
		vector<Node*> m_buckets;		// ��ϣ��ײ���vector������ÿ���±��Ӧ��������Ϊ������
		size_t m_size = 0;			// ��¼������Ч���ݸ���
	};
}
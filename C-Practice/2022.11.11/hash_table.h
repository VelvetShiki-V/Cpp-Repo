#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

enum status {
	EMPTY,
	EXIST,
	DELETE
};

template<class K, class V>
struct HashData {
	pair<K, V> m_data;
	status m_status = EMPTY;
};

template<class K>
struct HashKey {
	size_t operator()(const K& key) {
		return (size_t)key;
	}
};

template<>		// string��ģ���ػ�
struct HashKey<string> {
	// BKDR�㷨�Ż�ȥ������ASCIIֵ
	size_t operator()(const string& s) {
		size_t asc = 0;
		for (auto& e : s) {
			asc *= 131;
			asc += e;
		}
		return asc;
	}
};

template<class K, class V, class Hash = HashKey<K>>		// KΪ��ȡֵ��Vһ��ͳ�ƴ�����HashΪȡģת���ķº�����Ĭ��size_t�������ػ�
class HashTable {
public:
	bool insert(const pair<K, V>& kv) {
		// ����������Ӵﵽ�ٽ�ֵ����Ϊ�ձ���������ݲ���ֵ�����±������׶Σ�������ȫ��
		if (find(kv.first)) return false;		// ��ֹ����
		if (m_table.size() == 0 || (size * 10 / m_table.size() >= 7)) {
			size_t new_size = m_table.size() == 0 ? 10 : m_table.size() * 2;
			HashTable<K, V, Hash> new_table;
			new_table.m_table.resize(new_size);
			for (auto& e : m_table) {
				if (e.m_status == EXIST) {
					new_table.insert(e.m_data);
				}
			}
			m_table.swap(new_table.m_table);
		}
		// �����û������ִ�в��벽�裬�����±��Ӧ��ֵ��״̬����Ϊ����̬EXIST
		Hash hashval;
		size_t subscript = hashval(kv.first) % m_table.size();		// ������ĸ���keyֵʹ�÷º���ǿת��size_t������ȡģ
		size_t flag = subscript;
		size_t i = 0;
		while (m_table[subscript].m_status == EXIST) {				// ����ȡģҲ������������ӳ�䵽�±���
			i++;
			subscript += i * i;		// ����̽��
			//subscript++;			// ����̽��
			subscript %= m_table.size();
			if (flag == subscript) return false;						// ��ֹ����ȫ��DELETE��EXIST״����û��EMPTY�����ʧ�ܣ����ñ��λ
		}
		m_table[subscript].m_data = kv;
		m_table[subscript].m_status = EXIST;
		size++;
		return true;
	}

	HashData<K, V>* find(const K& key) {
		if (m_table.size() == 0) return nullptr;
		Hash hashval;
		size_t subscript = hashval(key) % m_table.size();
		while (m_table[subscript].m_data.first != key && m_table[subscript].m_status != EMPTY) {
			subscript++;
			subscript %= m_table.size();
		}
		if (m_table[subscript].m_status == EMPTY) return nullptr;
		else if (m_table[subscript].m_status == DELETE) return nullptr;		// �Ѳ���ֵ�����ҵ������ؿ�ָ��
		else return &m_table[subscript];
	}

	void erase(const K& key) {
		HashData<K, V>* aim = nullptr;
		assert(aim = find(key));		// ����ֵ���ڲ���ɾ��
		aim->m_status = DELETE;
		--size;
	}

	void print() {
		assert(m_table.size());
		for (size_t i = 0; i < m_table.size(); ++i) {
			if (m_table[i].m_status == EXIST) {
				cout << i << " : first->" << m_table[i].m_data.first /*<< "  second-> " << m_table[i].m_data.second*/ << endl;
			}
		}
	}
private:
	vector<HashData<K, V>> m_table;
	size_t size = 0;
};
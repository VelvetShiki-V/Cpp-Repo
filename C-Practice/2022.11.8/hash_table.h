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

template<>		// string类模板特化
struct HashKey<string> {
	// BKDR算法优化去除冗余ASCII值
	size_t operator()(const string& s) {
		size_t asc = 0;
		for (auto& e : s) {
			asc *= 131;
			asc += e;
		}
		return asc;
	}
};

template<class K, class V, class Hash = HashKey<K>>		// K为存取值，V一般统计次数，Hash为取模转换的仿函数，默认size_t，可以特化
class HashTable {
public:
	bool insert(const pair<K, V>& kv) {
		// 如果负载因子达到临界值，或为空表，则进入扩容并数值插入新表，交换阶段，不可能全满
		if (find(kv.first)) return false;		// 防止冗余
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
		// 如果表没满，则执行插入步骤，并将下标对应数值中状态设置为存在态EXIST
		Hash hashval;
		size_t subscript = hashval(kv.first) % m_table.size();		// 将传入的各种key值使用仿函数强转成size_t类型以取模
		size_t flag = subscript;
		size_t i = 0;
		while (m_table[subscript].m_status == EXIST) {				// 负数取模也得正数，可以映射到下标上
			i++;
			subscript += i * i;		// 二次探测
			//subscript++;			// 线性探测
			subscript %= m_table.size();
			if (flag == subscript) return false;						// 防止表中全是DELETE或EXIST状况，没有EMPTY则插入失败，设置标记位
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
		else if (m_table[subscript].m_status == DELETE) return nullptr;		// 已擦除值不算找到，返回空指针
		else return &m_table[subscript];
	}

	void erase(const K& key) {
		HashData<K, V>* aim = nullptr;
		assert(aim = find(key));		// 该数值存在才能删除
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
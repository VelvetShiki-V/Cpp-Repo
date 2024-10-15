#pragma once
#include<iostream>
#include<vector>
using namespace std;

enum status {
	EMPTY,
	EXIST,
	DELETE
};

template<class K, class V>
struct HashData {
	pair<K, V> m_data;
	status m_status;
};

template<class K, class V>
class HashTable {
public:
	bool insert(const pair<K, V>& kv) {
		if (m_table.size() == 0 || (size * 10 / m_table.size() >= 7)) {
			size_t new_size = m_table.size() == 0 ? 10 : m_table.size() * 2;
			HashTable<K, V> new_table;
			new_table.m_table.resize(new_size);
			for (auto& e : m_table) {
				if (e.m_status == EXIST) {
					new_table.insert(e.m_data);
				}
			}
			m_table.swap(new_table.m_table);
		}
		size_t subscript = kv.first % m_table.size();
		while (m_table[subscript].m_status == EXIST) {
			subscript++;
			subscript %= m_table.size();
		}
		m_table[subscript].m_data = kv;
		m_table[subscript].m_status = EXIST;
		size++;
		return true;
	}
private:
	vector<HashData<K, V>> m_table;
	size_t size = 0;
};
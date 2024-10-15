#pragma once
#include "bucket_map_set.h"

namespace myhash {
	template<class K, class V, class Hash = HashBucket::HashKey<K>>
	class unordered_map {
	public:
		struct UnMapKeyInT {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
		typedef typename HashBucket::HashTable<K, pair<K, V>, Hash, UnMapKeyInT>::iterator iterator;
		typedef typename HashBucket::HashTable<K, pair<K, V>, Hash, UnMapKeyInT>::const_iterator const_iterator;
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return m_hash_table.insert(kv);
		}
		iterator find(const K& key) {
			return m_hash_table.find(key);
		}
		iterator begin() {
			return m_hash_table.begin();
		}
		const_iterator cbegin() {
			return m_hash_table.cbegin();
		}
		iterator end() {
			return m_hash_table.end();
		}
		const_iterator cend() {
			return m_hash_table.cend();
		}
		V& operator[](const K& key) {
			iterator kv = find(key);
			if (kv != iterator(nullptr)) return kv.m_node->m_data.second;
			else {
				pair<iterator, bool> p = insert(make_pair(key, V()));
				if (p.second) {
					return p.first.m_node->m_data.second;
				}
			}
		}

		size_t size() {
			return m_hash_table.size();
		}

		bool empty() {
			return m_hash_table.empty();
		}


	private:
		HashBucket::HashTable<K, pair<K, V>, Hash, UnMapKeyInT> m_hash_table;
	};

	template<class K, class Hash = HashBucket::HashKey<K>>
	class unordered_set {
	public:
		struct UnSetKeyInT {
			const K& operator()(const K& key) {
				return key;
			}
		};
		typedef typename HashBucket::HashTable<K, K, Hash, UnSetKeyInT>::iterator iterator;
		typedef typename HashBucket::HashTable<K, K, Hash, UnSetKeyInT>::const_iterator const_iterator;

	private:
		HashBucket::HashTable<K, K, Hash, UnSetKeyInT> m_hash_table;
	};
}
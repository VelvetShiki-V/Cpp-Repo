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
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return m_hash_table.insert(kv);
		}
		iterator find(const K& key) {
			return m_hash_table.find(key);
		}
		iterator begin() {
			return m_hash_table.begin();
		}
		iterator end() {
			return m_hash_table.end();
		}
		V& operator[](const K& key) {
			pair<iterator, bool> flag = insert(make_pair(key, V()));
			return flag.first->second;		// 等价于first.m_node->m_data.second
			// 可简写为return (insert(make_pair(key, V()))).first->second;
		}
		size_t erase(const K& key) {
			return m_hash_table.erase(key);
		}
		size_t size() const {
			return m_hash_table.size();
		}
		size_t max_size() const {
			return m_hash_table.max_size();
		}
		bool empty() const {
			return m_hash_table.empty();
		}
		size_t bucket_count() const {
			return m_hash_table.bucket_count();
		}
		size_t max_bucket_count() const {
			return m_hash_table.max_bucket_count();
		}
		size_t bucket_size(size_t n) const {
			return m_hash_table.bucket_size(n);
		}
		size_t bucket(const K& k) {
			return m_hash_table.bucket(k);
		}
		float load_factor() const {
			return m_hash_table.load_factor();
		}
		void rehash(size_t n) {
			return m_hash_table.rehash(n);
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
		pair<iterator, bool> insert(const K& key) {
			return m_hash_table.insert(key);
		}
		iterator find(const K& key) {
			return m_hash_table.find(key);
		}
		iterator begin() {
			return m_hash_table.begin();
		}
		iterator end() {
			return m_hash_table.end();
		}
		size_t erase(const K& key) {
			return m_hash_table.erase(key);
		}
		size_t size() const {
			return m_hash_table.size();
		}
		size_t max_size() const {
			return m_hash_table.max_size();
		}
		bool empty() const {
			return m_hash_table.empty();
		}
		size_t bucket_count() const {
			return m_hash_table.bucket_count();
		}
		size_t max_bucket_count() const {
			return m_hash_table.max_bucket_count();
		}
		size_t bucket_size(size_t n) const {
			return m_hash_table.bucket_size(n);
		}
		size_t bucket(const K& key) {
			return m_hash_table.bucket(key);
		}
		float load_factor() const {
			return m_hash_table.load_factor();
		}
		void rehash(size_t n) {
			return m_hash_table.rehash(n);
		}
	private:
		HashBucket::HashTable<K, K, Hash, UnSetKeyInT> m_hash_table;
	};
}
#pragma once
#include<vector>
#include"map_set_tree.h"

namespace my_map_set {
	template<class K, class V>
	class map {
	public:
		struct KeyInT {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
		typedef typename RBTree<K, pair<K, V>, KeyInT>::iterator iterator;
		typedef typename RBTree<K, pair<K, V>, KeyInT>::const_iterator const_iterator;
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return m_tree.insert(kv);
		}
		iterator begin() {
			return m_tree.begin();
		}
		const_iterator cbegin() {
			return m_tree.cbegin();
		}
		iterator end() {
			return m_tree.end();
		}
		const_iterator cend() {
			return m_tree.cend();
		}
		V& operator[](const K& key) {
			pair<iterator, bool> k = insert(make_pair(key, V()));
			return k.first->second;
		}
	private:
		RBTree<K, pair<K, V>, KeyInT> m_tree;
	};

	template<class K>
	class set {
	public:
		struct KeyInT {
			const K& operator()(const K& k) {
				return k;
			}
		};
		typedef typename RBTree<K, K, KeyInT>::iterator iterator;
		typedef typename RBTree<K, K, KeyInT>::const_iterator const_iterator;
		pair<iterator, bool> insert(const K& k) {
			return m_tree.insert(k);
		}
		iterator begin() {
			return m_tree.begin();
		}
		const_iterator cbegin() {
			return m_tree.cbegin();
		}
		iterator end() {
			return m_tree.end();
		}
		const_iterator cend() {
			return m_tree.cend();
		}
	private:
		RBTree<K, K, KeyInT> m_tree;
	};
}
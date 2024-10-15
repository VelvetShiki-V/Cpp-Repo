#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<assert.h>
#include<queue>
using namespace std;

namespace key {
	template<class K>
	struct BSTNode {
		K key;
		BSTNode* left;
		BSTNode* right;
		BSTNode(const K& x)
			:key(x)
			, left(nullptr)
			, right(nullptr)
		{}
		//~BSTNode() {
		//	key = 0;
		//	free(left); left = nullptr;
		//	free(right); right = nullptr;
		//}
	};

	template<class K>
	class Binary_Search_Tree {
	public:
		typedef BSTNode<K> Node;
		// 默认构造
		Binary_Search_Tree() = default;		// 强制编译器生成默认构造函数C++11
		// 拷贝构造
		Binary_Search_Tree(const Binary_Search_Tree<K>& b) {
			m_root = m_copy(b.m_root);
		}

		// 析构
		~Binary_Search_Tree() {
			Destroy(m_root);
		}

		// 赋值重载
		Binary_Search_Tree<K>& operator=(Binary_Search_Tree<K> t) {
			swap(m_root, t.m_root);
			return *this;
		}

		// insert循环版本
		bool insert(const K& x) {
			if (m_root == nullptr) {
				m_root = new Node(x);
				return true;
			}
			Node* cur = m_root, * parent = cur;
			while (cur) {
				if (x < cur->key) {
					parent = cur;
					cur = cur->left;
				}
				else if (x > cur->key) {
					parent = cur;
					cur = cur->right;
				}
				else {
					return false;
				}
			}
			cur = new Node(x);
			if (x < parent->key) parent->left = cur;
			if (x > parent->key) parent->right = cur;
			return true;
		}

		// insert递归版本
		bool insertR(const K& x) {
			return m_insertR(m_root, x);
		}

		// find循环版本
		bool find(const K& x) {
			if (m_root == nullptr) return false;
			Node* cur = m_root;
			while (cur) {
				if (x < cur->key) cur = cur->left;
				else if (x > cur->key) cur = cur->right;
				else if (x == cur->key) return true;
			}
			return false;
		}
		Node* find_pos(const K& x) {
			if (m_root == nullptr) return nullptr;
			Node* cur = m_root;
			while (cur) {
				if (x < cur->key) cur = cur->left;
				else if (x > cur->key) cur = cur->right;
				else if (x == cur->key) return cur;
			}
			return nullptr;
		}

		// find递归版本
		bool findR(const K& x) {
			return m_findR(m_root, x);
		}

		// erase循环版本
		bool erase(const K& x) {
			Node* parent = nullptr, * cur = m_root;
			while (cur) {
				if (x > cur->key) {
					parent = cur;
					cur = cur->right;
				}
				else if (x < cur->key) {
					parent = cur;
					cur = cur->left;
				}
				else if (x == cur->key) break;
			}
			if (cur == nullptr) return false;
			// case1: 单子树为空
			if (cur->left == nullptr) {					// 左子树为空
				if (cur == m_root) {					// 如果待删结点为根结点，修正根结点位置至非空子结点
					m_root = cur->right;
				}
				else {									// 判断待删结点位于父节点左侧或右侧
					if (parent->left == cur) {			// 父左子为待删结点，则让左子树托管待删结点右子树
						parent->left = cur->right;
					}
					else {								// 否则使父右子树托管待删结点右子树
						parent->right = cur->right;
					}
				}
				delete cur;
				cur = nullptr;
			}
			else if (cur->right == nullptr) {			// 右树为空同理
				if (cur == m_root) {
					m_root = cur->left;
				}
				else {
					if (parent->left == cur) {
						parent->left = cur->left;
					}
					else {
						parent->right = cur->left;
					}
				}
				delete cur;
				cur = nullptr;
			}
			// case2:左右子树都不为空——替换法（使用右树最小结点）
			else {
				Node* min = cur->right, * minprt = cur;		// 待删结点可能为根，或第二层结点，不能将minprt给nullptr
				while (min->left != nullptr) {	// 找右子树中的最小结点
					minprt = min;
					min = min->left;
				}
				if (minprt->left == min) minprt->left = min->right;		// 判断待删结点在minprt左侧或右侧，将孙子树链接
				else minprt->right = min->right;	// 不管最小结点右有无右子树，都让父结点继承
				swap(min->key, cur->key);			// 最小结点与待删结点交换，并释放
				delete min;
				min = nullptr;
			}
			return true;
		}

		// erase递归版本
		bool eraseR(const K& x) {
			return m_eraseR(m_root, x);
		}

		void Inorder() {
			m_Inorder(m_root);
		}

		void empty() {
			if (m_root == nullptr) cout << "空树" << endl;
			else cout << "非空" << endl;
		}

	private:
		// 方法
		// 前序拷贝
		Node* m_copy(Node* root) {
			if (root == nullptr) return nullptr;
			Node* copyroot = new Node(root->key);
			copyroot->left = m_copy(root->left);
			copyroot->right = m_copy(root->right);
			return copyroot;
		}
		// 后序销毁
		void Destroy(Node*& root) {
			if (root == nullptr) return;
			Destroy(root->left);
			Destroy(root->right);
			delete root;
			root = nullptr;
		}

		// 中序遍历
		void m_Inorder(Node* root) {
			if (root == nullptr) return;
			m_Inorder(root->left);
			cout << root->key << " ";
			m_Inorder(root->right);
		}

		// find递归
		bool m_findR(Node* root, const K& x) {
			if (root == nullptr) return false;
			if (x < root->key) return m_findR(root->left, x);
			else if (x > root->key) return m_findR(root->right, x);
			else return true;
		}

		// insert递归
		bool m_insertR(Node*& root, const K& key) {
			if (root == nullptr) {
				root = new Node(key);
				return true;
			}
			if (key > root->key) return m_insertR(root->right, key);
			else if (key < root->key) return m_insertR(root->left, key);
			else return false;
		}

		// erase递归
		bool m_eraseR(Node*& root, const K& key) {
			if (root == nullptr) return false;
			if (key < root->key) return m_eraseR(root->left, key);
			else if (key > root->key) return m_eraseR(root->right, key);
			else {
				Node* tmp = root;
				if (root->left == nullptr) {
					root = root->right;
				}
				else if (root->right == nullptr) {
					root = root->left;
				}
				else {
					Node* min = root->right;
					while (min->left) {
						min = min->left;
					}
					swap(min->key, root->key);
					return m_eraseR(root->right, key);
				}
				delete tmp;
				return true;
			}
		}

		// 属性
		Node* m_root = nullptr;
	};
}

namespace keyval {
	template<class K, class V>
	struct BSTNode {
		K key;
		V val;
		BSTNode* left;
		BSTNode* right;
		BSTNode(const K& x, const V& value)
			: key(x)
			, val(value)
			, left(nullptr)
			, right(nullptr)
		{}
	};

	template<class K, class V>
	class Binary_Search_Tree {
	public:
		typedef BSTNode<K, V> Node;
		// 默认构造
		Binary_Search_Tree() = default;		// 强制编译器生成默认构造函数C++11

		// 析构
		~Binary_Search_Tree() {
			Destroy(m_root);
		}

		// insert循环版本
		bool insert(const K& x, const V& value) {
			if (m_root == nullptr) {
				m_root = new Node(x, value);
				return true;
			}
			Node* cur = m_root, * parent = cur;
			while (cur) {
				if (x < cur->key) {
					parent = cur;
					cur = cur->left;
				}
				else if (x > cur->key) {
					parent = cur;
					cur = cur->right;
				}
				else {
					return false;
				}
			}
			cur = new Node(x, value);
			if (x < parent->key) parent->left = cur;
			if (x > parent->key) parent->right = cur;
			return true;
		}

		// find循环版本
		Node* find(const K& x) {
			if (m_root == nullptr) return nullptr;
			Node* cur = m_root;
			while (cur) {
				if (x < cur->key) cur = cur->left;
				else if (x > cur->key) cur = cur->right;
				else if (x == cur->key) return cur;
			}
			return nullptr;
		}

		void Inorder() {
			m_Inorder(m_root);
		}

	private:
		// 后序销毁
		void Destroy(Node*& root) {
			if (root == nullptr) return;
			Destroy(root->left);
			Destroy(root->right);
			delete root;
			root = nullptr;
		}

		// 中序遍历
		void m_Inorder(Node* root) {
			if (root == nullptr) return;
			m_Inorder(root->left);
			cout << root->key << " = " << root->val << endl;
			m_Inorder(root->right);
		}

		// 属性
		Node* m_root = nullptr;
	};
}


////////////////////////////////////////////////////OJ题目


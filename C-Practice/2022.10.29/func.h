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
		// Ĭ�Ϲ���
		Binary_Search_Tree() = default;		// ǿ�Ʊ���������Ĭ�Ϲ��캯��C++11
		// ��������
		Binary_Search_Tree(const Binary_Search_Tree<K>& b) {
			m_root = m_copy(b.m_root);
		}

		// ����
		~Binary_Search_Tree() {
			Destroy(m_root);
		}

		// ��ֵ����
		Binary_Search_Tree<K>& operator=(Binary_Search_Tree<K> t) {
			swap(m_root, t.m_root);
			return *this;
		}

		// insertѭ���汾
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

		// insert�ݹ�汾
		bool insertR(const K& x) {
			return m_insertR(m_root, x);
		}

		// findѭ���汾
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

		// find�ݹ�汾
		bool findR(const K& x) {
			return m_findR(m_root, x);
		}

		// eraseѭ���汾
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
			// case1: ������Ϊ��
			if (cur->left == nullptr) {					// ������Ϊ��
				if (cur == m_root) {					// �����ɾ���Ϊ����㣬���������λ�����ǿ��ӽ��
					m_root = cur->right;
				}
				else {									// �жϴ�ɾ���λ�ڸ��ڵ������Ҳ�
					if (parent->left == cur) {			// ������Ϊ��ɾ��㣬�����������йܴ�ɾ���������
						parent->left = cur->right;
					}
					else {								// ����ʹ���������йܴ�ɾ���������
						parent->right = cur->right;
					}
				}
				delete cur;
				cur = nullptr;
			}
			else if (cur->right == nullptr) {			// ����Ϊ��ͬ��
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
			// case2:������������Ϊ�ա����滻����ʹ��������С��㣩
			else {
				Node* min = cur->right, * minprt = cur;		// ��ɾ������Ϊ������ڶ����㣬���ܽ�minprt��nullptr
				while (min->left != nullptr) {	// ���������е���С���
					minprt = min;
					min = min->left;
				}
				if (minprt->left == min) minprt->left = min->right;		// �жϴ�ɾ�����minprt�����Ҳ࣬������������
				else minprt->right = min->right;	// ������С��������������������ø����̳�
				swap(min->key, cur->key);			// ��С������ɾ��㽻�������ͷ�
				delete min;
				min = nullptr;
			}
			return true;
		}

		// erase�ݹ�汾
		bool eraseR(const K& x) {
			return m_eraseR(m_root, x);
		}

		void Inorder() {
			m_Inorder(m_root);
		}

		void empty() {
			if (m_root == nullptr) cout << "����" << endl;
			else cout << "�ǿ�" << endl;
		}

	private:
		// ����
		// ǰ�򿽱�
		Node* m_copy(Node* root) {
			if (root == nullptr) return nullptr;
			Node* copyroot = new Node(root->key);
			copyroot->left = m_copy(root->left);
			copyroot->right = m_copy(root->right);
			return copyroot;
		}
		// ��������
		void Destroy(Node*& root) {
			if (root == nullptr) return;
			Destroy(root->left);
			Destroy(root->right);
			delete root;
			root = nullptr;
		}

		// �������
		void m_Inorder(Node* root) {
			if (root == nullptr) return;
			m_Inorder(root->left);
			cout << root->key << " ";
			m_Inorder(root->right);
		}

		// find�ݹ�
		bool m_findR(Node* root, const K& x) {
			if (root == nullptr) return false;
			if (x < root->key) return m_findR(root->left, x);
			else if (x > root->key) return m_findR(root->right, x);
			else return true;
		}

		// insert�ݹ�
		bool m_insertR(Node*& root, const K& key) {
			if (root == nullptr) {
				root = new Node(key);
				return true;
			}
			if (key > root->key) return m_insertR(root->right, key);
			else if (key < root->key) return m_insertR(root->left, key);
			else return false;
		}

		// erase�ݹ�
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

		// ����
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
		// Ĭ�Ϲ���
		Binary_Search_Tree() = default;		// ǿ�Ʊ���������Ĭ�Ϲ��캯��C++11

		// ����
		~Binary_Search_Tree() {
			Destroy(m_root);
		}

		// insertѭ���汾
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

		// findѭ���汾
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
		// ��������
		void Destroy(Node*& root) {
			if (root == nullptr) return;
			Destroy(root->left);
			Destroy(root->right);
			delete root;
			root = nullptr;
		}

		// �������
		void m_Inorder(Node* root) {
			if (root == nullptr) return;
			m_Inorder(root->left);
			cout << root->key << " = " << root->val << endl;
			m_Inorder(root->right);
		}

		// ����
		Node* m_root = nullptr;
	};
}


////////////////////////////////////////////////////OJ��Ŀ


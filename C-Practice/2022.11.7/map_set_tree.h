#pragma once
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

enum Color {
	BLACK,
	RED
};

template<class T>			// 泛型模板参数
struct RBTreeNode {
	T m_data;
	Color m_col;
	RBTreeNode<T>* left;
	RBTreeNode<T>* right;
	RBTreeNode<T>* m_parent;
	RBTreeNode(const T& kv)
		:m_data(kv)
		,m_col(RED)
		,left(nullptr)
		,right(nullptr)
		,m_parent(nullptr)
	{}
};

template<class T, class Ref, class Ptr>
struct __RBTree_Iterator {
	typedef RBTreeNode<T> Node;
	typedef __RBTree_Iterator<T, Ref, Ptr> iterator;
	Node* m_node;
	__RBTree_Iterator(Node* node = nullptr)
		:m_node(node)
	{}
	Ref operator*() {
		return m_node->m_data;
	}
	Ptr operator->() {
		return &(m_node->m_data);
	}
	bool operator!=(const iterator& it) const {
		return m_node != it.m_node;
	}
	bool operator==(const iterator& it) const {
		return m_node == it.m_node;
	}
	iterator& operator++() {
		if (m_node->right) {
			Node* left = m_node->right;
			while (left->left != nullptr) left = left->left;
			m_node = left;
		}
		else {
			Node* cur = m_node, * parent = cur->m_parent;
			while (parent && parent->right == cur) {
				cur = parent;
				parent = parent->m_parent;
			}
			m_node = parent;
		}
		return *this;
	}
	iterator& operator--() {
		if (m_node->left) {
			Node* right = m_node->left;
			while (right->right) right = right->right;
			m_node = right;
		}
		else {
			Node* cur = m_node, * parent = cur->m_parent;
			while (parent && parent->left == cur) {
				cur = parent;
				parent = parent->m_parent;
			}
			m_node = parent;
		}
		return *this;
	}
};
 
template<class K, class T, class KeyInT>		// K参数用于函数find，作为key用于查找
class RBTree {									// KeyInT为仿函数，用于区分map和set的值T是pair还是key
public:
	typedef RBTreeNode<T> Node;
	typedef __RBTree_Iterator<T, T&, T*> iterator;
	typedef __RBTree_Iterator<T, const T&, const T*> const_iterator;
	iterator begin() {
		Node* left = m_root;
		while (left && left->left) {
			left = left->left;
		}
		return iterator(left);
	}

	const_iterator cbegin() {
		return begin();
	}

	iterator end() {
		return iterator(nullptr);
	}

	const_iterator cend() {
		return end();
	}

	pair<iterator, bool> insert(const T& data) {
		KeyInT type;
		if (m_root == nullptr) {
			m_root = new Node(data);
			m_root->m_col = BLACK;
			return make_pair(iterator(m_root), true);
		}
		Node* cur = m_root, * parent = nullptr;
		while (cur) {
			if (type(data) < type(cur->m_data)) {
				parent = cur;
				cur = cur->left;
			}
			else if (type(data) > type(cur->m_data)) {
				parent = cur;
				cur = cur->right;
			}
			else return make_pair(iterator(cur), false);
		}
		cur = new Node(data);
		cur->m_parent = parent;
		if (type(data) < type(parent->m_data)) parent->left = cur;
		else parent->right = cur;
		// 平衡控制，只有parent为RED才进入修正平衡性
		Node* newnode = cur;
		while (parent && parent->m_col == RED) {
			Node* grandparent = parent->m_parent;
			assert(grandparent && grandparent->m_col == BLACK);
			if (parent == grandparent->left) {
				Node* uncle = grandparent->right;
				// case1: uncle is red
				if (uncle && uncle->m_col == RED) {
					uncle->m_col = parent->m_col = BLACK;
					grandparent->m_col = RED;
					cur = grandparent;
					parent = cur->m_parent;
				}
				// case2&3
				else {
					// case2
					if (cur == parent->left) {			// 左子树的左侧插入
						rotateR(grandparent);
						parent->m_col = BLACK;
						grandparent->m_col = RED;
					}
					// case3
					else {								// 左子树右侧插入
						rotateLR(grandparent);
						cur->m_col = BLACK;
						grandparent->m_col = RED;
					}
					break;
				}
			}
			else {
				// case1: uncle is red
				Node* uncle = grandparent->left;
				if (uncle && uncle->m_col == RED) {
					uncle->m_col = parent->m_col = BLACK;
					grandparent->m_col = RED;
					cur = grandparent;
					parent = cur->m_parent;
				}
				else {
					// case2
					if (parent->right == cur) {			// 右子树右侧插入
						rotateL(grandparent);
						parent->m_col = BLACK;
						grandparent->m_col = RED;
					}
					// case3
					else {								// 右子树左侧插入
						rotateRL(grandparent);
						cur->m_col = BLACK;
						grandparent->m_col = RED;
					}
					break;
				}
			}
		}
		m_root->m_col = BLACK;		// 根必定为黑
		return make_pair(iterator(newnode), true);
	}

	void Inorder() {
		m_Inorder(m_root);
	}

	bool isBalanced() {
		if (m_root == nullptr) return true;
		if (m_root->m_col == RED) return false;
		int ref = 0;
		return m_isBalanced(m_root, 0, ref);
	}

private:
	bool m_isBalanced(Node* root, int blacknum, int& ref) {
		if (root == nullptr) {
			if (ref == 0) {
				ref = blacknum;
			}
			if (blacknum != ref) return false;
			return true;
		}
		if (root->m_col == BLACK) blacknum++;
		if (root->m_col == RED && root->m_parent->m_col == RED) return false;
		return m_isBalanced(root->left, blacknum, ref) && m_isBalanced(root->right, blacknum, ref);
	}
	void m_Inorder(Node* root) {
		if (root == nullptr) {
			return;
		}
		m_Inorder(root->left);
		cout << "first: " << root->m_kv.first << " second: " << root->m_kv.second << endl;
		m_Inorder(root->right);
	}

	void rotateL(Node* parent) {
		Node* subRight = parent->right, * subRLeft = subRight->left, * ppNode = parent->m_parent;
		parent->m_parent = subRight;
		subRight->left = parent;
		parent->right = subRLeft;
		if (subRLeft) {
			subRLeft->m_parent = parent;
		}
		subRight->m_parent = ppNode;
		if (ppNode) {
			if (ppNode->left == parent) ppNode->left = subRight;
			else ppNode->right = subRight;
		}
		else m_root = subRight;
	}

	void rotateR(Node* parent) {
		Node* subLeft = parent->left, * subLRight = subLeft->right, * ppNode = parent->m_parent;
		parent->m_parent = subLeft;
		subLeft->right = parent;
		parent->left = subLRight;
		if (subLRight) {
			subLRight->m_parent = parent;
		}
		subLeft->m_parent = ppNode;
		if (ppNode) {
			if (ppNode->left == parent) ppNode->left = subLeft;
			else ppNode->right = subLeft;
		}
		else m_root = subLeft;
	}

	void rotateLR(Node* parent) {
		rotateL(parent->left);
		rotateR(parent);
	}

	void rotateRL(Node* parent) {
		rotateR(parent->right);
		rotateL(parent);
	}

private:
	Node* m_root = nullptr;
};
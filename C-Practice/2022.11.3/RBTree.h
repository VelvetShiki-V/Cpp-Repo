#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

enum Color {
	BLACK,
	RED
};

template<class K, class V>
struct RBTreeNode {
	pair<K, V> m_kv;
	Color m_col;
	RBTreeNode<K, V>* left;
	RBTreeNode<K, V>* right;
	RBTreeNode<K, V>* m_parent;
	RBTreeNode(const pair<K, V>& kv) 
		:m_kv(kv)
		,m_col(RED)
		,left(nullptr)
		,right(nullptr)
		,m_parent(nullptr)
	{}
};

template<class K, class V>
class RBTree {
public:
	typedef RBTreeNode<K, V> Node;
	bool insert(const pair<K, V>& kv) {
		if (m_root == nullptr) {
			m_root = new Node(kv);
			m_root->m_col = BLACK;
		}
		Node* cur = m_root, * parent = nullptr;
		while (cur) {
			if (kv.first < cur->m_kv.first) {
				parent = cur;
				cur = cur->left;
			}
			else if (kv.first > cur->m_kv.first) {
				parent = cur;
				cur = cur->right;
			}
			else return false;
		}
		cur = new Node(kv);
		cur->m_parent = parent;
		if (kv.first < parent->m_kv.first) parent->left = cur;
		else parent->right = cur;
		// 平衡控制，只有parent为RED才进入修正平衡性
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
		return true;
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
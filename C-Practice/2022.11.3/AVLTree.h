#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>
#include<vector>
#include<time.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode {
	int bf;
	pair<K, V> m_kv;
	AVLTreeNode<K, V>* left;
	AVLTreeNode<K, V>* right;
	AVLTreeNode<K, V>* m_parent;
	AVLTreeNode(const pair<K, V>& p) 
		:bf(0)
		,m_kv(p)
		,right(nullptr)
		,left(nullptr)
		,m_parent(nullptr)
	{}
};

template<class K, class V>
class AVLTree {
public:
	typedef AVLTreeNode<K, V> Node;
	bool insert(const pair<K, V>& kv) {
		// 插入结点
		if (root == nullptr) {
			root = new Node(kv);
			return true;
		}
		Node* cur = root, * parent = nullptr;
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
		if (kv.first < parent->m_kv.first) parent->left = cur;
		else parent->right = cur;
		cur->m_parent = parent;
		// 控制平衡因子
		while (parent) {
			if (cur == parent->left) parent->bf--;		// 判断新插入结点在子根左或右子树
			else parent->bf++;
			if (parent->bf == 0) break;
			else if (abs(parent->bf) == 1) {
				cur = parent;
				parent = parent->m_parent;
			}
			else if (abs(parent->bf) == 2) {
				if (parent->bf == 2 && cur->bf == 1) rotateL(parent);			// 右右，左单旋
				else if (parent->bf == -2 && cur->bf == -1) rotateR(parent);	// 左左，右单旋
				else if (parent->bf == -2 && cur->bf == 1) rotateLR(parent);	// 内侧插入，先左旋再右旋
				else if (parent->bf == 2 && cur->bf == -1) rotateRL(parent);	// 右左双旋
				break;
			}
			else {
				assert(false);
			}
		}
		return true;
	}

	void Inorder() {
		m_Inorder(root);
	}

	bool isBalanced() {
		return m_isBalanced(root);
	}

private:
	bool m_isBalanced(Node* root) {
		if (root == nullptr) return true;
		int LHeight = AVLTree_Height(root->left);
		int RHeight = AVLTree_Height(root->right);
		int diff = RHeight - LHeight;
		return abs(diff) < 2 && m_isBalanced(root->left) && m_isBalanced(root->right);
	}
	int AVLTree_Height(Node* root) {
		if (root == nullptr) {
			return 0;
		}
		return max(AVLTree_Height(root->left), AVLTree_Height(root->right)) + 1;
	}
	void m_Inorder(Node* root) {
		if (root == nullptr) {
			return;
		}
		m_Inorder(root->left);
		cout << "key: " << root->m_kv.first << " val: " << root->m_kv.second << endl;
		m_Inorder(root->right);
	}
	void rotateL(Node* parent) {
		Node* subRight = parent->right, * subRLeft = subRight->left, * ppNode = parent->m_parent;
		subRight->left = parent;
		parent->m_parent = subRight;
		parent->right = subRLeft;		// 不管右子树的左子树是否存在，都需要更新左旋后的parent右子树指向新的地址
		if (subRLeft) {
			subRLeft->m_parent = parent;
		}
		subRight->m_parent = ppNode;	// 不管祖先结点是否存在，先让新成为父节点的右子结点指向原父结点的祖先结点
		if (ppNode) {
			if (ppNode->left == parent) ppNode->left = subRight;
			else ppNode->right = subRight;
		}
		else {
			root = subRight;
		}
		subRight->bf = parent->bf = 0;
	}
	void rotateR(Node* parent) {
		Node* subLeft = parent->left, * subLRight = subLeft->right, * ppNode = parent->m_parent;
		subLeft->right = parent;
		parent->m_parent = subLeft;
		parent->left = subLRight;
		if (subLRight) {
			subLRight->m_parent = parent;
		}
		subLeft->m_parent = ppNode;
		if (ppNode) {
			if (ppNode->left == parent) ppNode->left = subLeft;
			else ppNode->right = subLeft;
		}
		else {
			root = subLeft;
		}
		subLeft->bf = parent->bf = 0;
	}
	void rotateLR(Node* parent) {
		Node* subLeft = parent->left, * subLRight = subLeft->right;
		int bf = subLRight->bf;
		rotateL(subLeft);
		rotateR(parent);
		subLRight->bf = 0;			// 双旋后内侧不平衡树根结点一定平衡了，bf置0
		if (bf == -1) {
			subLeft->bf = 0;
			parent->bf = 1;			//	只需要更新双旋后的不平衡原根结点bf，这里出问题？
		}
		else if (bf == 1) {
			subLeft->bf = -1;		// 只需要更新双旋后的不平衡左子树根bf
			parent->bf = 0;
		}
		else if (bf == 0) {
			subLeft->bf = parent->bf = 0;		// 双旋后都变为0了
		}
		else assert(false);
	}
	void rotateRL(Node* parent) {
		Node* subRight = parent->right, * subRLeft = subRight->left;
		int bf = subRLeft->bf;
		rotateR(subRight);
		rotateL(parent);
		subRLeft->bf = 0;
		if (bf == -1) {
			subRight->bf = 1;
			parent->bf = 0;
		}
		else if (bf == 1) {
			subRight->bf = 0;
			parent->bf = -1;
		}
		else if (bf == 0) {
			parent->bf = subRight->bf = 0;
		}
		else {
			assert(false);
		}
	}
private:
	Node* root = nullptr;
};
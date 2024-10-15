#pragma once
#include<iostream>
#include<assert.h>
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
		// ������
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
		// ����ƽ������
		while (parent) {
			if (cur == parent->left) parent->bf--;		// �ж��²��������Ӹ����������
			else parent->bf++;
			if (parent->bf == 0) break;
			else if (abs(parent->bf) == 1) {
				cur = parent;
				parent = parent->m_parent;
			}
			else if (abs(parent->bf) == 2) {
				if (parent->bf == 2 && cur->bf == 1) rotateL(parent);			// ���ң�����
				else if (parent->bf == -2 && cur->bf == -1) rotateR(parent);	// �����ҵ���
				else if (parent->bf == -2 && cur->bf == 1) rotateLR(parent);	// �ڲ���룬������������
				break;
			}
			else {
				assert(false);
			}
		}
		return true;
	}
private:
	void rotateL(Node* parent) {
		Node* subRight = parent->right, * subRLeft = subRight->left, * ppNode = parent->m_parent;
		subRight->left = parent;
		parent->m_parent = subRight;
		if (subRLeft) {
			subRLeft->m_parent = parent;
			parent->right = subRLeft;
		}
		if (ppNode) {
			subRight->m_parent = ppNode;
			if (ppNode->left == parent) ppNode->left = subRight;
			else ppNode->right = subRight;
		}
		subRight->bf = parent->bf = 0;
	}
	void rotateR(Node* parent) {
		Node* subLeft = parent->left, * subLRight = subLeft->right, * ppNode = parent->m_parent;
		subLeft->right = parent;
		parent->m_parent = subLeft;
		if (subLRight) {
			subLRight->m_parent = parent;
			parent->left = subLRight;
		}
		if (ppNode) {
			subLeft->m_parent = ppNode;
			if (ppNode->left == parent) ppNode->left = subLeft;
			else ppNode->right = subLeft;
		}
		subLeft->bf = parent->bf = 0;
	}
	void rotateLR(Node* parent) {
		Node* subLeft = parent->left, * subLRight = subLeft->right;
		int bf = subLRight->bf;
		rorateL(parent->left);
		rotateR(parent);
		subLRight->bf = 0;		// ˫�����ڲ಻ƽ���������һ��ƽ���ˣ�bf��0
		if (bf == -1) {
			parent = 1;			//	ֻ��Ҫ����˫����Ĳ�ƽ��ԭ�����bf
		}
		else if (bf == 1) {
			subLeft->bf = -1;	// ֻ��Ҫ����˫����Ĳ�ƽ����������bf
		}
		else if (bf == 0) {
			;					// ˫���󶼱�Ϊ0��
		}
		else assert(false);
	}
private:
	Node* root = nullptr;
};
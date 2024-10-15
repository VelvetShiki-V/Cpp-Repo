#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int BTEtype;
typedef struct BinaryTreeNode
{
	BTEtype data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

//�����������ӿ�
BTNode* BuyTreeNode(BTEtype x);						//���������
BTNode* TreeCreate();								//����һ����ʽ������
void Preorder(BTNode* root);						//ǰ�����
void Inorder(BTNode* root);							//�������
void Postorder(BTNode* root);						//��������
void TreeSize(BTNode* root);						//�������н�����
int TreeSize2(BTNode* root);						
int LeafSize(BTNode* root);							//��������Ҷ�ӽ�����
int TreeDepth(BTNode* root);						//�����������
int KNodeCount(BTNode* root, int k);				//�������е�K��Ľ�����
BTNode* TreeNodeFind(BTNode* root, BTEtype x);		//�������е�ĳ���ڵ㲢���ؽ���ַ
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

//二叉树函数接口
BTNode* BuyTreeNode(BTEtype x);						//开辟树结点
BTNode* TreeCreate();								//创建一颗链式二叉树
void Preorder(BTNode* root);						//前序遍历
void Inorder(BTNode* root);							//中序遍历
void Postorder(BTNode* root);						//后续遍历
void TreeSize(BTNode* root);						//计算树中结点个数
int TreeSize2(BTNode* root);						
int LeafSize(BTNode* root);							//计算树种叶子结点个数
int TreeDepth(BTNode* root);						//计算树的深度
int KNodeCount(BTNode* root, int k);				//计算树中第K层的结点个数
BTNode* TreeNodeFind(BTNode* root, BTEtype x);		//查找树中的某个节点并返回结点地址
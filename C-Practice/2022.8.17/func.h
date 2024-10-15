#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct TreeNode
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
}root;

struct TreeNode* BuyTreeNode(int val)
{
	struct TreeNode* tmp = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    assert(tmp);
	tmp->left = tmp->right = NULL;
	tmp->val = val;
	return tmp;
}

void Preorder(struct TreeNode* root, int* ret, int* returnSize)
{
    if (root == NULL)
    {
        return;
    }
    if (root->val == NULL)
    {
        return;
    }
    static int i = 0;
    ret[i++] = root->val;
    *returnSize = i;
    Preorder(root->left, ret, returnSize);
    Preorder(root->right, ret, returnSize);
}
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    if (root == NULL)
    {
        *returnSize = 0;
        return NULL;
    }
    int* ret = (int*)malloc(sizeof(int) * 100);
    Preorder(root, ret, returnSize);
    return ret;
}
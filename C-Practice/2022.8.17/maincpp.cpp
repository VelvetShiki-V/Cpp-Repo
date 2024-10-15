#include"func.h"


void test1()
{
	struct TreeNode* root = BuyTreeNode(1);
	//struct TreeNode* r1 = BuyTreeNode(NULL);
	//struct TreeNode* r2 = BuyTreeNode(2);
	//struct TreeNode* r3 = BuyTreeNode(3);
	//root->left = r1;
	//root->right = r2;
	//r2->left = r3;
	int* ret = NULL;
	int returnSize = 0;
	int* Size = &returnSize;
	ret = preorderTraversal(root, Size);
}

void test2()
{
	//二叉树前序遍历，leetcode刷题144
	int i = 0;
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
		assert(ret);
		Preorder(root, ret, returnSize);
		i = 0;
		return ret;
	}

	//中序遍历
	//int i = 0;
	//void Preorder(struct TreeNode* root, int* ret, int* returnSize)
	//{
	//	if (root == NULL)
	//	{
	//		return;
	//	}
	//	Preorder(root->left, ret, returnSize);
	//	ret[i++] = root->val;
	//	*returnSize = i;
	//	Preorder(root->right, ret, returnSize);
	//}
	//int* inorderTraversal(struct TreeNode* root, int* returnSize) {
	//	if (root == NULL)
	//	{
	//		*returnSize = 0;
	//		return NULL;
	//	}
	//	int* ret = (int*)malloc(sizeof(int) * 100);
	//	assert(ret);
	//	Preorder(root, ret, returnSize);
	//	i = 0;
	//	return ret;
	//}

	//后序遍历
	//int i = 0;
	//void Preorder(struct TreeNode* root, int* ret, int* returnSize)
	//{
	//	if (root == NULL)
	//	{
	//		return;
	//	}
	//	if (root->val == NULL)
	//	{
	//		return;
	//	}
	//	Preorder(root->left, ret, returnSize);
	//	Preorder(root->right, ret, returnSize);
	//	ret[i++] = root->val;
	//	*returnSize = i;
	//}
	//int* postorderTraversal(struct TreeNode* root, int* returnSize) {
	//	if (root == NULL)
	//	{
	//		*returnSize = 0;
	//		return NULL;
	//	}
	//	int* ret = (int*)malloc(sizeof(int) * 100);
	//	assert(ret);
	//	Preorder(root, ret, returnSize);
	//	i = 0;
	//	return ret;
	//}
}
int main()
{
	//test1();
	test2();
	return 0;
}
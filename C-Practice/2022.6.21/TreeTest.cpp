#include"Func.h"

BTNode* BuyTreeNode(BTEtype x)
{
	BTNode* NewNode = (BTNode*)malloc(sizeof(BTNode));
	assert(NewNode);
	NewNode->data = x;
	NewNode->left = NULL;
	NewNode->right = NULL;
	return NewNode;
}

BTNode* TreeCreate()
{
	BTNode* n1 = BuyTreeNode(1);
	BTNode* n2 = BuyTreeNode(2);
	BTNode* n3 = BuyTreeNode(3);
	BTNode* n4 = BuyTreeNode(4);
	BTNode* n5 = BuyTreeNode(5);
	BTNode* n6 = BuyTreeNode(6);

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n3->left = n5;
	n3->right = n6;

	return n1;
}

void Preorder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%d ", root->data);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	Inorder(root->left);
	printf("%d ", root->data);
	Inorder(root->right);
}

void Postorder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	Postorder(root->left);
	Postorder(root->right);
	printf("%d ", root->data);
}

void TreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	extern int count;
	count++;
	TreeSize(root->left);
	TreeSize(root->right);
}

int TreeSize2(BTNode* root)
{
	return root == NULL ? 0 : TreeSize2(root->left) + TreeSize2(root->right) + 1;
}

int LeafSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	return LeafSize(root->left) + LeafSize(root->right);
}

int TreeDepth(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	int LDepth = 0, RDepth = 0, MAX = 0;
	LDepth = TreeDepth(root->left);
	RDepth = TreeDepth(root->right);
	MAX = LDepth > RDepth ? LDepth : RDepth;
	return MAX + 1;
}

int KNodeCount(BTNode* root, int k)
{
	assert(k >= 1/* && k <= TreeDepth(root)*/);
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return KNodeCount(root->left, k - 1) + KNodeCount(root->right, k - 1);
}

BTNode* TreeNodeFind(BTNode* root, BTEtype x)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->data == x)
	{
		return root;
	}
	BTNode* Lresult = TreeNodeFind(root->left, x);
	if (Lresult)
	{
		return Lresult;
	}
	BTNode* Rresult = TreeNodeFind(root->right, x);
	if (Rresult)
	{
		return Rresult;
	}
	return NULL;
}
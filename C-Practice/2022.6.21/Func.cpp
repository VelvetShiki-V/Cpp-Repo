#include"Func.h"
int count;
void Traversal(BTNode* root)
{
	printf("前序遍历：");
	Preorder(root);
	printf("\n");
	printf("中序遍历：");
	Inorder(root);
	printf("\n");
	printf("后序遍历：");
	Postorder(root);
	printf("\n");
}

void Size(BTNode* root)
{
	//一次调用
	count = 0;
	TreeSize(root);
	printf("Size is : %d\n", count);
	//二次调用
	count = 0;
	TreeSize(root);
	printf("Size is : %d\n", count);
	//不使用全局变量计算结点数
	int size = TreeSize2(root);
	printf("Size is : %d\n", size);
	//计算叶子结点数
	int lfsize = LeafSize(root);
	printf("Leaf size is : %d\n", lfsize);
}

void NodeCount(BTNode* root)
{
	//树的深度
	int depth = TreeDepth(root);
	printf("Depth of Tree is : %d\n", depth);
	//第K层的结点数量
	int num = KNodeCount(root, 1);
	printf("第一层结点数量为：%d\n", num);
	num = KNodeCount(root, 2);
	printf("第二层结点数量为：%d\n", num);
	num = KNodeCount(root, 3);
	printf("第三层结点数量为：%d\n", num);
	num = KNodeCount(root, 4);
	printf("第四层结点数量为：%d\n", num);
}

void Find(BTNode* root)
{
	BTNode* result = TreeNodeFind(root, 10);
	if (result)
	{
		printf("查找结果为：%d\n", result->data);
	}
	else
	{
		printf("找不到\n");
	}
}
int main()
{
	BTNode* root = TreeCreate();
	Traversal(root);
	Size(root);
	NodeCount(root);
	Find(root);
	return 0;
}
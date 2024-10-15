#include"Func.h"
int count;
void Traversal(BTNode* root)
{
	printf("ǰ�������");
	Preorder(root);
	printf("\n");
	printf("���������");
	Inorder(root);
	printf("\n");
	printf("���������");
	Postorder(root);
	printf("\n");
}

void Size(BTNode* root)
{
	//һ�ε���
	count = 0;
	TreeSize(root);
	printf("Size is : %d\n", count);
	//���ε���
	count = 0;
	TreeSize(root);
	printf("Size is : %d\n", count);
	//��ʹ��ȫ�ֱ�����������
	int size = TreeSize2(root);
	printf("Size is : %d\n", size);
	//����Ҷ�ӽ����
	int lfsize = LeafSize(root);
	printf("Leaf size is : %d\n", lfsize);
}

void NodeCount(BTNode* root)
{
	//�������
	int depth = TreeDepth(root);
	printf("Depth of Tree is : %d\n", depth);
	//��K��Ľ������
	int num = KNodeCount(root, 1);
	printf("��һ��������Ϊ��%d\n", num);
	num = KNodeCount(root, 2);
	printf("�ڶ���������Ϊ��%d\n", num);
	num = KNodeCount(root, 3);
	printf("������������Ϊ��%d\n", num);
	num = KNodeCount(root, 4);
	printf("���Ĳ�������Ϊ��%d\n", num);
}

void Find(BTNode* root)
{
	BTNode* result = TreeNodeFind(root, 10);
	if (result)
	{
		printf("���ҽ��Ϊ��%d\n", result->data);
	}
	else
	{
		printf("�Ҳ���\n");
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
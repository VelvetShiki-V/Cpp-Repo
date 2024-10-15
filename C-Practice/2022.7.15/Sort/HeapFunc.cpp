#include"Func.h"

HP* HPInit()
{
	HP* NewArray = (HP*)malloc(sizeof(HP));
	assert(NewArray);
	NewArray->arr = NULL;
	NewArray->capacity = NewArray->size = 0;
	return NewArray;
}

bool Bigger(HPEtype a, HPEtype b)		//大堆规则
{
	return a > b;
}

bool Smaller(HPEtype a, HPEtype b)		//小堆规则
{
	return a < b;
}

void Swap(HPEtype* a, HPEtype* b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void HPPush(HP* root, HPEtype x, COM rule)
{
	assert(root);
	if (root->capacity == root->size)
	{
		int expand = root->capacity == 0 ? 4 : root->capacity * 2;
		HPEtype* NewSpace = (HPEtype*)realloc(root->arr, sizeof(HPEtype) * expand);
		assert(NewSpace);
		root->arr = NewSpace;
		root->capacity = expand;
	}
	root->arr[root->size] = x;
	root->size++;
	AdjustUpward(root->arr, root->size - 1, rule);
}

void AdjustUpward(HPEtype* arr, int child, COM rule)
{
	assert(arr);
	int parent = (child - 1) / 2;
	while (child)
	{
		if (rule(arr[child], arr[parent]))
		{
			Swap(&arr[child], &arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void HPPop(HP* root, COM rule)
{
	assert(root);
	if (!HPEmpty(root))
	{
		Swap(&root->arr[0], &root->arr[root->size - 1]);			//堆首尾元素交换
		root->size--;		//剔除堆尾元素
		AdjustDownward(root->arr,root->size, 0, rule);
	}
}

void AdjustDownward(HPEtype* arr, int size, int parent, COM rule)
{
	assert(arr);
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && rule(arr[child + 1], arr[child]))
		{
			child = child + 1;
		}
		if (rule(arr[child], arr[parent]))
		{
			Swap(&arr[parent], &arr[child]);
			parent = child;
			child = child * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

bool HPEmpty(HP* root)
{
	assert(root);
	return root->size == 0;
}

HPEtype HPTop(HP* root)
{
	assert(root);
	if (HPEmpty(root))
	{
		return -1;
	}
	return root->arr[0];
}

int HPSize(HP* root)
{
	assert(root);
	return root->size;
}

HP* HPDestroy(HP* root)
{
	assert(root);
	free(root->arr);
	free(root);
	root = NULL;
	return root;
}

void HPCreateDown(int* arr, int size, COM rule)
{
	assert(arr);
	if (size != 0)
	{
		int root = (size - 1 - 1) / 2;
		while (root >= 0)
		{
			AdjustDownward(arr, size, root, rule);
			root--;
		}
	}
}

void HPCreateUP(int* arr, int size, COM rule)
{
	assert(arr);
	if (size != 0)
	{
		int child = 0;
		while (child < size)
		{
			AdjustUpward(arr, child, rule);
			child++;
		}
	}
}

void HPSort(int* arr, int size, COM rule)
{
	int end = size - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		AdjustDownward(arr, end, 0, rule);
		end--;
	}
}

void HPPrint(HP* root, COM rule)
{
	assert(root);
	if (HPEmpty(root))
	{
		printf("堆为空，无法遍历\n");
		return;
	}
	while (!HPEmpty(root))
	{
		printf("%d ", HPTop(root));
		HPPop(root, rule);
	}
}

void BubbleSort(int* arr, int size, COM rule)
{
	assert(arr);
	int round = size;
	while (round - 1)
	{
		int i = 0;
		while (i < size - 1)
		{
			if (rule(arr[i], arr[i + 1]))
			{
				Swap(&arr[i], &arr[i + 1]);
			}
			i++;
		}
		round--;
	}
}

HPEtype* TopK(HPEtype* arr, int k, int size, COM rule)
{
	assert(arr);
	HPEtype* TopHeap = (HPEtype*)malloc(k * sizeof(HPEtype));
	assert(TopHeap);
	int i = 0;
	for (i = 0; i < k; i++)
	{
		TopHeap[i] = arr[i];
	}
	for (i = (k - 2) / 2; i >= 0; i--)
	{
		AdjustDownward(TopHeap, k, i, rule);
	}
	for (i = k; i < size; i++)
	{
		if (rule(TopHeap[0], arr[i]))
		{
			TopHeap[0] = arr[i];
			AdjustDownward(TopHeap, k, 0, rule);
		}
	}
	return TopHeap;
}

void PrintTopK(HPEtype* Toparr, int k)
{
	assert(Toparr);
	int i = 0;
	for (i; i < k; i++)
	{
		printf("%d ", Toparr[i]);
	}
	printf("\n");
}
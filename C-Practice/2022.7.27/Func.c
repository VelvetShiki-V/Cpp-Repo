#include"Func.h"

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//ֱ�Ӳ�������
void InsertSort(int* arr, int sz)
{
	int* cur = arr, * prev = arr;			//�����²���ֵ��ָ���ǰһ����ָ��
	while (++cur < &arr[sz])				//cur�����鷶Χ�ڵ�����ѭ��
	{
		int value = *cur;					//��ʱ�洢�²����ֵ
		while (prev >= arr)					//����ѭ������ǰԽ��ʱֹͣ
		{
			if (value < *prev)				//����²����ֵ��ǰһ��С������ɱ䣩
			{
				*(prev-- + 1) = *prev;		//prev�����ú�Ų���ǣ����Լ�
			}
			else
			{
				break;						//�����²����ֵ��prev��ʱֹͣ����ѭ��
			}
		}
		*(prev + 1) = value;				//����ֵ���뵽prev�ĺ�һ�������ϣ������ûص�curλ��
		prev = cur;
	}
}

void ShellSort(int* arr, int sz)
{
	int gap = sz;
	while (gap > 1)
	{
		int* cur = arr, * prev = arr;
		gap = gap / 3 + 1;
		while (cur < &arr[sz - gap])
		{
			int value = *(cur + gap);
			while (prev >= arr)
			{
				if (value < *prev)				//����ɱ�
				{
					*(prev + gap) = *prev;
					prev -= gap;
				}
				else
				{
					break;
				}
			}
			*(prev + gap) = value;
			cur++;
			prev = cur;
		}
	}
}

void SelectSort(int* arr, int sz)
{
	for (int i = 0; i <= (sz - 1) / 2; i++)
	{
		int max = i, min = i;
		for (int j = i; j < sz - i; j++)
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
			if (arr[max] < arr[j])
			{
				max = j;
			}
		}
		Swap(&arr[max], &arr[sz - 1 - i]);
		if (max != i || min != sz - 1 - i)
		{
			Swap(&arr[min], &arr[i]);
		}
	}
}

void BubbleSort(int* arr, int sz)
{
	for (int i = 0; i < sz - 1; i++)
	{
		bool flag = true;
		for (int j = 0; j < sz - 1 - i; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
				flag = false;
			}
		}
		if (flag)
		{
			break;
		}
	}
}

void QuickSort(int* arr, int Head, int Tail)
{
	if (Head >= Tail)
	{
		return;
	}
	//int key = HoareSort(arr, Head, Tail);
	//int key = PitSort(arr, Head, Tail);
	int key = PointerSort(arr, Head, Tail);
	if (Tail - Head > 15)
	{
		QuickSort(arr, Head, key - 1);
		QuickSort(arr, key + 1, Tail);
	}
	else
	{
		InsertSort(arr + Head, Tail - Head + 1);
	}
}

int HoareSort(int* arr, int left, int right)
{
	int key = left, keyval = arr[key];
	while (left < right)
	{
		while(left < right && arr[right] >= keyval)
			right--;
		while(left < right && arr[left] <= keyval)
			left++;
		Swap(&arr[left], &arr[right]);
	}
	Swap(&arr[key], &arr[left]);
	key = left;
	return key;
}

int PitSort(int* arr, int left, int right)
{
	int pit = left, keyval = arr[pit];
	while (left < right)
	{
		while (left < right && arr[right] < keyval)right--;
		arr[pit] = arr[right];
		pit = right;
		while (left < right && arr[left] > keyval)left++;
		arr[pit] = arr[left];
		pit = left;
	}
	arr[pit] = keyval;
	return pit;
}

int PointerSort(int* arr, int left, int right)
{
	int mid = GetMid(arr, left, right);
	Swap(&arr[mid], &arr[left]);
	int key = left, keyval = arr[key], cur = left + 1, prev = left;
	while (cur <= right)
	{
		while (arr[cur] < keyval && ++prev != cur)
		{
			Swap(&arr[cur], &arr[prev]);
		}
		cur++;
	}
	Swap(&arr[prev], &arr[key]);
	key = prev;
	return key;
}

int GetMid(int* arr, int left, int right)
{
	int mid = (left + right) / 2;
	int array[] = { arr[left], arr[mid], arr[right] };
	InsertSort(array, 3);
	if (array[1] == arr[left])
		return left;
	else if (array[1] == arr[mid])
		return mid;
	else
		return right;
}

void QuickSortStack(int* arr, int Head, int Tail)
{
	ST* Bot = STInit();
	STPush(Bot, Tail);
	STPush(Bot, Head);
	while (!STEmpty(Bot))
	{
		int left = STTop(Bot);
		STPop(Bot);
		int right = STTop(Bot);
		STPop(Bot);
		if (left < right)
		{
			int key = PointerSort(arr, left, right);
			STPush(Bot, right);
			STPush(Bot, key + 1);
			STPush(Bot, key - 1);
			STPush(Bot, left);
		}
		else
		{
			continue;
		}
	}
	STDestroy(&Bot);
}

void MergeSort(int* arr, int sz)
{
	int* tmp = (int*)malloc(sz * sizeof(int));
	assert(tmp);
	Subsort(arr, tmp, 0, sz - 1);
	free(tmp);
}
void Subsort(int* arr, int* tmp, int Head, int Tail)
{
	if (Head >= Tail)
	{
		return;
	}
	int mid = (Head + Tail) / 2;
	int left = Head, leftend = mid, right = mid + 1, rightend = Tail, i = Head;
	Subsort(arr, tmp, Head, mid);
	Subsort(arr, tmp, mid + 1, Tail);
	while (left <= leftend && right <= rightend)
	{
		if (arr[left] <= arr[right])
			tmp[i++] = arr[left++];
		else
			tmp[i++] = arr[right++];
	}
	while(left <= leftend)
		tmp[i++] = arr[left++];
	while(right <= rightend)
		tmp[i++] = arr[right++];
	memcpy(arr + Head, tmp + Head, (Tail - Head + 1)*sizeof(int));

	//static int k = 1;
	//printf("��%d�ι鲢��", k++);
	//for (int j = 0; j < 5; j++)
	//{
	//	printf("%d  ", arr[j]);
	//}
	//puts("\n");
}

void NonRecurMergeSort(int* arr, int sz)
{
	int gap = 1;
	int* tmp = (int*)malloc(sz * sizeof(int));
	assert(tmp);
	while (gap < sz)
	{
		int left = 0, i = 0;
		while (left < sz)
		{
			int leftend = left + gap - 1, right = left + gap, rightend = right + gap - 1;
			if (leftend >= sz || right >= sz)						//�߽紦�������ĩ�±�Խ���������±�Խ�磬ֱ�ӽ���ѭ�����鲢
			{
				break;
			}
			else if (rightend >= sz)								//�����ĩ�±�Խ�磬�򽫸��±����������ĩԪ���±꣬�Դ���δ���鲢��ĩԪ��
			{
				rightend = sz - 1;
			}
			int Head = left;										//��Ҫ���µ�ʵ���������
			int size = rightend - left + 1;							//��Ҫ���µ�ʵ���������
			while (left <= leftend && right <= rightend)			//�鲢��ʼ
			{
				if (arr[left] <= arr[right])
					tmp[i++] = arr[left++];
				else
					tmp[i++] = arr[right++];
			}
			while (left <= leftend)
				tmp[i++] = arr[left++];
			while (right <= rightend)
				tmp[i++] = arr[right++];							//�鲢����
			memcpy(arr + Head, tmp + Head, size * sizeof(int));		//�ڴ濽�������ÿһС�ι鲢������ѭ���ж����ܷ���һ��ѭ���⣬����Ϊ���ܻ´����Ч������
			left += gap;											//��Ծ�Ѿ��鲢�õķ�Χ����ʼ�������ݹ鲢

			//static int k = 1;
			//printf("gap=%d�ĵ�%d�ι鲢:", gap, k++);
			//for (int j = 0; j < 5; j++)
			//{
			//	printf("%d  ", arr[j]);
			//}
			//puts("\n");
		}
		gap *= 2;													//��ÿ�ι鲢�����ķ�Χ����ÿ���������
	}
	free(tmp);
}

void CountSort(int* arr, int sz)
{
	int max = arr[0], min = arr[0];
	for (int i = 0; i < sz; i++)
	{
		if (max < arr[i])
			max = arr[i];
		if (min > arr[i])
			min = arr[i];
	}
	int range = max - min + 1;
	int* tmp = (int*)malloc(range * sizeof(int));
	assert(tmp);
	memset(tmp, 0, range * sizeof(int));
	for (int i = 0; i < sz; i++)
	{
		tmp[arr[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (tmp[i]--)
		{
			arr[j++] = i + min;
		}
	}
	free(tmp);
}

////////////////////////////////////////////////////////////////////////////////////
bool Ascend(int a, int b)
{
	return a > b;
}
bool Descend(int a, int b)
{
	return a < b;
}
void HPCreate(int* arr, int sz, COM rule)
{
	int end = (sz - 2) / 2;
	while (end >= 0)
	{
		AdjustDownward(arr, sz, end, rule);
		end--;
	}
}
void AdjustDownward(int* arr, int sz, int parent, COM rule)
{
	int child = parent * 2 + 1;
	while (child < sz)
	{
		if (child + 1 < sz && rule(arr[child + 1], arr[child]))
		{
			child = child + 1;
		}
		if (rule(arr[child], arr[parent]))
		{
			Swap(&arr[child], &arr[parent]);
			parent = child;
			child = child * 2 + 1;
		}
		else
			break;
	}
}
void HPSort(int* arr, int sz, COM rule)
{
	int end = sz - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		AdjustDownward(arr, end, 0, rule);
		end--;
	}
}

//////////////////////////////////////////////////////////////////////////////////
ST* STInit()
{
	ST* NewStack = (ST*)malloc(sizeof(ST));
	assert(NewStack);
	NewStack->arr = NULL;
	NewStack->capacity = NewStack->top = 0;
	return NewStack;
}

void STPush(ST* Bot, STEtype x)
{
	if (Bot->capacity == Bot->top)
	{
		STEtype expand = Bot->capacity == 0 ? 4 : Bot->capacity * 2;
		Bot->arr = (STEtype*)realloc(Bot->arr, expand * sizeof(STEtype));
		assert(Bot->arr);
		Bot->capacity = expand;
	}
	Bot->arr[Bot->top] = x;
	Bot->top++;
}

void STPop(ST* Bot)
{
	if (!STEmpty(Bot))
	{
		Bot->top--;
	}
}

STEtype STTop(ST* Bot)
{
	if (!STEmpty(Bot))
	{
		return Bot->arr[Bot->top - 1];
	}
	return -99;
}

void STDestroy(ST** Bot)
{
	while (!STEmpty(*Bot))
	{
		(*Bot)->top--;
	}
	free((*Bot)->arr);
	free(*Bot);
	(*Bot) = NULL;
}

bool STEmpty(ST* Bot)
{
	return Bot->top == 0;
}
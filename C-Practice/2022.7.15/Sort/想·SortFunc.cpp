#include"Func.h"
int count;

bool Descend(int a, int b)
{
	return a > b;
}

bool Ascend(int a, int b)
{
	return a < b;
}

//void Swap(int* a, int* b)
//{
//	*a ^= *b;
//	*b ^= *a;
//	*a ^= *b;
//}

void InsertSort(int* arr, int sz, COM rule)
{
	assert(arr);
	int pos = 1, tmp = 0;
	while (pos < sz)
	{
		int prev = pos - 1;
		if (rule(arr[pos], arr[prev]))
		{
			tmp = pos;
			while (prev >= 0)
			{
				if (rule(arr[tmp], arr[prev]))
				{
					Swap(&arr[tmp], &arr[prev]);
					tmp--;
					prev--;
				}
				else
				{
					break;
				}
			}
		}
		pos++;
	}
}

void InsertSort2(int* arr, int sz, COM rule)
{
	assert(arr);
	int i = 0;
	while (i < sz - 1)
	{
		int end = i;
		int tmp = arr[end + 1];
		while (end >= 0)
		{
			if (rule(tmp, arr[end]))
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
			{
				break;
			}
		}
		arr[end + 1] = tmp;
		i++;
	}
}

void ShellSort(int* arr, int sz, COM rule)
{
	assert(arr);
	int gap = sz;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < sz - gap; i++)
		{
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0)
			{
				if (rule(tmp, arr[end]))
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			arr[end + gap] = tmp;
		}
		//printf("gap:%d--> ", gap);
		//for (int i = 0; i < sz; i++)
		//{
		//	printf("%d ", arr[i]);
		//}
		//printf("\n");
	}
}


void SelectSort(int* arr, int sz, COM rule)
{
	assert(arr);
	for (int i = 0; i < sz; i++)						//主循环控制首部向后移动
	{
		int FindSmall = i, FindLarge = i, end = i;
		while (end < sz)
		{
			if (arr[end] < arr[FindSmall])				//遍历一遍有效数组范围，选出最大和最小数的下标存储在变量中
			{
				FindSmall = end;
			}
			if (arr[end] > arr[FindLarge])
			{
				FindLarge = end;
			}
			end++;
		}
		if (rule == Ascend)								//根据排序规则， 将最大和最小数下标对应值与有效范围内的首尾元素替换
		{
			Swap(&arr[i], &arr[FindSmall]);
			if (FindLarge == i)							//为了防止下标与首部重叠情况，造成最小值与最大值再次交换
			{
				FindLarge = FindSmall;
			}
 			Swap(&arr[sz - 1], &arr[FindLarge]);
		}
		else
		{
			Swap(&arr[i], &arr[FindLarge]);
			if (FindSmall == i)
			{
				FindSmall = FindLarge;
			}
			Swap(&arr[sz - 1], &arr[FindSmall]);
		}
		sz--;											//sz控制尾部向前移动
	}
}

void BubbleSortRevised(int* arr, int sz, COM rule)
{
	assert(arr);
	for (int i = 0; i < sz - 1; i++)
	{
		bool flag = true;
		for (int j = 1; j < sz - i; j++)
		{
			if (rule(arr[j], arr[j - 1]))
			{
				Swap(&arr[j], &arr[j - 1]);
				flag = false;
			}
		}
		if (flag)									//如果一趟对比下来没有将flag置false，则继续比对
		{											//最好情况为有序数组，只需遍历一遍即可，时度O(N)
			return;
		}
	}

}

void QuickSort(int* arr, int Head, int Tail)
{
	count++;
	if (Head >= Tail)
	{
		return;
	}
	int key = Head;
	//key = HoareSort(arr, left, right);
	//key = PitSort(arr, left, right);
	key = PointerSort(arr, Head, Tail);
	if (Head - Tail < 15)
	{
		QuickSort(arr, Head, key - 1);
		QuickSort(arr, key + 1, Tail);
	}
	else
	{
		InsertSort2(arr + Head, Tail - Head + 1, Ascend);
	}

}

//hoare版
int HoareSort(int* arr, int left, int right)
{
	int key = left;
	while (left < right)
	{
		while (left < right && arr[right] >= arr[key])
		{
			right--;
		}
		while (left < right && arr[left] <= arr[key])
		{
			left++;
		}
		Swap(&arr[left], &arr[right]);
	}
	Swap(&arr[left], &arr[key]);
	key = left;
	return key;
}

//挖坑法
int PitSort(int* arr, int left, int right)
{
	int key = left, keyval = arr[key], pit = left;
	while (left < right)
	{
		while (left < right && arr[right] <= keyval)
		{
			right--;
		}
		arr[pit] = arr[right];
		pit = right;
		while (left < right && arr[left] >= keyval)
		{
			left++;
		}
		arr[pit] = arr[left];
		pit = left;
	}
	arr[pit] = keyval;
	key = left;
	return key;
}

//前后指针法
int PointerSort(int* arr, int left, int right)
{
	int cur = left + 1, prev = left, key = left, mid = GetMid(arr, left, right);
	Swap(&arr[key], &arr[mid]);
	while (cur <= right)
	{
		if (arr[cur] < arr[key] && ++prev != cur)
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
	int a[3] = { arr[left], arr[mid], arr[right] };
	InsertSort2(a, 3, Descend);
	if (a[1] == arr[left])
		return left;
	else if (a[1] == arr[mid])
		return mid;
	else
		return right;
}

void QuickSortStack(int* arr, int Head, int Tail)
{
	ST* a = StackInit();
	StackPush(a, Tail);
	StackPush(a, Head);
	while (!StackEmpty(a))
	{
		int left = StackTop(a);
		StackPop(a);
		int right = StackTop(a);
		StackPop(a);
		if(left < right)
		{
			int key = PointerSort(arr, left, right);
			StackPush(a, right);
			StackPush(a, key + 1);
			StackPush(a, key - 1);
			StackPush(a, left);
		}
	}
}

void Subsort(int* arr, int* tmp, int Head, int Tail)
{
	if (Head >= Tail)
	{
		return;
	}
	int mid = (Head + Tail) / 2;
	Subsort(arr, tmp, Head, mid);
	Subsort(arr, tmp, mid + 1, Tail);
	int left = Head, leftend = mid;
	int right = mid + 1, rightend = Tail;
	int i = 0;
	while (left <= leftend && right <= rightend)
	{
		if (arr[left] <= arr[right])
			tmp[i++] = arr[left++];
		else
			tmp[i++] = arr[right++];
	}
	while (left <= leftend)
		tmp[i++] = arr[left++];
	while(right <= rightend)
		tmp[i++] = arr[right++];
	memcpy(arr + Head, tmp, (Tail - Head + 1) * sizeof(int));
}

void MergeSort(int* arr, int sz)
{
	int* tmp = (int*)malloc(sz * sizeof(int));
	assert(tmp);
	Subsort(arr, tmp, 0, sz - 1);
	free(tmp);
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
			int startchange = left;								//需要更新的实参数组起点
			int leftend = left + gap - 1, right = left + gap, rightend = right + gap - 1;
			if (leftend >= sz || right >= sz)					//边界处理，如果左末下标越界或右起点下标越界，直接结束循环不归并
			{
				break;
			}
			else if (rightend >= sz)							//如果右末下标越界，则将该下标调整至数组末元素下标，以处理未被归并的末元素
			{
				rightend = sz - 1;
			}
			int memchange = rightend - left + 1;				//需要更新的实参数组个数
			while (left <= leftend && right <= rightend)		//归并开始
			{
				if (arr[left] <= arr[right])
					tmp[i++] = arr[left++];
				else
					tmp[i++] = arr[right++];
			}
			while (left <= leftend)
				tmp[i++] = arr[left++];
			while (right <= rightend)
				tmp[i++] = arr[right++];						//归并结束
			memcpy(arr + startchange, tmp + startchange, memchange * sizeof(int));		//内存拷贝需放在每一小次归并结束的循环中而不能放在一趟循环外，是因为可能会拷贝无效的数据
			left += gap;					//跳跃已经归并好的范围，开始对新数据归并				
		}
		gap *= 2;							//将归并调整的范围扩大，每次扩大二倍
	}
	free(tmp);
}

void CountSort(int* arr, int sz)
{
	assert(arr);
	int max = arr[0], min = arr[0];
	for (int i = 0; i < sz; i++)
	{
		if (max < arr[i])
			max = arr[i];
		if (min > arr[i])
			min = arr[i];
	}
	int range = max - min + 1;
	int* countarr = (int*)malloc(range * sizeof(int));
	assert(countarr);
	memset(countarr, 0, range * sizeof(int));
	for (int i = 0; i < sz; i++)
	{
		countarr[arr[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (countarr[i]--)
		{
			arr[j++] = i + min;
		}
	}
}
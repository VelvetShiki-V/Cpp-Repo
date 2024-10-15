#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//Leetcode:合并两个有序数组
//描述：有两个非递减顺序排列整型数组nums1和nums2，另有sz1和sz2给你两个按非递减顺序
//排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
//如输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
//输出：[1, 2, 2, 3, 5, 6]
//解释：需要合并[1, 2, 3] 和[2, 5, 6] 。
//合并结果是[1, 2, 2, 3, 5, 6] ，其中斜体加粗标注的为 nums1 中的元素。
//要求：时间复杂度O(N), 空间复杂度O(M+N)
int* merge(int* nums1, int num1Size, int* nums2, int nums2Size)
{
	int move1 = num1Size - 1;
	int move2 = nums2Size - 1;
	int ptr = num1Size + nums2Size - 1;
	while (move1 >= 0 && move2 >= 0)
	{
		if (nums1[move1] > nums2[move2])
		{
			nums1[ptr--] = nums1[move1--];
		}
		else
		{
			nums1[ptr--] = nums2[move2--];
		}
	}
	while (move1 < 0 && move2 >= 0)					//当nums1的move1下标越界，判断nums2中有负数且没有赋值完毕时进入该循环
	{
		nums1[ptr--] = nums2[move2--];
	}
	return nums1;
}
int main()
{
	//int nums1[] = { 1,2,3,0,0,0 };
	//int nums2[] = { 2,5,6 };
	//int nums1[] = { 1,3,5,7,10,0,0,0,0,0 };
	//int nums2[] = {2,4,7,8,9};
	//int nums1[] = { 1,3,5,7,10,0,0,0,0,0 };
	//int nums2[] = { -7,-4,-2,8,9 };
	int nums1[] = { -5,-3,-1,7,10,0,0,0,0,0 };
	int nums2[] = { -7,-4,-2,8,9 };
	int sz1 = sizeof(nums1) / sizeof(nums1[0]);
	int sz2 = sizeof(nums2) / sizeof(nums2[0]);
	int* arr = merge(nums1, sz1 - sz2, nums2, sz2);
	for (int i = 0; i < sz1; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}


//Leetcode:删除有序数组重复项（去重算法）
//描述：有一个升序排列数组nums，要求原地删除重复出现元素，使每个元素仅出现一次，并返回删除后数组的新长度
//如（nums = {0,0,1,1,1,2,2,3,3,4}，修改后的数组为nums = {0,1,2,3,4}，新长度为newsize = 5）
//去重后的数组各元素间的相对顺序仍需保持一致（升序）
//要求：时间复杂度O(N), 空间复杂度O(1)
//int removeDuplicates(int* nums, int numSize)
//{
//	int ptr = 0, move = 0;
//	while (move < numSize)
//	{
//		if (nums[ptr] == nums[move])
//		{
//			move++;
//		}
//		else
//		{
//			nums[++ptr] = nums[move++];
//		}
//	}
//	return ++ptr;
//}
//
//int main()
//{
//	//int nums[] = { 0,0,1,1,1,2,2,3,3,4 };
//	//int nums[] = { 0,0,1,1,1,2,2,3,3,4 };
//	//int nums[] = { 0,0,0,2,2,3};
//	int nums[] = { 0,1,2,3,4,4 };
//	int sz = sizeof(nums) / sizeof(nums[0]);
//	int ret = removeDuplicates(nums, sz);
//	printf("New size is:%d\n", ret);
//	return 0;
//}


//Leetcode:数组元素移除
//描述：给一个数组和值val，要求删除与val相等的所有元素，
//并返回新数组长度（如数组1,2,2,3,3,4,5,6，要求删除val=3，返回新sz=6）
//要求：时间复杂度O(N), 空间复杂度O(1)
//int removeElement(int* nums, int sz, int val) 
//{
//	int ptr = 0, move = 0;
//	while (move < sz)
//	{
//		if (nums[ptr] == val)
//		{
//			if (nums[move] == val)
//			{
//				move++;
//			}
//			else
//			{
//				nums[ptr++] = nums[move++];
//			}
//		}
//		else
//		{
//			ptr++;
//			move++;
//		}
//	}
//	return ptr;
//}
//
//int main()
//{
//	int arr[10] = { 1,2,2,3,5,7,8,8,9,13 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int Delete = 13;
//	int NewSize = removeElement(arr, sz, Delete);
//	printf("New size of array is: %d", NewSize);
//	return 0;
//}
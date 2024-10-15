#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"

//4. 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
//有效字符串需满足：
//左括号必须用相同类型的右括号闭合。
//左括号必须以正确的顺序闭合。
int main()
{
	//char arr[7] = "()[]{}";
	char arr[5] = "(]{}";
	int size = sizeof(arr) / sizeof(arr[0]);
	if (BracketMatch(arr, size))
	{
		puts("true");
	}
	else
	{
		puts("false");
	}
	return 0;
}


//3. 深拷贝带随机指针的链表
//描述：给一个长度为 n 的链表，每个节点包含一个随机指针random ，该指针可以指向链表中的任何节点或空节点。
//要求将该附带随即指针的链表完全拷贝一份，并返回该拷贝的头结点地址，注意该拷贝链表的指针不能指向任何原链表结点
//int main()
//{
//	RD* n1 = BuyRandom(1);
//	RD* n2 = BuyRandom(2);
//	RD* n3 = BuyRandom(3);
//	RD* n4 = BuyRandom(4);
//	RD* n5 = BuyRandom(5);
//	n1->next = n2;
//	n1->random = n3;
//	n2->next = n3;
//	n3->next = n4;
//	n3->random = n1;
//	n4->next = n5;
//	n4->random = n2;
//	n5->random = n5;
//
//	RD* Duplicate = Copy(n1);				//调试观察
//	return 0;
//}

//2. 环形链表——返回入环结点
//描述：给定一个链表的头节点Head ，返回链表开始入环的第一个节点地址； 如果链表无环，则返回 null
//int main()
//{
//	SGL* n1 = BuyListNode(1);
//	SGL* n2 = BuyListNode(2);
//	SGL* n3 = BuyListNode(3);
//	SGL* n4 = BuyListNode(4);
//	SGL* n5 = BuyListNode(5);
//	n1->next = n2;
//	n2->next = n3;
//	n3->next = n4;
//	n4->next = n5;
//	n5->next = n3;						//以第k个结点为入环点
//	if (Detect(n1))
//	{
//		printf("有环\n");
//	}
//	else
//	{
//		printf("无环\n");
//	}
//	printf("入环点为：%d\n", Enter(n1));
//}



//1. LeetCode--旋转数组——逆置算法
//描述：一个数组，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
//要求时间复杂度O(N)，空间复杂度O(1)，原地算法
//例：输入 : nums = [1, 2, 3, 4, 5, 6, 7], k = 3    输出 : [5, 6, 7, 1, 2, 3, 4]
//输入：nums = [-1, -100, 3, 99], k = 2				输出：[3, 99, -1, -100]
//int* Reverse(int arr[], int sz)
//{
//	int left = 0, right = sz - 1;				//右下标应为sz - 1，若下标==size，则会访问越界
//	while (left < right)						//如果使用异或交换，left不能等于right，防止计数个数时将中间数值置为0（因为一个数异或本身为0）
//	{
//		arr[left] ^= arr[right];
//		arr[right] ^= arr[left];
//		arr[left] ^= arr[right];
//		left++;
//		right--;
//	}
//	return arr;
//}
//
//int* RotateARR(int arr[], int sz, int k)
//{
//	Reverse(arr, sz - k);
//	Reverse(arr + sz - k, k);
//	Reverse(arr, sz);
//	return arr;
//}
//
//int main()
//{
//	//int arr[5] = { 1,2,3,4,5 };
//	int arr[9] = { 1,2,3,4,5,6,7,8,9 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int* Rarr = RotateARR(arr, sz, 8);
//	for (int i = 0; i < sz; i++)
//	{
//		printf("%d ", Rarr[i]);
//	}
//	return 0;
//}
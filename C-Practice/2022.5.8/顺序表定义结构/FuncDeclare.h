#pragma once
typedef int SLElemType;

//顺序表声明
typedef struct SeqList
{
	//int arr[100];			//类型不可变，容量不可变定义方式——静态顺序表
	SLElemType* arr;		//指向动态开辟数组的指针——类型可变，数组容量可被初始化函数中malloc改变
	int size;				//顺序表中有效数据个数，数值总是为末元素下标值+1
	int capacity;			//当数组容量不够扩容时，使用扩容函数中realloc改变
}SL;						//SL为线性表结构体类型名

//增删查改功能
/*void SLInit(SL s);*/							//定义结构体形参s传入初始化SLInit函数
void SLInit(SL* ps);							//将结构体形参指针ps传入初始化函数并通过解引用改变实参值
void SLCapacityCheck(SL* ps);					//顺序表容量防满和扩容函数，用于动态开辟数组空间
void PushFront(SL* ps, SLElemType x);			//头插
void PushBack(SL* ps, SLElemType x);			//尾插，参数为实参取地址和待尾插值
void PopBack(SL* ps);							//尾删
void PopFront(SL* ps);							//头删
void SLDestroy(SL* ps);							//释放动态开辟的顺序表数组地址
void SLInsert(SL* ps, int pos, SLElemType x);	//在第pos个位置插入数值函数
void SLErase(SL* ps, int pos);					//在第pos个位置擦除数据函数
int SLFind(SL* ps, SLElemType x);				//找一个值，返回其下标位置
int SLModify(SL* ps, int pos, SLElemType x);
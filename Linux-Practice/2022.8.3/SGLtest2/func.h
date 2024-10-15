#include<iostream>
#include<assert.h>
#include<stdlib.h>
using namespace std;

//顺序表
typedef int SGLEtype;
typedef struct SigLinkList
{
    SGLEtype* arr;
    int size;
    int capacity;
}SGL;

//功能函数
void SGLInit(SGL& Head);
void SGLPushBack(SGL& Head, SGLEtype x);
void SGLPushFront(SGL& Head, SGLEtype x);
int SGLSearch(SGL& Head);
void SGLModify(SGL& Head, SGLEtype x);
void SGLPrint(const SGL& Head);

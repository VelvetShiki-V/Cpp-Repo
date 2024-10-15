#include"func.h"


void SGLInit(SGL& Head)
{
    Head.arr = NULL;
    Head.size = Head.capacity = 0;
}

void CapacityCheck(SGL& Head)
{
    if(Head.size == Head.capacity)
    {
       int expand = Head.capacity == 0 ? 4 : Head.capacity * 2;
       SGLEtype* tmp = (SGLEtype*)realloc(Head.arr, sizeof(SGLEtype) * expand);
       assert(tmp);
       Head.arr = tmp;
       Head.capacity = expand;
    }
}

void SGLPushBack(SGL& Head, SGLEtype x)
{
    CapacityCheck(Head);
    Head.arr[Head.size++] = x;
    Head.capacity++;
}

void SGLPushFront(SGL& Head, SGLEtype x)
{
    CapacityCheck(Head);
    int tail = Head.size;
    while(tail > 0)
    {
        Head.arr[tail] = Head.arr[tail - 1];
        tail--;
    }
    Head.arr[tail] = x;
    Head.size++;
    Head.capacity++;
}


void SGLPrint(const SGL& Head)
{
    for(int i = 0; i < Head.size; i++)
    {
        cout << Head.arr[i] << ' ';
    }
}

int& SGLSearch(SGL& Head, SGLEtype x)
{
    for(int i = 0; i < Head.size; i++)
    {
        if(x == Head.arr[i])
        {
            return i;
        }
    }
    return -1;
}

void SGLModify(SGL& Head, int value, SGLEtype x)
{
    
}

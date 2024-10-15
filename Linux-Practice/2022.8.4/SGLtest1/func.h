#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct SGList
{
    int data;
    struct SGList* next;
}SGLNode;

SGLNode* BuyListNode(int x);
void ListPrint(SGLNode* Head);
void PushBack(SGLNode** Head, int x);
void PopBack(SGLNode** Head);

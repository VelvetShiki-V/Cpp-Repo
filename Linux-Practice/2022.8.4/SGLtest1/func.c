#include"func.h"


SGLNode* BuyListNode(int x)
{
    SGLNode* New = (SGLNode*)malloc(sizeof(SGLNode));
    assert(New);
    New->data = x;
    New->next = NULL;
    return New;
}
void ListPrint(SGLNode* Head)
{
    SGLNode* cur = Head;
    while(cur)
    {
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

void PushBack(SGLNode** Head, int x)
{
    assert(Head);
    if(*Head == NULL)
    {
        *Head = BuyListNode(x);
        return;
    }
    SGLNode* tail = *Head;
    while(tail->next)
    {
        tail = tail->next;
    }
    tail->next = BuyListNode(x);
}

void PopBack(SGLNode** Head)									//链表尾删
{
	assert(Head);
    if((*Head) != NULL)											//如果链表不为空才可尾删
    {
		if ((*Head)->next == NULL)
        {
            free(*Head);										//先通过指向该结点的结构体指针释放该结点的空间
            *Head = NULL;
            //谨记将指向结点的指针置空前，必须先释放该结点malloc的内存空间，否则无法通过该指针找到对应空间释放内存
                                                                //对于尾删结点，先释放，再置空
        }
        else
        {
            SGLNode* Tail = *Head;
            while (Tail->next->next != NULL)					//找倒数第二个结点Tail
            {
                Tail = Tail->next;
            }
            free(Tail->next);									//释放尾结点
            Tail->next = NULL;									//并使倒数第二个结点的后续指针置空
        }
 }
}

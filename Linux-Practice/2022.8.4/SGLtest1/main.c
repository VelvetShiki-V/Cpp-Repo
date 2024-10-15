#include"func.h"

void test1()
{
    SGLNode* n1 = BuyListNode(1);
    SGLNode* n2 = BuyListNode(2);
    SGLNode* n3 = BuyListNode(3);
    SGLNode* n4 = BuyListNode(4);
    SGLNode* n5 = BuyListNode(5);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    
    ListPrint(n1);

    PopBack(&n1);
    PopBack(&n1);

    ListPrint(n1);
}

int main()
{
    test1();
    return 0;
}

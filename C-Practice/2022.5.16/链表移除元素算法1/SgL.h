#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int Etype;
typedef struct Singly_linked_list
{
	Etype data;
	Singly_linked_list* next;
}SgL;

SgL* BuyListNode(Etype Newnode);
void Print(SgL* Head);
SgL* Remove(SgL* Head, int value);
#pragma once
#include<iostream>
using namespace std;

typedef struct stack
{
	int* arr;
	int top;
	int capacity;
}ST;

void StackInitial(ST* Bot, int cap = 10)
{
	Bot->arr = (int*)calloc(cap, sizeof(int));
	Bot->top = 0;
	Bot->capacity = cap;
}

int multi(int a, int b)
{
	return a * b;
}

float multi(float c, float d)
{
	return c * d;
}

double multi(double e, double f)
{
	return e * f;
}
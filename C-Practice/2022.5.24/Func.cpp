#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
ST* StackInit()
{
	ST* init = (ST*)malloc(sizeof(ST));
	assert(init);
	init->a = NULL;
	init->capacity = init->top = 0;
	return init;
}

void STPop(ST* Bot)
{
	assert(Bot);
	if (Bot->top != 0)
	{
		Bot->top--;
	}
}

SType STTop(ST* Bot)
{
	assert(Bot);
	if (Bot->top != 0)
	{
		return Bot->a[Bot->top - 1];
	}
	return NULL;
}

bool BracketMatch(char* arr, int sz)
{
	ST* match = StackInit();
	assert(match);
	if (match->capacity == match->top)
	{
		int expand = match->capacity == 0 ? sz : match->capacity * 2;
		SType* newcap = (SType*)realloc(match->a, sizeof(SType) * expand);
		assert(newcap);
		match->a = newcap;
		match->capacity = expand;
	}
	char* cur = arr;
	char tmp[3] = { '0' };
	while (*cur != '\0')
	{
		if (*cur == '(' || *cur == '[' || *cur == '{')
		{
			match->a[match->top] = *cur;
			cur++;
			match->top++;
			continue;
		}
		if (*cur == ')' || *cur == ']' || *cur == '}')
		{
			if (cur == arr)
			{
				return false;
			}
			match->a[match->top] = *cur;
			match->top++;
			tmp[1] = STTop(match);
			STPop(match);
			tmp[0] = STTop(match);
			STPop(match);
		}
		if (strcmp(tmp, "()") && strcmp(tmp, "[]") && strcmp(tmp, "{}"))
		{
			return false;
		}
		cur++;
	}
	if (match->top > 0)
	{
		return false;
	}
	return true;
}
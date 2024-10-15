#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"FuncDeclare.h"

//˳���Ľṹ�������ʼ��
void SLInit(SL* ps)
{
	//s.arr = NULL;						//�βδ�ֵд��������ı���Main�ﶨ�崫����ʵ������ֵ
	//s.size = s.capacity = 0;
	assert(ps);							//Ԥ��ʽ��̣���ֹ�����\Ұָ�뵫����������
	ps->arr = NULL;						//�������ַ�ÿ�
	ps->size = ps->capacity = 0;		//��Ч��ֵ������������0
}

//���˳���ṹ�������Ƿ�Ϊ�ջ����������̬����
void SLCapacityCheck(SL* ps)
{
	assert(ps != NULL);
	if (ps->capacity == ps->size)														//�����������Ч��ֵ����������������˳�����
	{
		int Expand = ps->capacity == 0 ? 4 : ps->capacity * 2;							//�ж�������գ�Ϊ�����¿��ٿռ䣬��Ϊ����ʹԭ��������1��
		SLElemType* tmp = (SLElemType*)realloc(ps->arr, Expand * sizeof(SLElemType));	//ʹ��realloc��malloc������̬����
		if (tmp == NULL)																//��ֹ����ʧ��
		{
			printf("%s\n", strerror(errno));
			exit(-1);
		}
		else
		{
			ps->arr = tmp;																//���¿��ٵ��ڴ��ַ����ԭ���飨ԭ�����ݻ�������ݣ�
			ps->capacity = Expand;														//��ʹ˳�����������
		}
	}
}

//β�庯��
void PushBack(SL* ps, SLElemType x)
{
	assert(ps);
	SLCapacityCheck(ps);			//���˳��������Ƿ������Ϊ�գ�����̬��������
	ps->arr[ps->size] = x;		//��β��ֵ����sizeֵ��Ӧ�������±�
	++ps->size;					//��ʹsize + 1����ʾ�²�����һ��ֵ
}

//ͷ�庯��
void PushFront(SL* ps, SLElemType x)
{
	assert(ps != NULL);
	SLCapacityCheck(ps);
	int end = ps->size - 1;
	while (end >= 0)
	{
		ps->arr[end + 1] = ps->arr[end];
		--end;
	}
	ps->arr[0] = x;
	++ps->size;
}

//βɾ����
void PopBack(SL* ps)
{
	//if (ps->size != 0)			//Ҳ����ʹ��assert(ps->size > 0);������飬��printf��ӡ��ʾ
	//{
	//	--ps->size;
	//}
	//else
	//{
	//	printf("The Sequence List is already empty.\n");
	//}
	assert(ps);
	assert(ps->size > 0);			//sizeֻ�д���0���ܽ���ɾ������������size���ܻ��Ϊ����
	ps->size--;
}

//ͷɾ����
void PopFront(SL* ps)
{
	assert(ps != NULL);
	assert(ps->size > 0);			//sizeֻ�д���0���ܽ���ɾ������������size���ܻ��Ϊ����
	int begin = 1;
	while (begin < ps->size)
	{
		ps->arr[begin - 1] = ps->arr[begin];
		begin++;
	}
	if (ps->size != 0)
	{
		ps->size--;
	}
}

//�ͷ��ڴ�
void SLDestroy(SL* ps)
{
	assert(ps);
	free(ps->arr);					//ֻ��free�Ż��������Ƿ�Խ�磬��Խ��ʱ�Ŀ���realloc��size���ʲ��ᱨ��
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

//void SLInsert(SL* ps, SLElemType x)

#define _CRT_SECURE_NO_WARNINGS 1
#include"Queue.h"

void QueueTest_1()							//��������Ϊ�Ƚ��ȳ�������������;���������ݣ��������ݵ����˳�򶼲���
{
	QP QueuePtr;
	QueueInit(&QueuePtr);
	QPushBack(&QueuePtr, 1);
	QPushBack(&QueuePtr, 2);
	QPushBack(&QueuePtr, 3);
	QPushBack(&QueuePtr, 4);
	QPushBack(&QueuePtr, 5);
	//QueueDestroy(&QueuePtr);				//��ǰ���ٶ��У���������ʻ������ӡ���ᣬȡֵ�ᣩ
	QPopFront(&QueuePtr);
	QPopFront(&QueuePtr);
	QPopFront(&QueuePtr);
	//QPopFront(&QueuePtr);
	//QPopFront(&QueuePtr);					//����Ԫ��ȫ��ͷɾ�꣬��ʱ����Ϊ��
	Print(&QueuePtr);						//��ӡֻ��Ϊ�˷���۲죬���������ʹ涨�����Ԫ��ֻ��ͨ��ͷɾֱ������β��ÿ�����ݲ������ܹ�ȡ��
	printf("��ͷԪ��Ϊ��%d\n", GetQHead(&QueuePtr));
	printf("��βԪ��Ϊ��%d\n", GetQTail(&QueuePtr));
	printf("���д�СΪ��%d\n", QueueSize(&QueuePtr));
	QueueDestroy(&QueuePtr);
}

int main()
{
	QueueTest_1();
	return 0;
}
#pragma once
typedef int SLElemType;

//˳�������
typedef struct SeqList
{
	//int arr[100];			//���Ͳ��ɱ䣬�������ɱ䶨�巽ʽ������̬˳���
	SLElemType* arr;		//ָ��̬���������ָ�롪�����Ϳɱ䣬���������ɱ���ʼ��������malloc�ı�
	int size;				//˳�������Ч���ݸ�������ֵ����ΪĩԪ���±�ֵ+1
	int capacity;			//������������������ʱ��ʹ�����ݺ�����realloc�ı�
}SL;						//SLΪ���Ա�ṹ��������

//��ɾ��Ĺ���
/*void SLInit(SL s);*/							//����ṹ���β�s�����ʼ��SLInit����
void SLInit(SL* ps);							//���ṹ���β�ָ��ps�����ʼ��������ͨ�������øı�ʵ��ֵ
void SLCapacityCheck(SL* ps);					//˳����������������ݺ��������ڶ�̬��������ռ�
void PushFront(SL* ps, SLElemType x);			//ͷ��
void PushBack(SL* ps, SLElemType x);			//β�壬����Ϊʵ��ȡ��ַ�ʹ�β��ֵ
void PopBack(SL* ps);							//βɾ
void PopFront(SL* ps);							//ͷɾ
void SLDestroy(SL* ps);							//�ͷŶ�̬���ٵ�˳��������ַ
void SLInsert(SL* ps, int pos, SLElemType x);	//�ڵ�pos��λ�ò�����ֵ����
void SLErase(SL* ps, int pos);					//�ڵ�pos��λ�ò������ݺ���
int SLFind(SL* ps, SLElemType x);				//��һ��ֵ���������±�λ��
int SLModify(SL* ps, int pos, SLElemType x);
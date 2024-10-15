#include"Declaration.h"

//����Ϊ��Ϸ��������
#define MAX 100						//�������������
#define Length 2					//�߳�ʼ���ȣ���󲻳���5(Recommended)
#define Scale 						//��ÿ�ڴ�С
#define FoodSize 5					//ʳ���С

//����Ϊ��Ϸ���ģ��Ľṹ��ģ��
struct snake						//�߽ṹ����
{
	int length;						//�ߵĳ�ʼ����
	int direction;					//�ߵĳ�ʼ����
	int speed;						//�ߵ��ٶ�
	POINT coord[MAX];				//��������MAX��Ƕ������ṹ������POINT��ͨ��coord[].x��coord[].y������ͷ��������ʵ���ߵ��ƶ�
};

enum direction						//������������ҷ���ö�ٶ���
{
	UP,								//0
	DOWN,							//1
	LEFT,							//2
	RIGHT							//3
};

struct Food							//ʳ�ﶨ��
{
	int x;							//ʳ�������
	int y;							//ʳ��������
	int r;							//ʳ���С�뾶
	DWORD color;					//unsigned long�ͱ���������ʳ����ɫRGBֵ
	time_t t;						//ʳ������Ϸ��������ɱ���
	bool flag;						//�ж�ʳ���Ƿ񱻳Ե��Ĳ���������0���ԣ�1û���ԣ�
};

//��Ϸ���ܺ���
int GameOver();						//��Ϸ����������Ϊ�գ�����ֵ���أ�����1���˳�0��
void GamePass(int PassNum);			//��Ϸͨ�أ�����Ϊ����ͨͨ�ص���һ���棬��ͨ�ػ�ʤ������Victory��
void Victory();						//��Ϸʤ��������Ϊ��
void Infinity();

//��������
int KeyBoardControl();				//ͨ�����̺�Windows��̬�⺯��ʵ��WASD�������ƶ�
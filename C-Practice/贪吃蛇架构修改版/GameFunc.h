#include"Declaration.h"

//��Ϸ���ܺ���
void GamePlay();										//��ʼ��Ϸ
void GameOver();										//��Ϸ����
void GamePass(int PassNum);								//��Ϸͨ��
void Victory();											//��Ϸʤ��
void SnakeMove();										//������ͷ�ƶ�����
void GameDraw();										//̰���ߺ�ʳ��ͼ�εĻ������
void FoodInit();										//ʳ���������ɺͳ���λ�ú���
void SnakeInit();										//�߳������״̬�ĳ�ʼ��
void BorderLine(int SnakeState);						//��������߽���ײ��⺯��
void EatSelf(int SnakeState);							//��������������ײ��⺯��
void EatFoot();											//ʳ�ﱻ���жϺ���

//��������
int KeyBoardControl();				//ͨ�����̺�Windows��̬�⺯��ʵ��WASD�������ƶ�
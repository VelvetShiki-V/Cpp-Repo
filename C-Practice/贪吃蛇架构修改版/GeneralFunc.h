#include"Declaration.h"

int MouseClick(ExMessage* click, int BUT_Width, int BUT_Height);	//ͨ��������������溯��������Ϊ��ExMessage*��깦�ܽṹ���ַ������ʵ��������Ҽ������Ľ���
																	//�Լ��������������İ�ť���
void Button(int shape, int x, int y);								//��ť��ʽ��ƺ���������Ϊ����״��
void TurnTo(int PageNum);											//������ת����������Ϊ����Ҫ��ת�Ľ����ţ�����ҳPageNum = 1,ģʽҳ��PageNum = 2�ȵȣ�
void Text(char* text, int x, int y);								//�ı��������
void Music(int MusicNum);											//���ֲ��ź���������Ϊ��������ţ����Ż�ֹͣ��
void Message(LPCSTR* title, LPCSTR* content);						//��������������Ϊ���������⣬�������ݣ�����Ϊ�����ַ�ָ��LPCSTR*��
void PicInsert(IMAGE img, char* route, int width, int height, int change);		//����ͼƬ�򱳾�����������Ϊ��ͼƬָ�룬ͼƬ·���ַ�����������ͼƬ��ߣ� // ���·���� "./image.jpg"		����·����"D:\App\Adobe\Dw"
void ParaCenter(int* x, int* y);									//ˮƽ���к���������Ϊ��ͼƬ���ı��������ص��������ĵ�ַint*��
void Exit();														//�˳�

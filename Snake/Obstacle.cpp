#include "Obstacle.h"

Obstacle::Obstacle() :BaseClass(0, 0) //���캯������ʽ���û���BaseClass��Ĭ�Ϲ��캯��BaseClass(0,0)
//ʹ�ϰ�������ֲ��ڵ�ͼ�ڣ�������Ϊ 10 �ı���������������ײ��⣩
{
	m_x = (1 + rand() % 50) * 10 + 10;
	m_y = (1 + rand() % 40) * 10 + 10;
}


void Obstacle::ChangeObstacle() //�ı��ϰ����λ��
//���������ϰ�������λ�ã����ڶ�̬ˢ��

{
	m_x = (1 + rand() % 50) * 10 + 10;
	m_y = (1 + rand() % 40) * 10 + 10;
}

 
void Obstacle::Show() //Show ��Ա����
{
	setfillcolor(BLACK);//��ɫ
	fillrectangle(m_x, m_y, m_x + 10, m_y - 10);
}



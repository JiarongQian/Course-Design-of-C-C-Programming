#include "BaseClass.h"
#include "FileInclude.h"

BaseClass::BaseClass() // Ĭ�Ϲ��캯��
{
	m_x = 50;
	m_y = 50;
}


BaseClass::BaseClass(int x, int y)
//�������Ĺ��캯�������� x �� y ����ֵ�����ڳ�ʼ�������λ������
{
	m_x = x;
	m_y = y;
}


void BaseClass::Show() 
//Show ��Ա����
{
	setlinecolor(BLACK); //���û���ͼ�ε�������ɫΪ��ɫ
	setfillcolor(RGB(255, 128, 0)); //���������ɫΪ��ɫ
	fillcircle(m_x, m_y, 5); //������ (m_x, m_y) ������һ���뾶Ϊ 5 �����Բ��
}


void BaseClass::Move(int x, int y)
//Move ��Ա����������ƫ������x,y�������¶�������
{
	m_x = m_x + x;
	m_y = m_y + y;
}

//Ϊ����ĳ�ʼ������ʾ���ƶ��ṩ������߼���
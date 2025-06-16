#include "Item.h"
#include "Game.h"

Item::Item():BaseClass(0,0) //���캯����ͨ��BaseClss��0��0����ʾ���û��๹�캯��
//ʹ��������ֲ�����Ϸ��ͼ�ڣ�������Ϊ 10 �ı��������������ͼ��
{
	m_x = (1 + rand() % 50) * 10 + 10; // x ������ [20, 510] ��Χ���������
	m_y = (1 + rand() % 40) * 10 + 10; //y ������ [20, 410] ��Χ���������
}


void Item::Change()// Change ��Ա����
//�������ɵ��ߵ����λ�ã����ڵ��߱��Ե���ˢ�£����߳Ե�����ʱ�����ô˺�������λ�����ɵ���
{
	m_x = (1 + rand() % 50) * 10 + 10;
	m_y = (1 + rand() % 40) * 10 + 10;
}


void Item::Show() //����Ļ����ʾ Item ����
//��д����BaseClass::Show()���������ݵ������ͻ��Ʋ�ͬ��ɫ

{
	if (m_item_type == ITEM_DRUGS)//ҩƷ->��ɫ
	{
		setfillcolor(RGB(255, 0, 0));
		fillcircle(m_x, m_y, 5);
	}
	else if(m_item_type == ITEM_COIN) //���->��ɫ
	{
		setfillcolor(RGB(255, 215, 0));
		fillcircle(m_x, m_y, 5);
	}
	else if (m_item_type == ITEM_DOUBLE_COIN)//˫�����->��ɫ
	{
		setfillcolor(RGB(255, 200, 0));
		fillcircle(m_x, m_y, 5);
	}
}
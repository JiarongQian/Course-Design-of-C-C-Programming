#ifndef ITEM_H
#define ITEM_H

#include "BaseClass.h"

class Item : public BaseClass 
	//���� Item �࣬�̳��� BaseClass
{
public:
	Item();//Ĭ�Ϲ��캯��
	void Change();//���ڸı� Item �����״̬������
	void Show(); //����Ļ����ʾ Item ����

	void SetItemType(int type) { m_item_type = type; }
	//���� Item ���������

	int GetItemType() { return m_item_type; }
	//��ȡ Item ��������ͣ����������жϵ�

public:
	int m_item_type;
	//���ڱ�ʾ Item ���������
};

#endif // !ITEM_H


#ifndef  BASE_CLASS_H
#define  BASE_CLASS_H
  
#include "FileInclude.h"

//�����͹������λ������Ķ���

class BaseClass //������ ��Ϊ������Ļ���
{
public:
	BaseClass();//Ĭ�Ϲ��캯��
	BaseClass(int x, int y);//�������Ĺ��캯��������x��y����ֵ�����ڳ�ʼ�������λ������

	virtual void Show(); //�麯����������������д�˺�����ʵ���Զ������ʾ�߼�
	void Move(int x, int y); //�ƶ�����������x��y����ֵ�������ƶ������µ�λ��

public://�������е����ͳ�Ա���������ڴ洢���������λ��
	int m_x;
	int m_y;
};

#endif // !BASE_CLASS_H

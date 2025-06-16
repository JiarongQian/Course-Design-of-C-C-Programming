#ifndef SNAKE_H
#define SNAKE_H

#include "BaseClass.h"

class Snake : public BaseClass
	//���� Snake �࣬�̳��� BaseClass

{
public:
	Snake(); //���캯��

	void SetSnakeLen(int n);
	//���������ߵĳ���

	virtual void Show();
	//��д������麯������������Ϸ��������ʾ�ߵ�����

	void DirectionMove(); 
	//���ݵ�ǰ���������ͷ��λ��

	void BodyMove(); 
	//����ʵ����������ƶ��߼��������������ÿ���ڵ�λ��

	void AddSnake();
	//�����ߵĳ��ȣ�����Ե�ʳ������ӳ��ȣ�
	
	void AddSpeed(int add_value);
	//���������ߵ��ƶ��ٶ�

public://���幫�г�Ա����
	char m_direction; //���ڴ洢�ߵ�ǰ���ƶ�����
	int m_speed;    //���ڴ洢�ߵ�ǰ���ƶ��ٶ�
	int m_snake_len; //���ڼ�¼�ߵĵ�ǰ���ȡ�
	std::vector<BaseClass> m_nodes;
	//���ڴ洢������ĸ����ڵ㣨ÿ���ڵ㶼��BaseClass���ͣ�����m_x,m_y���꣩
};

#endif // !SNAKE_H


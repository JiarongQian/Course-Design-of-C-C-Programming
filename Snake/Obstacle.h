#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "BaseClass.h"

class Obstacle : public BaseClass
	//���� Obstacle �࣬�̳��� BaseClass
{
public:
	Obstacle();//Ĭ�Ϲ��캯�������ڳ�ʼ�� Obstacle ����

	virtual void Show(); 
	//��д������麯������������Ϸ��������ʾ�ϰ��������

	void ChangeObstacle(); 
	//�ı��ϰ����״̬������
};


#endif // !OBSTACLE_H


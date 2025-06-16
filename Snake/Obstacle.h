#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "BaseClass.h"

class Obstacle : public BaseClass
	//定义 Obstacle 类，继承自 BaseClass
{
public:
	Obstacle();//默认构造函数，用于初始化 Obstacle 对象。

	virtual void Show(); 
	//重写基类的虚函数，用于在游戏界面上显示障碍物的形象。

	void ChangeObstacle(); 
	//改变障碍物的状态或属性
};


#endif // !OBSTACLE_H


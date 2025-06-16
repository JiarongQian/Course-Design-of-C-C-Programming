#ifndef SNAKE_H
#define SNAKE_H

#include "BaseClass.h"

class Snake : public BaseClass
	//定义 Snake 类，继承自 BaseClass

{
public:
	Snake(); //构造函数

	void SetSnakeLen(int n);
	//用于设置蛇的长度

	virtual void Show();
	//重写基类的虚函数，用于在游戏界面上显示蛇的形象。

	void DirectionMove(); 
	//根据当前方向更新蛇头的位置

	void BodyMove(); 
	//用于实现蛇身体的移动逻辑，更新蛇身体的每个节点位置

	void AddSnake();
	//增加蛇的长度（例如吃到食物后增加长度）
	
	void AddSpeed(int add_value);
	//用于增加蛇的移动速度

public://定义公有成员变量
	char m_direction; //用于存储蛇当前的移动方向
	int m_speed;    //用于存储蛇当前的移动速度
	int m_snake_len; //用于记录蛇的当前长度。
	std::vector<BaseClass> m_nodes;
	//用于存储蛇身体的各个节点（每个节点都是BaseClass类型，包含m_x,m_y坐标）
};

#endif // !SNAKE_H


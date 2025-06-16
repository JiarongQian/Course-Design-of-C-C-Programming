#include "Obstacle.h"

Obstacle::Obstacle() :BaseClass(0, 0) //构造函数，显式调用基类BaseClass的默认构造函数BaseClass(0,0)
//使障碍物随机分布在地图内，且坐标为 10 的倍数（适配网格碰撞检测）
{
	m_x = (1 + rand() % 50) * 10 + 10;
	m_y = (1 + rand() % 40) * 10 + 10;
}


void Obstacle::ChangeObstacle() //改变障碍物的位置
//重新生成障碍物的随机位置，用于动态刷新

{
	m_x = (1 + rand() % 50) * 10 + 10;
	m_y = (1 + rand() % 40) * 10 + 10;
}

 
void Obstacle::Show() //Show 成员函数
{
	setfillcolor(BLACK);//黑色
	fillrectangle(m_x, m_y, m_x + 10, m_y - 10);
}



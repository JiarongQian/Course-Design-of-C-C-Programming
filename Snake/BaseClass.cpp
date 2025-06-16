#include "BaseClass.h"
#include "FileInclude.h"

BaseClass::BaseClass() // 默认构造函数
{
	m_x = 50;
	m_y = 50;
}


BaseClass::BaseClass(int x, int y)
//带参数的构造函数，接受 x 和 y 坐标值，用于初始化对象的位置坐标
{
	m_x = x;
	m_y = y;
}


void BaseClass::Show() 
//Show 成员函数
{
	setlinecolor(BLACK); //设置绘制图形的线条颜色为黑色
	setfillcolor(RGB(255, 128, 0)); //设置填充颜色为橙色
	fillcircle(m_x, m_y, 5); //在坐标 (m_x, m_y) 处绘制一个半径为 5 的填充圆形
}


void BaseClass::Move(int x, int y)
//Move 成员函数，接受偏移量（x,y），更新对象坐标
{
	m_x = m_x + x;
	m_y = m_y + y;
}

//为对象的初始化、显示和移动提供具体的逻辑。
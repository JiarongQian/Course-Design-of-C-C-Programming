#include "Item.h"
#include "Game.h"

Item::Item():BaseClass(0,0) //构造函数，通过BaseClss（0，0）显示调用基类构造函数
//使道具随机分布在游戏地图内，且坐标为 10 的倍数（适配网格地图）
{
	m_x = (1 + rand() % 50) * 10 + 10; // x 坐标在 [20, 510] 范围内随机生成
	m_y = (1 + rand() % 40) * 10 + 10; //y 坐标在 [20, 410] 范围内随机生成
}


void Item::Change()// Change 成员函数
//重新生成道具的随机位置，用于道具被吃掉后刷新，当蛇吃到道具时，调用此函数在新位置生成道具
{
	m_x = (1 + rand() % 50) * 10 + 10;
	m_y = (1 + rand() % 40) * 10 + 10;
}


void Item::Show() //在屏幕上显示 Item 对象
//重写基类BaseClass::Show()方法，根据道具类型绘制不同颜色

{
	if (m_item_type == ITEM_DRUGS)//药品->红色
	{
		setfillcolor(RGB(255, 0, 0));
		fillcircle(m_x, m_y, 5);
	}
	else if(m_item_type == ITEM_COIN) //金币->金色
	{
		setfillcolor(RGB(255, 215, 0));
		fillcircle(m_x, m_y, 5);
	}
	else if (m_item_type == ITEM_DOUBLE_COIN)//双倍金币->橙色
	{
		setfillcolor(RGB(255, 200, 0));
		fillcircle(m_x, m_y, 5);
	}
}
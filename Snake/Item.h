#ifndef ITEM_H
#define ITEM_H

#include "BaseClass.h"

class Item : public BaseClass 
	//定义 Item 类，继承自 BaseClass
{
public:
	Item();//默认构造函数
	void Change();//用于改变 Item 对象的状态或属性
	void Show(); //在屏幕上显示 Item 对象

	void SetItemType(int type) { m_item_type = type; }
	//设置 Item 对象的类型

	int GetItemType() { return m_item_type; }
	//获取 Item 对象的类型，用于条件判断等

public:
	int m_item_type;
	//用于表示 Item 对象的类型
};

#endif // !ITEM_H


#ifndef  BASE_CLASS_H
#define  BASE_CLASS_H
  
#include "FileInclude.h"

//创建和管理具有位置坐标的对象

class BaseClass //定义类 作为其他类的基类
{
public:
	BaseClass();//默认构造函数
	BaseClass(int x, int y);//带参数的构造函数，接受x和y坐标值，用于初始化对象的位置坐标

	virtual void Show(); //虚函数，允许派生类重写此函数以实现自定义的显示逻辑
	void Move(int x, int y); //移动函数，接受x和y坐标值，用于移动对象到新的位置

public://两个公有的整型成员变量，用于存储对象的坐标位置
	int m_x;
	int m_y;
};

#endif // !BASE_CLASS_H

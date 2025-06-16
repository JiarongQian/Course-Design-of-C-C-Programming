#include "Snake.h"

Snake::Snake() //构造函数 Snake::Snake() 初始化

{
	m_direction = 'd'; //初始方向向右

	//创建蛇的初始身体节点，这里初始长度为 3 个节点，
	m_nodes.push_back((BaseClass(200, 50)));  //第一个节点位置为 (200, 50)
	m_nodes.push_back((BaseClass(190, 50)));  //第二个节点位置为 (190, 50)
	m_nodes.push_back((BaseClass(180, 50)));  //第三个节点位置为 (180, 50)
	m_snake_len = 3; //设置蛇的初始长度为 3
	m_speed = 50; //设置蛇的初始移动速度为 50。
}




void Snake::Show() //Show 函数 绘制蛇的所有节点
//遍历蛇的所有节点，调用每个节点的 Show 函数，将蛇的各个节点显示在游戏界面上。
//每个节点都是BaseClass类型
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i].Show();
	}
}

void Snake::DirectionMove() //DirectionMove 函数 处理方向输入
//使用GetAsyncKeyState检测键盘输入，更新蛇的移动方向。
{
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('w') || GetAsyncKeyState('W'))
	{
		if (m_direction != 's' && m_direction != 'S' && m_direction != 80)
		{
			m_direction = 'w';
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('s') || GetAsyncKeyState('S'))
	{
		if (m_direction != 'w' && m_direction != 'W' && m_direction != 72)
		{
			m_direction = 's';
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('a') || GetAsyncKeyState('A'))
	{
		if (m_direction != 'd' && m_direction != 'D' && m_direction != 77)
		{
			m_direction = 'a';
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('d') || GetAsyncKeyState('D'))
	{
		if (m_direction != 'a' && m_direction != 'A' && m_direction != 75)
		{
			m_direction = 'd';
		}
	}
}


void Snake::BodyMove() //移动函数 蛇身移动逻辑
{
	if (m_nodes.empty())
	{
		return;
	}

	//身体节点虽头部移动
	for (int i = (int)m_nodes.size() - 1; i > 0; i--)
	{
		m_nodes[i] = m_nodes[i - 1];
	}

	DirectionMove();//更新方向

	//根据当前方向移动蛇头节点
	if (m_direction == 'w')
	{
		m_nodes[0].Move(0, -10);
	}
	else if (m_direction == 's')
	{
		m_nodes[0].Move(0, 10);
	}
	else if (m_direction == 'a')
	{
		m_nodes[0].Move(-10, 0);
	}
	else if (m_direction == 'd')
	{
		m_nodes[0].Move(10, 0);
	}
}


void Snake::AddSnake() 
//蛇吃到食物后生长
{
	m_nodes.push_back((BaseClass()));//在蛇尾添加一个新的节点
	m_snake_len++;
}


void Snake::SetSnakeLen(int n)
//设置蛇的长度函数
{
	m_snake_len = n;
	if (n >= 3)
	{
		m_nodes.push_back((BaseClass()));
	}
	else
	{
		for (int i = 0; i < 3 - n; i++)
		{
			m_nodes.pop_back();
		}
	}
}


void Snake::AddSpeed(int add_value)
//速度控制函数
{
	if (m_speed < 150) // 限制速度上限为 150
	{
		m_speed += add_value;
		m_speed = m_speed < 150 ? m_speed : 150; //确保速度不超过 150
	}
}


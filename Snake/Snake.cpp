#include "Snake.h"

Snake::Snake() //���캯�� Snake::Snake() ��ʼ��

{
	m_direction = 'd'; //��ʼ��������

	//�����ߵĳ�ʼ����ڵ㣬�����ʼ����Ϊ 3 ���ڵ㣬
	m_nodes.push_back((BaseClass(200, 50)));  //��һ���ڵ�λ��Ϊ (200, 50)
	m_nodes.push_back((BaseClass(190, 50)));  //�ڶ����ڵ�λ��Ϊ (190, 50)
	m_nodes.push_back((BaseClass(180, 50)));  //�������ڵ�λ��Ϊ (180, 50)
	m_snake_len = 3; //�����ߵĳ�ʼ����Ϊ 3
	m_speed = 50; //�����ߵĳ�ʼ�ƶ��ٶ�Ϊ 50��
}




void Snake::Show() //Show ���� �����ߵ����нڵ�
//�����ߵ����нڵ㣬����ÿ���ڵ�� Show ���������ߵĸ����ڵ���ʾ����Ϸ�����ϡ�
//ÿ���ڵ㶼��BaseClass����
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i].Show();
	}
}

void Snake::DirectionMove() //DirectionMove ���� ����������
//ʹ��GetAsyncKeyState���������룬�����ߵ��ƶ�����
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


void Snake::BodyMove() //�ƶ����� �����ƶ��߼�
{
	if (m_nodes.empty())
	{
		return;
	}

	//����ڵ���ͷ���ƶ�
	for (int i = (int)m_nodes.size() - 1; i > 0; i--)
	{
		m_nodes[i] = m_nodes[i - 1];
	}

	DirectionMove();//���·���

	//���ݵ�ǰ�����ƶ���ͷ�ڵ�
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
//�߳Ե�ʳ�������
{
	m_nodes.push_back((BaseClass()));//����β���һ���µĽڵ�
	m_snake_len++;
}


void Snake::SetSnakeLen(int n)
//�����ߵĳ��Ⱥ���
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
//�ٶȿ��ƺ���
{
	if (m_speed < 150) // �����ٶ�����Ϊ 150
	{
		m_speed += add_value;
		m_speed = m_speed < 150 ? m_speed : 150; //ȷ���ٶȲ����� 150
	}
}


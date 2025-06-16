#include "Game.h"

//���캯��
Game::Game() //���캯�� Game::Game()  ���캯�������ڳ�ʼ�� Game ����
{
	m_item_flag = 0; //���߱�־λ m_item_flag ��ʼ��Ϊ 0
	m_init_item_num = 5; //��ʼ��������
	m_item_list.clear(); //��մ洢���ߵ�����

	m_obstacle_flag = 0; //�ϰ����־λ m_obstacle_flag ��ʼ��Ϊ 0
	m_init_obstacle_num = 3; //��ʼ�ϰ�������
	m_obstacle_list.clear(); //��մ洢�ϰ��������

	m_mark = 0; //��Ϸ�÷� m_mark ��ʼ��Ϊ 0
	m_game_begin_time = 0; //��Ϸ��ʼ��ʱ�� m_game_begin_time ��ʼ��Ϊ 0

	m_rank_list.clear(); //��մ洢���а������
	ReadRankInfo(); //��ȡ���а���Ϣ
}

//���������������� Game ��������ʱ������Դ����
Game::~Game() //�������� Game::~Game()
{

}

//��ʼ����Ϸ�˵���
void Game::InitMenu() //��ʼ���β˵�ҳ��
{
	cleardevice(); //�����ǰ��ͼ�豸�ϵ���������

	IMAGE img; //���ڴ洢���ص�ͼ��
	loadimage(&img, L"./background_image.jpg", 1000, 600); //�ӵ�ǰĿ¼�¼�����Ϊ background_image.jpg ��ͼƬ������������Ϊ 1000x600 �ĳߴ磬�洢�� img �С�
	putimage(0, 0, &img); //�����ص�ͼƬ��ʾ�ڻ�ͼ�豸�����Ͻ�
	setbkmode(TRANSPARENT);//�����ı��ı���ģʽΪ͸��

	setfillcolor(BROWN); //���������ɫΪ��ɫ
	fillroundrect(280, 300, 280 + 200, 300 + 80, 10, 10); //����һ��Բ�Ǿ�����Ϊ��ť
	settextstyle(30, 0, L"����");//�����ı���������ʽ
	int width = textwidth(L"��ʼ��Ϸ");
	int high = textheight(L"��ʼ��Ϸ");
	outtextxy(280 + (200 - width) / 2, 300 + (80 - high) / 2, L"��ʼ��Ϸ");

	fillroundrect(500, 300, 500 + 200, 300 + 80, 10, 10);
	settextstyle(30, 0, L"����");
	width = textwidth(L"�ָ��浵");
	high = textheight(L"�ָ��浵");
	outtextxy(500 + (200 - width) / 2, 300 + (80 - high) / 2, L"�ָ��浵");

	fillroundrect(280, 400, 280 + 200, 400 + 80, 10, 10);
	settextstyle(30, 0, L"����");
	width = textwidth(L"��Ϸ����");
	high = textheight(L"��Ϸ����");
	outtextxy(280 + (200 - width) / 2, 400 + (80 - high) / 2, L"��Ϸ����");

	fillroundrect(500, 400, 500 + 200, 400 + 80, 10, 10);
	settextstyle(30, 0, L"����");
	width = textwidth(L"��Ϸ����");
	high = textheight(L"��Ϸ����");
	outtextxy(500 + (200 - width) / 2, 400 + (80 - high) / 2, L"��Ϸ����");

	fillroundrect(280, 500, 280 + 200, 500 + 80, 10, 10);
	settextstyle(30, 0, L"����");
	width = textwidth(L"���а�");
	high = textheight(L"���а�");
	outtextxy(280 + (200 - width) / 2, 500 + (80 - high) / 2, L"���а�");
}

//��ʼ����Ϸ��ͼ��
void Game::InitGameMap() //������Ϸ��ͼ�߿�
{
	for (int i = 0; i < 600; i++)
	{
		setlinecolor(BLACK);
		fillrectangle(i, 15, i + 1, 0);
	}
	for (int i = 0; i < 500; i++)
	{
		setlinecolor(BLACK);
		fillrectangle(0, 15 + i, 15, 15 + i);
	}
	for (int i = 0; i < 500; i++)
	{
		setlinecolor(BLACK);
		fillrectangle(585, 15 + i, 600, 15 + i);
	}
	for (int i = 0; i < 600; i++)
	{
		setlinecolor(BLACK);
		fillrectangle(i, 515, i + 1, 500);
	}

	IMAGE img;// ���ز���ʾͼƬ
	loadimage(&img, L"./snake.jpg", 400, 380);
	putimage(610, 0, &img);

	settextstyle(20, 15, _T("����")); //��ʾ��Ϸ�÷���Ϣ
	wchar_t A[] = L"������Ϸ��ǰ�÷�Ϊ��";
	settextcolor(BLACK);
	outtextxy(620, 400, A);

	TCHAR s[5];
	_stprintf_s(s, _T("%d"), m_mark);
	settextcolor(MAGENTA);
	outtextxy(910, 400, s);

	wchar_t C[] = L"�������ƶ��ٶ�Ϊ��   ��"; //��ʾ��Ϸ�ٶ���Ϣ
	settextcolor(BLACK);
	outtextxy(620, 490, C);

	_stprintf_s(s, _T("%d"), (150 - m_snake.m_speed) / 50); // ��ʾ��Ϸʱ����Ϣ
	settextcolor(RED);
	outtextxy(900, 490, s);

	wchar_t T[] = L"��Ϸʱ���ѹ�ȥ��  ��  ��";
	settextcolor(BLACK);
	outtextxy(620, 540, T);
	int time_now = (int)std::time(nullptr);
	int minute = (time_now - m_game_begin_time) / 60;
	int second = (time_now - m_game_begin_time) % 60;
	_stprintf_s(s, _T("%d"), minute);
	settextcolor(MAGENTA);
	outtextxy(860, 540, s);
	_stprintf_s(s, _T("%d"), second);
	settextcolor(MAGENTA);
	outtextxy(920, 540, s);

	/*setfillcolor(BROWN);
	fillroundrect(10, 520, 60, 570, 60, 60);
	settextstyle(15, 0, L"����");
	settextcolor(BLACK);
	if (m_is_stop)
	{
		int width = textwidth(L"����");
		int high = textheight(L"����");
		outtextxy(10 + (50 - width) / 2, 520 + (50 - high) / 2, L"����");
	}
	else
	{
		int width = textwidth(L"��ͣ");
		int high = textheight(L"��ͣ");
		outtextxy(10 + (50 - width) / 2, 520 + (50 - high) / 2, L"��ͣ");
	}

	fillroundrect(80, 520, 140, 570, 60, 60);
	settextstyle(15, 0, L"����");
	settextcolor(BLACK);
	int width = textwidth(L"����");
	int high = textheight(L"����");
	outtextxy(80 + (50 - width) / 2, 520 + (50 - high) / 2, L"����");*/

}

//������Ϸ�������õĳ�ʼ����
void Game::InitSet()
{
	IMAGE img; //���ز���ʾͼƬ
	cleardevice();
	loadimage(&img, L"./background_set.jpg", 1000, 600);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);

	//�����ߵĳ�ʼ�����������
	setfillcolor(LIGHTBLUE); //���������ɫΪǳ��ɫ
	fillroundrect(400, 100, 400 + 200, 100 + 50, 10, 10);//����һ��Բ�Ǿ�����Ϊ��ť
	settextstyle(15, 0, L"����");//�����ı���������ʽ
	settextcolor(BLACK);//�����ı���ɫΪ��ɫ
	int width = textwidth(L"�ߵĳ�ʼ����Ϊ��");
	int high = textheight(L"�ߵĳ�ʼ����Ϊ��");
	outtextxy(400 + (200 - width) / 2, 100 + (50 - high) / 2, L"�ߵĳ�ʼ����Ϊ��");
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), m_snake.m_snake_len);
	outtextxy(400 + (200 - width) / 2 + width, 100 + (50 - high) / 2, s);

	setfillcolor(BROWN);
	fillcircle(350, 125, 20);
	outtextxy(350, 120, L"һ");

	setfillcolor(BROWN);
	fillcircle(650, 125, 20);
	outtextxy(650, 120, L"ʮ");

	////���õ��ߵĳ�ʼ�����������
	setbkmode(TRANSPARENT); 
	setfillcolor(LIGHTBLUE);
	fillroundrect(400, 180, 400 + 200, 180 + 50, 10, 10);
	settextstyle(15, 0, L"����");
	settextcolor(BLACK);
	width = textwidth(L"���ߵĳ�ʼ����Ϊ��");
	high = textheight(L"���ߵĳ�ʼ����Ϊ��");
	outtextxy(400 + (200 - width) / 2, 180 + (50 - high) / 2, L"���ߵĳ�ʼ����Ϊ��");
	_stprintf_s(s, _T("%d"), m_init_item_num);
	outtextxy(400 + (200 - width) / 2 + width, 180 + (50 - high) / 2, s);

	setfillcolor(BROWN);
	fillcircle(350, 205, 20);
	outtextxy(340, 195, L"һ");

	setfillcolor(BROWN);
	fillcircle(650, 205, 20);
	outtextxy(642, 195, L"ʮ");

	//�����ϰ���ĳ�ʼ�����������
	setbkmode(TRANSPARENT);
	setfillcolor(LIGHTBLUE);
	fillroundrect(400, 260, 400 + 200, 260 + 50, 10, 10);
	settextstyle(15, 0, L"����");
	settextcolor(BLACK);
	width = textwidth(L"�ϰ���ĳ�ʼ����Ϊ��");
	high = textheight(L"�ϰ���ĳ�ʼ����Ϊ��");
	outtextxy(400 + (200 - width) / 2, 260 + (50 - high) / 2, L"�ϰ���ĳ�ʼ����Ϊ��");
	_stprintf_s(s, _T("%d"), m_init_obstacle_num);
	outtextxy(400 + (200 - width) / 2 + width, 260 + (50 - high) / 2, s);

	setfillcolor(BROWN);
	fillcircle(350, 285, 20);
	outtextxy(340, 275, L"һ");

	setfillcolor(BROWN);
	fillcircle(650, 285, 20);
	outtextxy(642, 275, L"ʮ");

	//���÷��ذ�ť
	setbkmode(TRANSPARENT);
	setfillcolor(BROWN);
	fillroundrect(0, 0, 50, 50, 50, 50);
	settextstyle(15, 0, L"����");
	width = textwidth(L"����");
	high = textheight(L"����");
	outtextxy(0 + (50 - width) / 2, 0 + (50 - high) / 2, L"����");
}

//�����ѡ����Ϸģʽ������һ������ֵ��ʾѡ������
bool Game::SelectGame()
{
	EndBatchDraw();//����������ͼ
	cleardevice();//�����ǰ��ͼ�豸�ϵ���������
	InitMenu();//��ʼ����Ϸ�˵�

	ExMessage msg;//����һ�� ExMessage ���͵ı��� msg�����ڴ洢����¼���Ϣ
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)//����������������Ϣ
			{
			case WM_LBUTTONDOWN://���������λ��ִ�в�ͬ����
			{
				//���������ڡ���Ϸ��������ť����
				if (msg.x >= 280 && msg.x <= 280 + 200 && msg.y >= 400 && msg.y <= 400 + 80)
				{
					ShowHelp();//��ʾ��Ϸ������Ϣ
				}

				//���������ڡ���Ϸ���á���ť����
				if (msg.x >= 500 && msg.x <= 500 + 200 && msg.y >= 400 && msg.y <= 400 + 80)
				{
					InitSet();
					InitGameData();//��ʼ����Ϸ���ݣ��ߵĳ��ȵȵȣ���
				}

				//���������ڡ����а񡱰�ť����
				if (msg.x >= 280 && msg.x <= 280 + 200 && msg.y >= 500 && msg.y <= 500 + 80)
				{
					InitRank();//��ʼ�����а�

				}

				//���������ڡ��ָ��浵����ť����
				if (msg.x >= 500 && msg.x <= 500 + 200 && msg.y >= 300 && msg.y <= 300 + 80)
				{
					m_item_flag = 0;
					m_init_item_num = 3;
					m_item_list.clear();
					m_obstacle_flag = 0;
					m_init_obstacle_num = 3;
					m_obstacle_list.clear();
					m_snake.m_nodes.clear();
					m_snake.m_snake_len = 3;
					m_mark = 0;
					m_game_begin_time = 0;
					m_is_stop = false;
				
					ReadGameInfo();//��ȡ��Ϸ��״̬��Ϣ
					return true;
				}

				//���������ڡ���ʼ��Ϸ����ť����
				if (msg.x >= 280 && msg.x <= 280 + 200 && msg.y >= 300 && msg.y <= 300 + 80)
				{
					return true;
				}

				break;
			}
			default:
				break;
			}
		}
	}
}

//��ʼ����Ϸ���ݣ��ߵĳ��ȵȵȣ���
void Game::InitGameData() //��ʼ����Ϸ����
{
	int flag_food = 0;
	int flag_obstacle = 0;
	//���ڱ������Ƿ�λ��ʳ����ϰ�����ص����򣬳�ʼֵ����Ϊ 0��

	while (1)//����һ������ѭ�������ڳ������������Ϣ��������Ӧ�Ĵ���
	{
		ExMessage tmp; //��ʼ����ͼ�ͽ���
		ExMessage t;
		BeginBatchDraw();
		InitSet();

		if (peekmessage(&tmp, EM_MOUSE)) //���������Ϣ
		{
			switch (tmp.message)
			{
			case WM_LBUTTONDOWN:
				//��������λ���Ƿ��� �����ء� ��ť��Χ��
				if (tmp.x >= 0 && tmp.x <= 50 && tmp.y >= 0 && tmp.y <= 50)
				{
					SelectGame();//�����ѡ����Ϸģʽ������һ������ֵ��ʾѡ������
					return;
				}
	
				//�ֱ��������λ���Ƿ����߳��ȡ�ʳ���������ϰ���������������ť��Χ�ڣ���������Ӧ�������ߵĳ��ȡ�ʳ��ĳ�ʼ�������ϰ���ĳ�ʼ������������������
				if (tmp.x >= 330 && tmp.x <= 370 && tmp.y >= 105 && tmp.y <= 145)
				{
					if (m_snake.m_snake_len > 1)
					{
						int n = m_snake.m_snake_len - 1; //����-1
						m_snake.SetSnakeLen(n);
					}
				}

				
				if (tmp.x >= 630 && tmp.x <= 670 && tmp.y >= 105 && tmp.y <= 145)
				{
					int n = m_snake.m_snake_len + 1; // ����+1
					m_snake.SetSnakeLen(n);
				}

				if (tmp.x >= 330 && tmp.x <= 370 && tmp.y >= 180 && tmp.y <= 225)
				{
					if (m_init_item_num > 1)
					{
						int n = m_init_item_num - 1; //����-1
						SetInitItemNum(n);
					}
				}

				if (tmp.x >= 630 && tmp.x <= 670 && tmp.y >= 180 && tmp.y <= 225)
				{
					if (m_init_item_num < 15)
					{
						int n = m_init_item_num + 1; //����+1
						SetInitItemNum(n);
					}
				}

				if (tmp.x >= 330 && tmp.x <= 370 && tmp.y >= 265 && tmp.y <= 305)
				{
					if (m_init_obstacle_num > 1)
					{
						int n = m_init_obstacle_num - 1; //�ϰ���-1
						SetInitObstacle(n);
					}
				}

				if (tmp.x >= 630 && tmp.x <= 670 && tmp.y >= 265 && tmp.y <= 305)
				{
					if (m_init_obstacle_num < 15)
					{
						int n = m_init_obstacle_num + 1; //�ϰ���+1
						SetInitObstacle(n);
					}
				}
			}
		}

		if (peekmessage(&t, EM_MOUSE))
		{
			switch (t.message)
			{
			case WM_MOUSEMOVE:
				if (t.x >= 400 && t.x <= 600 && t.y >= 180 && t.y <= 230)
				{
					flag_food = 1; //��ʾ����ڵ���������������
				}
				else
				{
					flag_food = 0; //��ʾ��겻�ڵ���������������
				}

				if (t.x >= 400 && t.x <= 600 && t.y >= 260 && t.y <= 310)
				{
					flag_obstacle = 1; //��ʾ������ϰ���������������
				}
				else
				{
					flag_obstacle = 0; //��ʾ��겻���ϰ���������������
				}
			}
		}

		if (flag_food == 1) // �������ڵ���������������  ��ʾ���������������ʾ��Ϣ
		{
			setbkmode(TRANSPARENT);
			setfillcolor(YELLOW);
			fillroundrect(t.x, t.y, t.x + 200, t.y + 50, 10, 10);
			settextstyle(15, 0, L"����");
			settextcolor(BLACK);
			int width = textwidth(L"���ߵ��������Ϊ��");
			int high = textheight(L"���ߵ��������Ϊ��");
			outtextxy(t.x + (200 - width) / 2, t.y + (50 - high) / 2, L"���ߵ��������Ϊ��");
			TCHAR s[5];
			_stprintf_s(s, _T("%d"), MAX_ITEM_NUM);
			outtextxy(t.x + (200 - width) / 2 + width, t.y + (50 - high) / 2, s);
		}

		if (flag_obstacle == 1) //���������ϰ���������������  ��ʾ�ϰ��������������ʾ��Ϣ
		{
			setbkmode(TRANSPARENT);
			setfillcolor(YELLOW);
			fillroundrect(t.x, t.y, t.x + 200, t.y + 50, 10, 10);
			settextstyle(15, 0, L"����");
			settextcolor(BLACK);
			int width = textwidth(L"�ϰ�����������Ϊ��");
			int high = textheight(L"�ϰ�����������Ϊ��");
			outtextxy(t.x + (200 - width) / 2, t.y + (50 - high) / 2, L"�ϰ�����������Ϊ��");
			TCHAR s[5];
			_stprintf_s(s, _T("%d"), MAX_ITEM_NUM);
			outtextxy(t.x + (200 - width) / 2 + width, t.y + (50 - high) / 2, s);
		}

		EndBatchDraw();
	}
}

//��ʼ�����а���ʾ���а�
void Game::InitRank() //��ʼ�����а�
{
	//ͼ�ν����ʼ��
	IMAGE img;
	cleardevice();
	loadimage(&img, L"./background_set.jpg", 1000, 600);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, L"����");
	settextcolor(BLACK);
	//��ָ��������Ʊ�ͷ
	outtextxy(200, 100, L"����");
	outtextxy(400, 100, L"���id");
	outtextxy(600, 100, L"����");
	
	//�������� ʹ�� C++���е�std::sort����ʵ�ְ���������
	std::sort(m_rank_list.begin(), m_rank_list.end());
	//m_rank_list��һ���洢rank�ṹ�������
	//std::sortĬ��ʹ��Ԫ�����͵�<��������бȽ�
	//rank�ṹ����ͷ�ļ�Game.h��������<�������ʹ�䰴������������

	TCHAR tmp[128];
	for (int i = 0; i < (int)m_rank_list.size(); ++i)
	{
		_stprintf_s(tmp, 128, _T("%d"), i + 1);
		outtextxy(200, 100 + (i + 1) * 50, tmp);

		_stprintf_s(tmp, 128, _T("���%d"), m_rank_list[i].id);
		outtextxy(400, 100 + (i + 1) * 50, tmp);

		_stprintf_s(tmp, 128, _T("%d"), m_rank_list[i].score);
		outtextxy(600, 100 + (i + 1) * 50, tmp);
	}

	//���÷��ذ�ť
	setbkmode(TRANSPARENT);
	setfillcolor(BROWN);
	fillroundrect(0, 0, 50, 50, 50, 50);
	settextstyle(15, 0, L"����");
	int width = textwidth(L"����");
	int high = textheight(L"����");
	outtextxy(0 + (50 - width) / 2, 0 + (50 - high) / 2, L"����");
	while (1)
	{
		ExMessage tmp;
		if (peekmessage(&tmp, EM_MOUSE))
		{
			switch (tmp.message)
			{
			case WM_LBUTTONDOWN:
				if (tmp.x >= 0 && tmp.x <= 50 && tmp.y >= 0 && tmp.y <= 50)
				{
					InitMenu();//��ʼ����Ϸ�˵���

					return;
				}
			}
		}
	}
}

//��ʾ��Ϸ������Ϣ
void Game::ShowHelp()
{
	IMAGE img;
	cleardevice();
	loadimage(&img, L"./background_help.png", 1000, 600);
	putimage(0, 0, &img);
	settextstyle(20, 0, L"����");
	settextcolor(BLACK);
	outtextxy(200, 70, L"---����Ϸ�ļ��̲ٿع���---");
	outtextxy(110, 90, L"w or W or �� Ϊ�����ƶ�");
	outtextxy(110, 110, L"a or A or �� Ϊ�����ƶ�");
	outtextxy(110, 130, L"s or S or �� Ϊ�����ƶ�");
	outtextxy(110, 150, L"d or D or �� Ϊ�����ƶ�");
	outtextxy(110, 170, L"q or Q or �� ��ͣ��Ϸ");
	outtextxy(110, 190, L"e or E or �� ������Ϸ");
	outtextxy(200, 240, L"---����Ϸ����������---");
	outtextxy(110, 270, L"�������߳����˱߽緶Χ������ͷ�����Լ���������������ϰ��� ��Ϸ�ͻ����");
	outtextxy(110, 300, L"�ϰ����ʼ��3�� �ߵĳ�������Ϊ��ı����Ͷ�һ���ϰ��� ���30��");
	outtextxy(110, 330, L"ʳ���ʼ��3�� �ߵĳ���ÿ�������ھͶ�һ��ʳ�� ���30��");
	
	//���÷��ذ�ť
	setbkmode(TRANSPARENT);
	setfillcolor(BROWN);
	fillroundrect(0, 0, 50, 50, 50, 50);
	settextstyle(15, 0, L"����");
	int width = textwidth(L"����");
	int high = textheight(L"����");
	outtextxy(0 + (50 - width) / 2, 0 + (50 - high) / 2, L"����");
	while (1)
	{
		ExMessage tmp;
		if (peekmessage(&tmp, EM_MOUSE))
		{
			switch (tmp.message)
			{
			case WM_LBUTTONDOWN:
				if (tmp.x >= 0 && tmp.x <= 50 && tmp.y >= 0 && tmp.y <= 50)
				{
					InitMenu();//��ʼ����Ϸ�˵���
					return;
				}
			}
		}
	}
}

//������Ϸ �����ʼ����Ϸ������������ϷԪ�أ���������ѭ��
void Game::Start()
{
	system("cls"); //�������̨��Ļ
	system("color 9E");//���ÿ���̨����ɫΪ��ɫ��ǰ��ɫΪ��ɫ

	//��ʼ��ͼ�δ���
	initgraph(1000, 600);
	cleardevice(); //��ջ�ͼ����
	setbkcolor(WHITE); //���ñ���ɫΪ��ɫ

	//ʹ��mciSendString API���ű�������
	//open����������ļ�
	//play...repeat��������ֲ�����Ϊѭ������
	mciSendString(L"open ./background_music.mp3", NULL, 0, NULL);
	mciSendString(L"play ./background_music.mp3 repeat", NULL, 0, NULL);

	//ѡ����Ϸģʽ
	if (SelectGame())//�����ѡ����Ϸģʽ������һ������ֵ��ʾѡ������
	{
		cleardevice();
	    
		//���ɳ�ʼ��Ϸ����
		for (int i = 0; i < m_init_item_num; ++i)
		{
			Item item;
			int randnum = rand() % 100; //�����������������
			if (randnum < 30) //0-29
			{
				item.SetItemType(ITEM_DOUBLE_COIN);
			}
			else if(randnum < 60) //30-59
			{
				item.SetItemType(ITEM_DRUGS);
			}
			else
			{
				item.SetItemType(ITEM_COIN); //60-99
			}

			m_item_list.push_back(item);
		}

		//�����ϰ���
		for (int i = 0; i < m_init_obstacle_num; ++i)
		{
			Obstacle obstacle;
			m_obstacle_list.push_back(obstacle);
		}

		//��¼��Ϸ��ʼʱ�䲢������Ϸ��ѭ��
		m_game_begin_time = (int)std::time(nullptr);
		while (1)
		{
			Run();
			Sleep(m_snake.m_speed);
		}
	}
}

//��Ϸ��ѭ�� ���������룬������Ϸ״̬����Ⱦ��Ϸ���档
void Game::Run()
{
	//�����������
	if (GetAsyncKeyState('q') || GetAsyncKeyState('Q'))
		//Q/q�л���Ϸ��ͣ״̬
	{
		m_is_stop = !m_is_stop;
	}

	if (GetAsyncKeyState('e') || GetAsyncKeyState('E'))
		//E/e��������Ϸ����
	{
		SaveGameInfo();//����Ϸ�ĵ�ǰ״̬��Ϣ���浽�ı��ļ���
	}

	//��ʼ������ͼ������
	BeginBatchDraw();
	cleardevice();
	InitGameMap(); //��ʼ����Ϸ��ͼ

	//��Ϸ�ж�̬������Ϸ����
	if ((int)m_item_list.size() < MAX_ITEM_NUM && m_item_flag == 3)
	{
		Item item;
		int randnum = rand() % 100;
		if (randnum < 50)//50%����������ͨ��ң�50%��������ҩƷ������û����������˫�����
		{
			item.SetItemType(ITEM_COIN);
		}
		else
		{
			item.SetItemType(ITEM_DRUGS);
		}

		m_item_list.push_back(item);
		m_item_flag = 0;
	}

	//��ʾ��Ϸ����
	for (int i = 0; i < (int)m_item_list.size() && i < MAX_ITEM_NUM; i++)
	{
		m_item_list[i].Show();
	}

	//��Ϸ�ж�̬�����ϰ���
	if ((int)m_obstacle_list.size() < MAX_OBSTACLE && m_obstacle_flag == 5)
	{
		Obstacle obstacle;
		m_obstacle_list.push_back(obstacle);
		m_obstacle_flag = 0;
	}

	//��ʾ�ϰ���
	for (int j = 0; j < (int)m_obstacle_list.size() && j < MAX_OBSTACLE; j++)
	{
		m_obstacle_list[j].Show();
	}

	//��ʾ��
	m_snake.Show(); //�����ߵ����нڵ�
	if (IsSnakeDie())//������Ƿ�����������ײ���Լ���߽磩��
	{
		GameOver();//������Ϸ�����߼�
	}

	//�ƶ���
	if (!m_is_stop) //δ��ͣ��Ϸʱ���߲Ż��ƶ�
	{
		m_snake.BodyMove();//�ߵ������ƶ�
	}
	
	//�����߳Ե��ߵ����
	EatItem();////������Ƿ�ٵ����ߣ�������Ч��
	EndBatchDraw();
}


//������Ƿ�Ե����ߣ�������Ч��
void Game::EatItem()
{
	//�������е���
	for (int i = 0; i < (int)m_item_list.size() && i < MAX_ITEM_NUM; i++)
	{  
		//�ж���ͷ�Ƿ�������ص�
		if (m_snake.m_nodes[0].m_x == m_item_list[i].m_x && m_snake.m_nodes[0].m_y == m_item_list[i].m_y)
		{  
			//���ųԵ��ߵ���Ч
			mciSendString(L"close ./eat_food_music.mp3", NULL, 0, NULL);
			mciSendString(L"open ./eat_food_music.mp3", NULL, 0, NULL);
			mciSendString(L"play ./eat_food_music.mp3", NULL, 0, NULL);
			
			//���ݵ������͸��·������ߵĳ���
			if (m_item_list[i].GetItemType() == ITEM_COIN)
			{
				m_mark++;
				m_snake.AddSnake();
			}
			else if (m_item_list[i].GetItemType() == ITEM_DOUBLE_COIN)
			{
				m_mark = m_mark + 2;
				m_snake.AddSnake();
			}
			else if (m_item_list[i].GetItemType() == ITEM_DRUGS)
			{
				m_snake.AddSpeed(5);
			}

			//���µ���λ�ò��޸ı�־λ
			m_item_list[i].Change();
			m_item_flag++;
			m_obstacle_flag++;

			return;
		}
	}
}

//������Ƿ�����������ײ���Լ���߽���ϰ��
bool Game::IsSnakeDie()
{
	//�߽���ײ���
	if (m_snake.m_nodes[0].m_x + 5 >= 590 || m_snake.m_nodes[0].m_x - 5 <= 10 
		|| m_snake.m_nodes[0].m_y + 5 >= 500 || m_snake.m_nodes[0].m_y - 5 <= 10)
	{
		return true;
	}

	//�ϰ�����ײ���
	for (int j = 0; j < (int)m_obstacle_list.size(); j++)//���������ϰ�������ͷ�Ƿ�������ײ
	{
		//���ĸ���������ͷԲ�����ϰ�����ε��ص�
		//��ͷ���� ��5���뾶�����ϰ����������Ƚ�

		//�����ͷ���ϰ�����Ҳ���ײ���
		if (m_snake.m_nodes[0].m_x + 5 >= m_obstacle_list[j].m_x // ��ͷ�Ҳ���ϰ������
			&& m_snake.m_nodes[0].m_x + 5 <= m_obstacle_list[j].m_x + 10//��ͷ�Ҳ���ϰ����Ҳ�
			&& m_snake.m_nodes[0].m_y >= m_obstacle_list[j].m_y - 10 // ��ͷ�������ϰ���ײ�
			&& m_snake.m_nodes[0].m_y <= m_obstacle_list[j].m_y)//��ͷ�������ϰ��ﶥ��
		{
			return true;
		}
	
		//�����ͷ���ϰ���������ײ���
		if (m_snake.m_nodes[0].m_x - 5 <= m_obstacle_list[j].m_x + 10 
			&& m_snake.m_nodes[0].m_x - 5 >= m_obstacle_list[j].m_x
			&& m_snake.m_nodes[0].m_y >= m_obstacle_list[j].m_y - 10 
			&& m_snake.m_nodes[0].m_y <= m_obstacle_list[j].m_y)
		{
			return true;
		}

		//�����ͷ���ϰ�����·���ײ���
		if (m_snake.m_nodes[0].m_y + 5 >= m_obstacle_list[j].m_y - 10 
			&& m_snake.m_nodes[0].m_y + 5 <= m_obstacle_list[j].m_y
			&& m_snake.m_nodes[0].m_x >= m_obstacle_list[j].m_x
			&& m_snake.m_nodes[0].m_x <= m_obstacle_list[j].m_x + 10)
		{
			return true;
		}

		//�����ͷ���ϰ�����Ϸ���ײ���
		if (m_snake.m_nodes[0].m_y - 5 <= m_obstacle_list[j].m_y 
			&& m_snake.m_nodes[0].m_y - 5 >= m_obstacle_list[j].m_y - 10
			&& m_snake.m_nodes[0].m_x >= m_obstacle_list[j].m_x 
			&& m_snake.m_nodes[0].m_x <= m_obstacle_list[j].m_x + 10)
		{
			return true;
		}
	}

	//��ͷ��������ײ��⣨����ײ��⣬�����ͷ�Ƿ������������ڵ������غϣ�
	//�ӵ�һ������ڵ㿪ʼ��飨i=1��������ͷ i=0�� ֱ�ӱȽ������Ƿ���ȫ��ͬ
	for (int i = 1; i < m_snake.m_nodes.size(); i++)
	{
		if (m_snake.m_nodes[0].m_x == m_snake.m_nodes[i].m_x && m_snake.m_nodes[0].m_y == m_snake.m_nodes[i].m_y)
		{
			return true;
		}
	}

	return false;
}

//������Ϸ�����߼�
//����������ʾ��������¼���û�����
void Game::GameOver()
{
	//����
	EndBatchDraw(); //����������ͼ
	mciSendString(L"stop ./background_music.mp3", NULL, 0, NULL);
	mciSendString(L"close ./game_fail_music.mp3 ", NULL, 0, NULL);
	mciSendString(L"open ./game_fail_music.mp3", NULL, 0, NULL);
	mciSendString(L"play ./game_fail_music.mp3 ", NULL, 0, NULL);

	//��Ϸ�����������
	Sleep(1500); //�ӳ�1.5s
	cleardevice();
	IMAGE img;
	cleardevice();
	loadimage(&img, L"./game_end_image.png", 1000, 600);
	putimage(0, 0, &img);
	settextcolor(RED);
	settextstyle(40, 0, L"��������");
	outtextxy(310, 250, L"---------��Ϸ����----------");
	settextcolor(BLACK);
	settextstyle(40, 0, L"����");
	outtextxy(300, 330, L"���ĵ÷�Ϊ��");
	TCHAR s[5];
	settextcolor(RED);
	_stprintf_s(s, _T("%d"), m_mark);
	outtextxy(550, 330, s);

	//������¼�����а����
	Rank rank;//�����µ� Rank �ṹ���¼��ǰ��Ϸ����
	rank.id = (int)m_rank_list.size() + 1;//���а���Ŀ���
	rank.score = m_mark; //��Ϸ�÷�
	rank.game_time = (int)std::time(nullptr) - m_game_begin_time;//��Ϸʱ��
	rank.game_time = rank.game_time < 0 ? 9999 : rank.game_time; //��ֹʱ��Ϊ��������Ϊ9999
	m_rank_list.push_back(rank); //����ǰ��Ϸ������ӵ����а��б���
	SaveRankInfo();//�����а���Ϣ���浽�ļ�


	//�û���������Ϸ����
	HWND hwnd = GetHWnd();
	while (1)
		//ѭ��������������
	{
		ExMessage tmp;
		peekmessage(&tmp, EM_MOUSE);
		if (tmp.message == WM_LBUTTONDOWN)
		{
			if (tmp.x >= 0 && tmp.y >= 0)
			{
				int isok = MessageBox(hwnd, L"���ź�����Ϸʧ�ܣ��������Ƿ���Ҫ���¿�ʼ", L"��ʾ", MB_YESNOCANCEL);
				if (isok == IDYES)//ѡ���ǡ�
				{
					srand((unsigned int)time(nullptr)); //�������������
					closegraph(); //�رյ�ǰͼ�δ���
					Game b; //�����µ� Game ���� b����ʼ������
					b.m_mark = 0;
					b.m_init_item_num = 3;
					b.m_snake.m_snake_len = 3;
					b.m_init_obstacle_num = 3;
					b.m_game_begin_time = 0;
					b.m_is_stop = false;
					b.Start();//���� Start() ������ʼ����Ϸ
				}
				else if (isok == IDNO)//ѡ�񡰷�
				{
					exit(0);
				}
			}
		}
	}
}

//����Ϸ�ĵ�ǰ״̬��Ϣ���浽�ı��ļ���
void Game::SaveGameInfo()
{  
	//������Ϸ�Ļ�����Ϣ���ļ�
	std::ofstream base_file("game_base_info.txt");
	if (base_file.is_open())
	{
		base_file << m_item_flag << " "
				  << m_init_item_num << " "
				  << m_obstacle_flag << " "
				  << m_init_obstacle_num << " "
				  << m_mark << " "
				  << m_game_begin_time << " "
				  << m_is_stop << " "
			      << m_snake.m_speed << " "
			      << m_snake.m_snake_len << std::endl;
		base_file.close();
	}

	//������Ϸ�ĵ�����Ϣ���ļ�
	std::ofstream item_file("game_item_info.txt");
	if (item_file.is_open())
	{
		for (int i = 0; i < (int)m_item_list.size(); ++i)
		{
			item_file << m_item_list[i].m_item_type << " "
					  << m_item_list[i].m_x << " "
					  << m_item_list[i].m_y << " " << std::endl;
		}

		item_file.close();
	}

	//������Ϸ���ϰ�����Ϣ���ļ�
	std::ofstream obstacle_file("game_obstacle_info.txt");
	if (obstacle_file.is_open())
	{
		for (int i = 0; i < (int)m_obstacle_list.size(); ++i)
		{
			obstacle_file << m_obstacle_list[i].m_x << " "
				<< m_obstacle_list[i].m_y << " " << std::endl;
		}

		obstacle_file.close();
	}

	//������Ϸ���ߵ���Ϣ���ļ�
	std::ofstream snake_file("game_snake_info.txt");
	if (snake_file.is_open())
	{
		for (int i = 0; i < (int)m_snake.m_nodes.size(); ++i)
		{
			snake_file << m_snake.m_nodes[i].m_x << " "
				<< m_snake.m_nodes[i].m_y << " " << std::endl;
		}

		snake_file.close();
	}
}

//��ȡ��Ϸ��״̬��Ϣ
void Game::ReadGameInfo()
{
	std::ifstream base_file("game_base_info.txt");
	if (base_file.is_open())
	{
		std::string line;
		while (std::getline(base_file, line))
		{
			std::istringstream stream(line);
			stream >> m_item_flag;
			stream >> m_init_item_num;
			stream >> m_obstacle_flag;
			stream >> m_init_obstacle_num;
			stream >> m_mark;
			stream >> m_game_begin_time;
			stream >> m_is_stop;
			stream >> m_snake.m_speed;
			stream >> m_snake.m_snake_len;
		}

		base_file.close();
	}

	std::ifstream item_file("game_item_info.txt");
	if (item_file.is_open())
	{
		std::string line;
		Item item;
		while (std::getline(item_file, line))
		{
			std::istringstream stream(line);
			stream >> item.m_item_type;
			stream >> item.m_x;
			stream >> item.m_y;
			m_item_list.push_back(item);
		}

		item_file.close();
	}

	std::ifstream obstacle_file("game_obstacle_info.txt");
	if (obstacle_file.is_open())
	{
		std::string line;
		Obstacle obstacle;
		while (std::getline(obstacle_file, line))
		{
			std::istringstream stream(line);
			stream >> obstacle.m_x;
			stream >> obstacle.m_y;
			m_obstacle_list.push_back(obstacle);
		}

		obstacle_file.close();
	}

	std::ifstream snake_file("game_snake_info.txt");
	if (snake_file.is_open())
	{
		std::string line;
		BaseClass snake_node;
		while (std::getline(snake_file, line))
		{
			std::istringstream stream(line);
			stream >> snake_node.m_x;
			stream >> snake_node.m_y;
			m_snake.m_nodes.push_back(snake_node);
		}

		snake_file.close();
	}
}

//�����а���Ϣ���浽�ļ�
void Game::SaveRankInfo()
{
	std::ofstream rank_file("rank.txt");
	if (rank_file.is_open())
	{
		for (int i = 0; i < (int)m_rank_list.size(); ++i)
		{
			rank_file << m_rank_list[i].id << " "
				<< m_rank_list[i].score << " " << m_rank_list[i].game_time << " " << std::endl;
		}

		rank_file.close();
	}
}

//��ȡ���а���Ϣ
void Game::ReadRankInfo()
{
	std::ifstream rank_file("rank.txt");
	if (rank_file.is_open())
	{
		std::string line;
		Rank rank;
		while (std::getline(rank_file, line))
		{
			std::istringstream stream(line);
			stream >> rank.id;
			stream >> rank.score;
			stream >> rank.game_time;
			m_rank_list.push_back(rank);
		}

		rank_file.close();
	}
}









#include "Game.h"

//构造函数
Game::Game() //构造函数 Game::Game()  构造函数，用于初始化 Game 对象。
{
	m_item_flag = 0; //道具标志位 m_item_flag 初始化为 0
	m_init_item_num = 5; //初始道具数量
	m_item_list.clear(); //清空存储道具的向量

	m_obstacle_flag = 0; //障碍物标志位 m_obstacle_flag 初始化为 0
	m_init_obstacle_num = 3; //初始障碍物数量
	m_obstacle_list.clear(); //清空存储障碍物的向量

	m_mark = 0; //游戏得分 m_mark 初始化为 0
	m_game_begin_time = 0; //游戏开始的时间 m_game_begin_time 初始化为 0

	m_rank_list.clear(); //清空存储排行榜的向量
	ReadRankInfo(); //读取排行榜信息
}

//析构函数，用于在 Game 对象销毁时进行资源清理。
Game::~Game() //析构函数 Game::~Game()
{

}

//初始化游戏菜单。
void Game::InitMenu() //初始化游菜单页面
{
	cleardevice(); //清除当前绘图设备上的所有内容

	IMAGE img; //用于存储加载的图像
	loadimage(&img, L"./background_image.jpg", 1000, 600); //从当前目录下加载名为 background_image.jpg 的图片，并将其缩放为 1000x600 的尺寸，存储到 img 中。
	putimage(0, 0, &img); //将加载的图片显示在绘图设备的左上角
	setbkmode(TRANSPARENT);//设置文本的背景模式为透明

	setfillcolor(BROWN); //设置填充颜色为棕色
	fillroundrect(280, 300, 280 + 200, 300 + 80, 10, 10); //绘制一个圆角矩形作为按钮
	settextstyle(30, 0, L"黑体");//设置文本的字体样式
	int width = textwidth(L"开始游戏");
	int high = textheight(L"开始游戏");
	outtextxy(280 + (200 - width) / 2, 300 + (80 - high) / 2, L"开始游戏");

	fillroundrect(500, 300, 500 + 200, 300 + 80, 10, 10);
	settextstyle(30, 0, L"黑体");
	width = textwidth(L"恢复存档");
	high = textheight(L"恢复存档");
	outtextxy(500 + (200 - width) / 2, 300 + (80 - high) / 2, L"恢复存档");

	fillroundrect(280, 400, 280 + 200, 400 + 80, 10, 10);
	settextstyle(30, 0, L"黑体");
	width = textwidth(L"游戏帮助");
	high = textheight(L"游戏帮助");
	outtextxy(280 + (200 - width) / 2, 400 + (80 - high) / 2, L"游戏帮助");

	fillroundrect(500, 400, 500 + 200, 400 + 80, 10, 10);
	settextstyle(30, 0, L"黑体");
	width = textwidth(L"游戏设置");
	high = textheight(L"游戏设置");
	outtextxy(500 + (200 - width) / 2, 400 + (80 - high) / 2, L"游戏设置");

	fillroundrect(280, 500, 280 + 200, 500 + 80, 10, 10);
	settextstyle(30, 0, L"黑体");
	width = textwidth(L"排行榜");
	high = textheight(L"排行榜");
	outtextxy(280 + (200 - width) / 2, 500 + (80 - high) / 2, L"排行榜");
}

//初始化游戏地图。
void Game::InitGameMap() //绘制游戏地图边框
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

	IMAGE img;// 加载并显示图片
	loadimage(&img, L"./snake.jpg", 400, 380);
	putimage(610, 0, &img);

	settextstyle(20, 15, _T("黑体")); //显示游戏得分信息
	wchar_t A[] = L"您的游戏当前得分为：";
	settextcolor(BLACK);
	outtextxy(620, 400, A);

	TCHAR s[5];
	_stprintf_s(s, _T("%d"), m_mark);
	settextcolor(MAGENTA);
	outtextxy(910, 400, s);

	wchar_t C[] = L"您的蛇移动速度为：   档"; //显示游戏速度信息
	settextcolor(BLACK);
	outtextxy(620, 490, C);

	_stprintf_s(s, _T("%d"), (150 - m_snake.m_speed) / 50); // 显示游戏时间信息
	settextcolor(RED);
	outtextxy(900, 490, s);

	wchar_t T[] = L"游戏时间已过去：  分  秒";
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
	settextstyle(15, 0, L"黑体");
	settextcolor(BLACK);
	if (m_is_stop)
	{
		int width = textwidth(L"继续");
		int high = textheight(L"继续");
		outtextxy(10 + (50 - width) / 2, 520 + (50 - high) / 2, L"继续");
	}
	else
	{
		int width = textwidth(L"暂停");
		int high = textheight(L"暂停");
		outtextxy(10 + (50 - width) / 2, 520 + (50 - high) / 2, L"暂停");
	}

	fillroundrect(80, 520, 140, 570, 60, 60);
	settextstyle(15, 0, L"黑体");
	settextcolor(BLACK);
	int width = textwidth(L"保存");
	int high = textheight(L"保存");
	outtextxy(80 + (50 - width) / 2, 520 + (50 - high) / 2, L"保存");*/

}

//进行游戏参数设置的初始化。
void Game::InitSet()
{
	IMAGE img; //加载并显示图片
	cleardevice();
	loadimage(&img, L"./background_set.jpg", 1000, 600);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);

	//设置蛇的初始长度相关内容
	setfillcolor(LIGHTBLUE); //设置填充颜色为浅蓝色
	fillroundrect(400, 100, 400 + 200, 100 + 50, 10, 10);//绘制一个圆角矩形作为按钮
	settextstyle(15, 0, L"黑体");//设置文本的字体样式
	settextcolor(BLACK);//设置文本颜色为黑色
	int width = textwidth(L"蛇的初始长度为：");
	int high = textheight(L"蛇的初始长度为：");
	outtextxy(400 + (200 - width) / 2, 100 + (50 - high) / 2, L"蛇的初始长度为：");
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), m_snake.m_snake_len);
	outtextxy(400 + (200 - width) / 2 + width, 100 + (50 - high) / 2, s);

	setfillcolor(BROWN);
	fillcircle(350, 125, 20);
	outtextxy(350, 120, L"一");

	setfillcolor(BROWN);
	fillcircle(650, 125, 20);
	outtextxy(650, 120, L"十");

	////设置道具的初始个数相关内容
	setbkmode(TRANSPARENT); 
	setfillcolor(LIGHTBLUE);
	fillroundrect(400, 180, 400 + 200, 180 + 50, 10, 10);
	settextstyle(15, 0, L"黑体");
	settextcolor(BLACK);
	width = textwidth(L"道具的初始个数为：");
	high = textheight(L"道具的初始个数为：");
	outtextxy(400 + (200 - width) / 2, 180 + (50 - high) / 2, L"道具的初始个数为：");
	_stprintf_s(s, _T("%d"), m_init_item_num);
	outtextxy(400 + (200 - width) / 2 + width, 180 + (50 - high) / 2, s);

	setfillcolor(BROWN);
	fillcircle(350, 205, 20);
	outtextxy(340, 195, L"一");

	setfillcolor(BROWN);
	fillcircle(650, 205, 20);
	outtextxy(642, 195, L"十");

	//设置障碍物的初始个数相关内容
	setbkmode(TRANSPARENT);
	setfillcolor(LIGHTBLUE);
	fillroundrect(400, 260, 400 + 200, 260 + 50, 10, 10);
	settextstyle(15, 0, L"黑体");
	settextcolor(BLACK);
	width = textwidth(L"障碍物的初始个数为：");
	high = textheight(L"障碍物的初始个数为：");
	outtextxy(400 + (200 - width) / 2, 260 + (50 - high) / 2, L"障碍物的初始个数为：");
	_stprintf_s(s, _T("%d"), m_init_obstacle_num);
	outtextxy(400 + (200 - width) / 2 + width, 260 + (50 - high) / 2, s);

	setfillcolor(BROWN);
	fillcircle(350, 285, 20);
	outtextxy(340, 275, L"一");

	setfillcolor(BROWN);
	fillcircle(650, 285, 20);
	outtextxy(642, 275, L"十");

	//设置返回按钮
	setbkmode(TRANSPARENT);
	setfillcolor(BROWN);
	fillroundrect(0, 0, 50, 50, 50, 50);
	settextstyle(15, 0, L"黑体");
	width = textwidth(L"返回");
	high = textheight(L"返回");
	outtextxy(0 + (50 - width) / 2, 0 + (50 - high) / 2, L"返回");
}

//让玩家选择游戏模式，返回一个布尔值表示选择结果。
bool Game::SelectGame()
{
	EndBatchDraw();//结束批量绘图
	cleardevice();//清除当前绘图设备上的所有内容
	InitMenu();//初始化游戏菜单

	ExMessage msg;//定义一个 ExMessage 类型的变量 msg，用于存储鼠标事件信息
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)//处理鼠标左键按下消息
			{
			case WM_LBUTTONDOWN://根据鼠标点击位置执行不同操作
			{
				//如果鼠标点击在“游戏帮助”按钮区域
				if (msg.x >= 280 && msg.x <= 280 + 200 && msg.y >= 400 && msg.y <= 400 + 80)
				{
					ShowHelp();//显示游戏帮助信息
				}

				//如果鼠标点击在“游戏设置”按钮区域
				if (msg.x >= 500 && msg.x <= 500 + 200 && msg.y >= 400 && msg.y <= 400 + 80)
				{
					InitSet();
					InitGameData();//初始化游戏数据（蛇的长度等等）。
				}

				//如果鼠标点击在“排行榜”按钮区域
				if (msg.x >= 280 && msg.x <= 280 + 200 && msg.y >= 500 && msg.y <= 500 + 80)
				{
					InitRank();//初始化排行榜

				}

				//如果鼠标点击在“恢复存档”按钮区域
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
				
					ReadGameInfo();//读取游戏的状态信息
					return true;
				}

				//如果鼠标点击在“开始游戏”按钮区域
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

//初始化游戏数据（蛇的长度等等）。
void Game::InitGameData() //初始化游戏数据
{
	int flag_food = 0;
	int flag_obstacle = 0;
	//用于标记鼠标是否位于食物和障碍物相关的区域，初始值都设为 0。

	while (1)//创建一个无限循环，用于持续监听鼠标消息并进行相应的处理。
	{
		ExMessage tmp; //初始化绘图和界面
		ExMessage t;
		BeginBatchDraw();
		InitSet();

		if (peekmessage(&tmp, EM_MOUSE)) //处理鼠标消息
		{
			switch (tmp.message)
			{
			case WM_LBUTTONDOWN:
				//检查鼠标点击位置是否在 “返回” 按钮范围内
				if (tmp.x >= 0 && tmp.x <= 50 && tmp.y >= 0 && tmp.y <= 50)
				{
					SelectGame();//让玩家选择游戏模式，返回一个布尔值表示选择结果。
					return;
				}
	
				//分别检查鼠标点击位置是否在蛇长度、食物数量和障碍物数量的增减按钮范围内，并根据相应条件对蛇的长度、食物的初始数量和障碍物的初始数量进行增减操作。
				if (tmp.x >= 330 && tmp.x <= 370 && tmp.y >= 105 && tmp.y <= 145)
				{
					if (m_snake.m_snake_len > 1)
					{
						int n = m_snake.m_snake_len - 1; //蛇身-1
						m_snake.SetSnakeLen(n);
					}
				}

				
				if (tmp.x >= 630 && tmp.x <= 670 && tmp.y >= 105 && tmp.y <= 145)
				{
					int n = m_snake.m_snake_len + 1; // 蛇身+1
					m_snake.SetSnakeLen(n);
				}

				if (tmp.x >= 330 && tmp.x <= 370 && tmp.y >= 180 && tmp.y <= 225)
				{
					if (m_init_item_num > 1)
					{
						int n = m_init_item_num - 1; //道具-1
						SetInitItemNum(n);
					}
				}

				if (tmp.x >= 630 && tmp.x <= 670 && tmp.y >= 180 && tmp.y <= 225)
				{
					if (m_init_item_num < 15)
					{
						int n = m_init_item_num + 1; //道具+1
						SetInitItemNum(n);
					}
				}

				if (tmp.x >= 330 && tmp.x <= 370 && tmp.y >= 265 && tmp.y <= 305)
				{
					if (m_init_obstacle_num > 1)
					{
						int n = m_init_obstacle_num - 1; //障碍物-1
						SetInitObstacle(n);
					}
				}

				if (tmp.x >= 630 && tmp.x <= 670 && tmp.y >= 265 && tmp.y <= 305)
				{
					if (m_init_obstacle_num < 15)
					{
						int n = m_init_obstacle_num + 1; //障碍物+1
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
					flag_food = 1; //表示鼠标在道具数量的区域内
				}
				else
				{
					flag_food = 0; //表示鼠标不在道具数量的区域内
				}

				if (t.x >= 400 && t.x <= 600 && t.y >= 260 && t.y <= 310)
				{
					flag_obstacle = 1; //表示鼠标在障碍物数量的区域内
				}
				else
				{
					flag_obstacle = 0; //表示鼠标不在障碍物数量的区域内
				}
			}
		}

		if (flag_food == 1) // 如果鼠标在道具数量的区域内  显示道具最大数量的提示信息
		{
			setbkmode(TRANSPARENT);
			setfillcolor(YELLOW);
			fillroundrect(t.x, t.y, t.x + 200, t.y + 50, 10, 10);
			settextstyle(15, 0, L"黑体");
			settextcolor(BLACK);
			int width = textwidth(L"道具的最大数量为：");
			int high = textheight(L"道具的最大数量为：");
			outtextxy(t.x + (200 - width) / 2, t.y + (50 - high) / 2, L"道具的最大数量为：");
			TCHAR s[5];
			_stprintf_s(s, _T("%d"), MAX_ITEM_NUM);
			outtextxy(t.x + (200 - width) / 2 + width, t.y + (50 - high) / 2, s);
		}

		if (flag_obstacle == 1) //如果鼠标在障碍物数量的区域内  显示障碍物最大数量的提示信息
		{
			setbkmode(TRANSPARENT);
			setfillcolor(YELLOW);
			fillroundrect(t.x, t.y, t.x + 200, t.y + 50, 10, 10);
			settextstyle(15, 0, L"黑体");
			settextcolor(BLACK);
			int width = textwidth(L"障碍物的最大数量为：");
			int high = textheight(L"障碍物的最大数量为：");
			outtextxy(t.x + (200 - width) / 2, t.y + (50 - high) / 2, L"障碍物的最大数量为：");
			TCHAR s[5];
			_stprintf_s(s, _T("%d"), MAX_ITEM_NUM);
			outtextxy(t.x + (200 - width) / 2 + width, t.y + (50 - high) / 2, s);
		}

		EndBatchDraw();
	}
}

//初始化排行榜（显示排行榜）
void Game::InitRank() //初始化排行榜
{
	//图形界面初始化
	IMAGE img;
	cleardevice();
	loadimage(&img, L"./background_set.jpg", 1000, 600);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, L"黑体");
	settextcolor(BLACK);
	//在指定坐标绘制表头
	outtextxy(200, 100, L"排名");
	outtextxy(400, 100, L"玩家id");
	outtextxy(600, 100, L"分数");
	
	//数据排序 使用 C++库中的std::sort函数实现按分数降序
	std::sort(m_rank_list.begin(), m_rank_list.end());
	//m_rank_list是一个存储rank结构体的容器
	//std::sort默认使用元素类型的<运算符进行比较
	//rank结构体在头文件Game.h中重载了<运算符，使其按分数降序排序

	TCHAR tmp[128];
	for (int i = 0; i < (int)m_rank_list.size(); ++i)
	{
		_stprintf_s(tmp, 128, _T("%d"), i + 1);
		outtextxy(200, 100 + (i + 1) * 50, tmp);

		_stprintf_s(tmp, 128, _T("玩家%d"), m_rank_list[i].id);
		outtextxy(400, 100 + (i + 1) * 50, tmp);

		_stprintf_s(tmp, 128, _T("%d"), m_rank_list[i].score);
		outtextxy(600, 100 + (i + 1) * 50, tmp);
	}

	//设置返回按钮
	setbkmode(TRANSPARENT);
	setfillcolor(BROWN);
	fillroundrect(0, 0, 50, 50, 50, 50);
	settextstyle(15, 0, L"黑体");
	int width = textwidth(L"返回");
	int high = textheight(L"返回");
	outtextxy(0 + (50 - width) / 2, 0 + (50 - high) / 2, L"返回");
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
					InitMenu();//初始化游戏菜单。

					return;
				}
			}
		}
	}
}

//显示游戏帮助信息
void Game::ShowHelp()
{
	IMAGE img;
	cleardevice();
	loadimage(&img, L"./background_help.png", 1000, 600);
	putimage(0, 0, &img);
	settextstyle(20, 0, L"黑体");
	settextcolor(BLACK);
	outtextxy(200, 70, L"---本游戏的键盘操控规则---");
	outtextxy(110, 90, L"w or W or ↑ 为向上移动");
	outtextxy(110, 110, L"a or A or ← 为向左移动");
	outtextxy(110, 130, L"s or S or ↓ 为向下移动");
	outtextxy(110, 150, L"d or D or → 为向右移动");
	outtextxy(110, 170, L"q or Q or → 暂停游戏");
	outtextxy(110, 190, L"e or E or → 保存游戏");
	outtextxy(200, 240, L"---本游戏的死亡规则---");
	outtextxy(110, 270, L"当您的蛇超过了边界范围或者蛇头碰到自己的身体或者碰到障碍物 游戏就会结束");
	outtextxy(110, 300, L"障碍物初始有3个 蛇的长度增加为五的倍数就多一个障碍物 最多30个");
	outtextxy(110, 330, L"食物初始有3个 蛇的长度每增加三节就多一个食物 最多30个");
	
	//设置返回按钮
	setbkmode(TRANSPARENT);
	setfillcolor(BROWN);
	fillroundrect(0, 0, 50, 50, 50, 50);
	settextstyle(15, 0, L"黑体");
	int width = textwidth(L"返回");
	int high = textheight(L"返回");
	outtextxy(0 + (50 - width) / 2, 0 + (50 - high) / 2, L"返回");
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
					InitMenu();//初始化游戏菜单。
					return;
				}
			}
		}
	}
}

//启动游戏 负责初始化游戏环境，生成游戏元素，并启动主循环
void Game::Start()
{
	system("cls"); //清除控制台屏幕
	system("color 9E");//设置控制台背景色为蓝色，前景色为白色

	//初始化图形窗口
	initgraph(1000, 600);
	cleardevice(); //清空绘图区域
	setbkcolor(WHITE); //设置背景色为白色

	//使用mciSendString API播放背景音乐
	//open命令打开音乐文件
	//play...repeat命令播放音乐并设置为循环播放
	mciSendString(L"open ./background_music.mp3", NULL, 0, NULL);
	mciSendString(L"play ./background_music.mp3 repeat", NULL, 0, NULL);

	//选择游戏模式
	if (SelectGame())//让玩家选择游戏模式，返回一个布尔值表示选择结果。
	{
		cleardevice();
	    
		//生成初始游戏道具
		for (int i = 0; i < m_init_item_num; ++i)
		{
			Item item;
			int randnum = rand() % 100; //随机数决定道具类型
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

		//生成障碍物
		for (int i = 0; i < m_init_obstacle_num; ++i)
		{
			Obstacle obstacle;
			m_obstacle_list.push_back(obstacle);
		}

		//记录游戏开始时间并允许游戏主循环
		m_game_begin_time = (int)std::time(nullptr);
		while (1)
		{
			Run();
			Sleep(m_snake.m_speed);
		}
	}
}

//游戏主循环 负责处理输入，更新游戏状态和渲染游戏画面。
void Game::Run()
{
	//处理键盘输入
	if (GetAsyncKeyState('q') || GetAsyncKeyState('Q'))
		//Q/q切换游戏暂停状态
	{
		m_is_stop = !m_is_stop;
	}

	if (GetAsyncKeyState('e') || GetAsyncKeyState('E'))
		//E/e键保存游戏进度
	{
		SaveGameInfo();//将游戏的当前状态信息保存到文本文件中
	}

	//开始批量绘图并清屏
	BeginBatchDraw();
	cleardevice();
	InitGameMap(); //初始化游戏地图

	//游戏中动态生成游戏道具
	if ((int)m_item_list.size() < MAX_ITEM_NUM && m_item_flag == 3)
	{
		Item item;
		int randnum = rand() % 100;
		if (randnum < 50)//50%概率生成普通金币，50%概率生成药品（这里没有设置生成双倍金币
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

	//显示游戏道具
	for (int i = 0; i < (int)m_item_list.size() && i < MAX_ITEM_NUM; i++)
	{
		m_item_list[i].Show();
	}

	//游戏中动态生成障碍物
	if ((int)m_obstacle_list.size() < MAX_OBSTACLE && m_obstacle_flag == 5)
	{
		Obstacle obstacle;
		m_obstacle_list.push_back(obstacle);
		m_obstacle_flag = 0;
	}

	//显示障碍物
	for (int j = 0; j < (int)m_obstacle_list.size() && j < MAX_OBSTACLE; j++)
	{
		m_obstacle_list[j].Show();
	}

	//显示蛇
	m_snake.Show(); //绘制蛇的所有节点
	if (IsSnakeDie())//检查蛇是否死亡（例如撞到自己或边界）。
	{
		GameOver();//处理游戏结束逻辑
	}

	//移动蛇
	if (!m_is_stop) //未暂停游戏时，蛇才会移动
	{
		m_snake.BodyMove();//蛇的身体移动
	}
	
	//处理蛇吃道具的情况
	EatItem();////检测蛇是否迟到道具，并处理效果
	EndBatchDraw();
}


//检测蛇是否吃到道具，并处理效果
void Game::EatItem()
{
	//遍历所有道具
	for (int i = 0; i < (int)m_item_list.size() && i < MAX_ITEM_NUM; i++)
	{  
		//判断蛇头是否与道具重叠
		if (m_snake.m_nodes[0].m_x == m_item_list[i].m_x && m_snake.m_nodes[0].m_y == m_item_list[i].m_y)
		{  
			//播放吃道具的音效
			mciSendString(L"close ./eat_food_music.mp3", NULL, 0, NULL);
			mciSendString(L"open ./eat_food_music.mp3", NULL, 0, NULL);
			mciSendString(L"play ./eat_food_music.mp3", NULL, 0, NULL);
			
			//根据道具类型更新分数和蛇的长度
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

			//更新道具位置并修改标志位
			m_item_list[i].Change();
			m_item_flag++;
			m_obstacle_flag++;

			return;
		}
	}
}

//检查蛇是否死亡（例如撞到自己或边界或障碍物）
bool Game::IsSnakeDie()
{
	//边界碰撞检测
	if (m_snake.m_nodes[0].m_x + 5 >= 590 || m_snake.m_nodes[0].m_x - 5 <= 10 
		|| m_snake.m_nodes[0].m_y + 5 >= 500 || m_snake.m_nodes[0].m_y - 5 <= 10)
	{
		return true;
	}

	//障碍物碰撞检测
	for (int j = 0; j < (int)m_obstacle_list.size(); j++)//遍历所有障碍物，检查蛇头是否与其碰撞
	{
		//从四个方向检查蛇头圆形与障碍物矩形的重叠
		//蛇头坐标 ±5（半径）与障碍物矩形坐标比较

		//检查蛇头在障碍物的右侧碰撞情况
		if (m_snake.m_nodes[0].m_x + 5 >= m_obstacle_list[j].m_x // 蛇头右侧≥障碍物左侧
			&& m_snake.m_nodes[0].m_x + 5 <= m_obstacle_list[j].m_x + 10//蛇头右侧≤障碍物右侧
			&& m_snake.m_nodes[0].m_y >= m_obstacle_list[j].m_y - 10 // 蛇头顶部≥障碍物底部
			&& m_snake.m_nodes[0].m_y <= m_obstacle_list[j].m_y)//蛇头顶部≤障碍物顶部
		{
			return true;
		}
	
		//检查蛇头在障碍物的左侧碰撞情况
		if (m_snake.m_nodes[0].m_x - 5 <= m_obstacle_list[j].m_x + 10 
			&& m_snake.m_nodes[0].m_x - 5 >= m_obstacle_list[j].m_x
			&& m_snake.m_nodes[0].m_y >= m_obstacle_list[j].m_y - 10 
			&& m_snake.m_nodes[0].m_y <= m_obstacle_list[j].m_y)
		{
			return true;
		}

		//检查蛇头在障碍物的下方碰撞情况
		if (m_snake.m_nodes[0].m_y + 5 >= m_obstacle_list[j].m_y - 10 
			&& m_snake.m_nodes[0].m_y + 5 <= m_obstacle_list[j].m_y
			&& m_snake.m_nodes[0].m_x >= m_obstacle_list[j].m_x
			&& m_snake.m_nodes[0].m_x <= m_obstacle_list[j].m_x + 10)
		{
			return true;
		}

		//检查蛇头在障碍物的上方碰撞情况
		if (m_snake.m_nodes[0].m_y - 5 <= m_obstacle_list[j].m_y 
			&& m_snake.m_nodes[0].m_y - 5 >= m_obstacle_list[j].m_y - 10
			&& m_snake.m_nodes[0].m_x >= m_obstacle_list[j].m_x 
			&& m_snake.m_nodes[0].m_x <= m_obstacle_list[j].m_x + 10)
		{
			return true;
		}
	}

	//蛇头与蛇身碰撞检测（自碰撞检测，检查蛇头是否与身体其他节点坐标重合）
	//从第一个身体节点开始检查（i=1，跳过蛇头 i=0） 直接比较坐标是否完全相同
	for (int i = 1; i < m_snake.m_nodes.size(); i++)
	{
		if (m_snake.m_nodes[0].m_x == m_snake.m_nodes[i].m_x && m_snake.m_nodes[0].m_y == m_snake.m_nodes[i].m_y)
		{
			return true;
		}
	}

	return false;
}

//处理游戏结束逻辑
//包括界面显示，分数记录和用户交互
void Game::GameOver()
{
	//音乐
	EndBatchDraw(); //结束批量绘图
	mciSendString(L"stop ./background_music.mp3", NULL, 0, NULL);
	mciSendString(L"close ./game_fail_music.mp3 ", NULL, 0, NULL);
	mciSendString(L"open ./game_fail_music.mp3", NULL, 0, NULL);
	mciSendString(L"play ./game_fail_music.mp3 ", NULL, 0, NULL);

	//游戏结束界面绘制
	Sleep(1500); //延迟1.5s
	cleardevice();
	IMAGE img;
	cleardevice();
	loadimage(&img, L"./game_end_image.png", 1000, 600);
	putimage(0, 0, &img);
	settextcolor(RED);
	settextstyle(40, 0, L"华文隶书");
	outtextxy(310, 250, L"---------游戏结束----------");
	settextcolor(BLACK);
	settextstyle(40, 0, L"黑体");
	outtextxy(300, 330, L"您的得分为：");
	TCHAR s[5];
	settextcolor(RED);
	_stprintf_s(s, _T("%d"), m_mark);
	outtextxy(550, 330, s);

	//分数记录与排行榜更新
	Rank rank;//创建新的 Rank 结构体记录当前游戏数据
	rank.id = (int)m_rank_list.size() + 1;//排行榜条目编号
	rank.score = m_mark; //游戏得分
	rank.game_time = (int)std::time(nullptr) - m_game_begin_time;//游戏时长
	rank.game_time = rank.game_time < 0 ? 9999 : rank.game_time; //防止时间为负数，设为9999
	m_rank_list.push_back(rank); //将当前游戏数据添加到排行榜列表中
	SaveRankInfo();//将排行榜信息保存到文件


	//用户交互与游戏重启
	HWND hwnd = GetHWnd();
	while (1)
		//循环检测鼠标左键点击
	{
		ExMessage tmp;
		peekmessage(&tmp, EM_MOUSE);
		if (tmp.message == WM_LBUTTONDOWN)
		{
			if (tmp.x >= 0 && tmp.y >= 0)
			{
				int isok = MessageBox(hwnd, L"很遗憾，游戏失败，请问您是否需要重新开始", L"提示", MB_YESNOCANCEL);
				if (isok == IDYES)//选择“是”
				{
					srand((unsigned int)time(nullptr)); //重置随机数种子
					closegraph(); //关闭当前图形窗口
					Game b; //创建新的 Game 对象 b并初始化参数
					b.m_mark = 0;
					b.m_init_item_num = 3;
					b.m_snake.m_snake_len = 3;
					b.m_init_obstacle_num = 3;
					b.m_game_begin_time = 0;
					b.m_is_stop = false;
					b.Start();//调用 Start() 方法开始新游戏
				}
				else if (isok == IDNO)//选择“否”
				{
					exit(0);
				}
			}
		}
	}
}

//将游戏的当前状态信息保存到文本文件中
void Game::SaveGameInfo()
{  
	//保存游戏的基本信息到文件
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

	//保存游戏的道具信息到文件
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

	//保存游戏的障碍物信息到文件
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

	//保存游戏的蛇的信息到文件
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

//读取游戏的状态信息
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

//将排行榜信息保存到文件
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

//读取排行榜信息
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









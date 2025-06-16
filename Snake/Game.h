#ifndef GAME_H

//这四个都是自定义的头文件
#include "FileInclude.h" //包含所有需要的头文件
#include "Snake.h"   //包含Snake类 蛇
#include "Item.h"    //包含Item类 道具
#include "Obstacle.h" //包含Obstacle类 障碍物

static const int MAX_ITEM_NUM = 30;  //定义了游戏中道具的最大数量为 30。
static const int MAX_OBSTACLE = 15;  //定义了游戏中障碍物的最大数量为 15。

enum ITEM_TYPE  //定义了道具的类型 （枚举类型）
{
	ITEM_COIN = 0, //金币（得分）
	ITEM_DRUGS,    //药品
	ITEM_DOUBLE_COIN, //双倍金币
};


class Game //定义Game类 
{

public:
	Game();  //构造函数，用于初始化 Game 对象。
	~Game(); //析构函数，用于在 Game 对象销毁时进行资源清理。

	//游戏初始化
	void InitMenu();  //初始化游戏菜单。
	void InitGameMap(); //初始化游戏地图。
	void InitSet();   //进行游戏参数设置的初始化。
	bool SelectGame(); //让玩家选择游戏模式，返回一个布尔值表示选择结果。
	void InitGameData(); //初始化游戏数据（蛇的长度等等）。
	void InitRank(); //加载排行榜数据。
	void ShowHelp();//显示游戏帮助信息

	//启动
	void Start();  //启动游戏。
	void Run(); //运行游戏的主循环。

	//游戏逻辑处理
	void EatItem(); //检测蛇是否迟到道具，并处理效果
	bool IsSnakeDie(); //检查蛇是否死亡（例如撞到自己或边界）。
	void GameOver(); //处理游戏结束逻辑

	//保存和读取
	void SaveGameInfo(); //保存游戏信息到文件。
	void ReadGameInfo(); //读取游戏信息从文件。
	void SaveRankInfo(); //保存排行榜数据到文件。
	void ReadRankInfo(); //从文件中读取排行榜信息。

    //设置道具和障碍物
	void SetInitItemNum(int n) { m_init_item_num = n; } //设置初始道具数量
	void SetInitObstacle(int n) { m_init_obstacle_num = n; } //初始障碍物数量。



private: //私有成员变量

	//道具
	int m_item_flag; //道具生成/消失标志位。
	int m_init_item_num; //初始道具数量。
	typedef std::vector<Item> ItemList; //定义了一个 std::vector<Item> 类型的别名，用于存储游戏中的道具。
	ItemList m_item_list; //存储游戏中所有道具的向量。

	//障碍物
	int m_obstacle_flag; //障碍物生成/消失的标志位。
	int m_init_obstacle_num; //初始障碍物数量。
	typedef std::vector<Obstacle> ObstacleList; //定义了一个 std::vector<Obstacle> 类型的别名，用于存储游戏中的障碍物。
	ObstacleList m_obstacle_list; //存储游戏中所有障碍物的向量。
	
	//蛇
	Snake m_snake; //游戏中的蛇对象。

	//游戏状态
	int m_mark;//游戏得分。
	int m_game_begin_time;//游戏开始的时间（用于计算时长）
	bool m_is_stop;//游戏是否暂停

	//排行榜记录结构体
	struct Rank //用于表示排行榜中的一条记录，包含编号（id）、得分（score）和游戏时间（game_time）。
	{
		Rank()
		{
			id = 0; //编号
			score = 0;//分数
			game_time = 0;//游戏时长
		}

		//重载了小于运算符 <，用于在排行榜中比较两条记录的得分和游戏时间，
		// //实现先按分数降序排序，若分数相同，则按游戏时间升序排序。
		bool operator < (const Rank& other) const
		{
			if (score > other.score)
			{
				return true;
			}

			return game_time >other.game_time;
		}

		int id; 
		int score;
		int game_time;
	};

	typedef std::vector<Rank> RankList;//排行榜列表类型别名
	RankList m_rank_list;//存储所有排行榜记录的容器


};

#endif // !GAME_H


#ifndef GAME_H

//���ĸ������Զ����ͷ�ļ�
#include "FileInclude.h" //����������Ҫ��ͷ�ļ�
#include "Snake.h"   //����Snake�� ��
#include "Item.h"    //����Item�� ����
#include "Obstacle.h" //����Obstacle�� �ϰ���

static const int MAX_ITEM_NUM = 30;  //��������Ϸ�е��ߵ��������Ϊ 30��
static const int MAX_OBSTACLE = 15;  //��������Ϸ���ϰ�����������Ϊ 15��

enum ITEM_TYPE  //�����˵��ߵ����� ��ö�����ͣ�
{
	ITEM_COIN = 0, //��ң��÷֣�
	ITEM_DRUGS,    //ҩƷ
	ITEM_DOUBLE_COIN, //˫�����
};


class Game //����Game�� 
{

public:
	Game();  //���캯�������ڳ�ʼ�� Game ����
	~Game(); //���������������� Game ��������ʱ������Դ����

	//��Ϸ��ʼ��
	void InitMenu();  //��ʼ����Ϸ�˵���
	void InitGameMap(); //��ʼ����Ϸ��ͼ��
	void InitSet();   //������Ϸ�������õĳ�ʼ����
	bool SelectGame(); //�����ѡ����Ϸģʽ������һ������ֵ��ʾѡ������
	void InitGameData(); //��ʼ����Ϸ���ݣ��ߵĳ��ȵȵȣ���
	void InitRank(); //�������а����ݡ�
	void ShowHelp();//��ʾ��Ϸ������Ϣ

	//����
	void Start();  //������Ϸ��
	void Run(); //������Ϸ����ѭ����

	//��Ϸ�߼�����
	void EatItem(); //������Ƿ�ٵ����ߣ�������Ч��
	bool IsSnakeDie(); //������Ƿ�����������ײ���Լ���߽磩��
	void GameOver(); //������Ϸ�����߼�

	//����Ͷ�ȡ
	void SaveGameInfo(); //������Ϸ��Ϣ���ļ���
	void ReadGameInfo(); //��ȡ��Ϸ��Ϣ���ļ���
	void SaveRankInfo(); //�������а����ݵ��ļ���
	void ReadRankInfo(); //���ļ��ж�ȡ���а���Ϣ��

    //���õ��ߺ��ϰ���
	void SetInitItemNum(int n) { m_init_item_num = n; } //���ó�ʼ��������
	void SetInitObstacle(int n) { m_init_obstacle_num = n; } //��ʼ�ϰ���������



private: //˽�г�Ա����

	//����
	int m_item_flag; //��������/��ʧ��־λ��
	int m_init_item_num; //��ʼ����������
	typedef std::vector<Item> ItemList; //������һ�� std::vector<Item> ���͵ı��������ڴ洢��Ϸ�еĵ��ߡ�
	ItemList m_item_list; //�洢��Ϸ�����е��ߵ�������

	//�ϰ���
	int m_obstacle_flag; //�ϰ�������/��ʧ�ı�־λ��
	int m_init_obstacle_num; //��ʼ�ϰ���������
	typedef std::vector<Obstacle> ObstacleList; //������һ�� std::vector<Obstacle> ���͵ı��������ڴ洢��Ϸ�е��ϰ��
	ObstacleList m_obstacle_list; //�洢��Ϸ�������ϰ����������
	
	//��
	Snake m_snake; //��Ϸ�е��߶���

	//��Ϸ״̬
	int m_mark;//��Ϸ�÷֡�
	int m_game_begin_time;//��Ϸ��ʼ��ʱ�䣨���ڼ���ʱ����
	bool m_is_stop;//��Ϸ�Ƿ���ͣ

	//���а��¼�ṹ��
	struct Rank //���ڱ�ʾ���а��е�һ����¼��������ţ�id�����÷֣�score������Ϸʱ�䣨game_time����
	{
		Rank()
		{
			id = 0; //���
			score = 0;//����
			game_time = 0;//��Ϸʱ��
		}

		//������С������� <�����������а��бȽ�������¼�ĵ÷ֺ���Ϸʱ�䣬
		// //ʵ���Ȱ���������������������ͬ������Ϸʱ����������
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

	typedef std::vector<Rank> RankList;//���а��б����ͱ���
	RankList m_rank_list;//�洢�������а��¼������


};

#endif // !GAME_H


#include <hgeanim.h>
#include <hgesprite.h>
#include <thread>
#include "Box.h"
#include "Timer.h"
#include "Utils.h"
#pragma once
enum DIRE
{
	DIRE_UP, DIRE_RIGHT, DIRE_DOWN, DIRE_LEFT,
};
class Player 
{
private:
	hgeAnimation *upAnimation;
	int map_side;//��ͼ����߳�
	int x, y;  //��ͼ����
	float sence_x, sence_y;//��������
	int speed; //�ƶ��ٶ�
	int dire;//��ǰ����
	int renderTime = 0; //�ϴ���Ⱦʱ��
	Timer *timer;
	bool isMoving = 0;
	Box *box=NULL;
	int (*map)[15];
	void moveUP();
	void moveRight();
	void moveDown();
	void moveLeft();
public:
	Player(HTEXTURE tex, int map_side);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setDire(DIRE dire);
	void Render(); //��Ⱦ���
	void update(int);
	void move(DIRE dire,Timer *timer, Box *box[],int map[10][15]);
	void pushBox(Box *box[],int x,int y);
	~Player();
};


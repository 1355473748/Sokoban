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
	hgeSprite *rightAnimation[4];
	hgeSprite *upAnimation[4];
	hgeSprite *downAnimation[4];
	hgeSprite *leftAnimation[4];
	int spr_index;//��ǰ״̬��������
	int map_side;//��ͼ����߳�
	int x, y;  //��ͼ����
	float sence_x, sence_y;//��������
	int speed; //�ƶ��ٶ�
	DIRE dire;//��ǰ����
	float renderTime = 0; //�ϴ���Ⱦʱ��
	float updateTime = 0; //�ϴθ��¶���ʱ��
	float boxStopTime; //����ֹͣʱ��
	float *timer;
	bool isMoving = 0;
	Box *box=NULL;
	int (*map)[9];
	int (*map_back)[8][9]; //��¼��ʷ����ָ��
	int *step;
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
	void Render(float,float); //��Ⱦ���
	void move(DIRE dire,float *timer, Box *box[],int map[8][9], int map_back[][8][9], int *step);
	void findBox(Box * box[], int x, int y);
	void pushBox(Box *box[],int x,int y);
	void stopBox(Box * box[], int x, int y);
	void stopBoxThread();
	void recodeMap();
	DIRE getDir();
	~Player();
};


#include "Player.h"
#include <stdio.h>
#include <ctime>
Player::Player(HTEXTURE tex,int map_side)
{
	this->rightAnimation[0] =new hgeSprite(tex,0,0,64,64);
	this->rightAnimation[1] = new hgeSprite(tex, 64, 0, 64, 64);
	this->rightAnimation[2] = new hgeSprite(tex, 64*2, 0, 64, 64);
	this->rightAnimation[3] = new hgeSprite(tex, 64*3, 0, 64, 64);
	
	this->upAnimation[0] = new hgeSprite(tex, 64*4, 0, 64, 64);
	this->upAnimation[1] = new hgeSprite(tex, 64*5, 0, 64, 64);
	this->upAnimation[2] = new hgeSprite(tex, 64 * 6, 0, 64, 64);
	this->upAnimation[3] = new hgeSprite(tex, 64 * 7, 0, 64, 64);

	this->downAnimation[0] = new hgeSprite(tex, 64 * 8, 0, 64, 64);
	this->downAnimation[1] = new hgeSprite(tex, 64 * 9, 0, 64, 64);
	this->downAnimation[2] = new hgeSprite(tex, 64 * 10, 0, 64, 64);
	this->downAnimation[3] = new hgeSprite(tex, 64 * 11, 0, 64, 64);

	this->leftAnimation[0] = new hgeSprite(tex, 64 * 12, 0, 64, 64);
	this->leftAnimation[1] = new hgeSprite(tex, 64 * 13, 0, 64, 64);
	this->leftAnimation[2] = new hgeSprite(tex, 64 * 14, 0, 64, 64);
	this->leftAnimation[3] = new hgeSprite(tex, 64 * 15, 0, 64, 64);
	spr_index = 0;
	this->map_side = map_side;
	this->speed = 16;
}
void Player::setX(int x) {
	this->x = x;
	sence_x = x*map_side;
}
void Player::setY(int y) {
	this->y = y;
	sence_y = y*map_side;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

void Player::setDire(DIRE dire)
{
	this->dire = dire;
}

void Player::Render(float off_x,float off_y)//��Ⱦ��ǰ����
{
	switch (dire) {
	case DIRE_UP:
		if (spr_index > 3) spr_index = 0;
		this->upAnimation[spr_index]->Render(sence_x + off_x, sence_y + off_y);
		break;
	case DIRE_RIGHT:
		if (spr_index > 3) spr_index = 0;
		this->rightAnimation[spr_index]->Render(sence_x + off_x, sence_y + off_y);
		break;
	case DIRE_DOWN:
		if (spr_index > 3) spr_index = 0;
		this->downAnimation[spr_index]->Render(sence_x + off_x, sence_y + off_y);
		break;
	case DIRE_LEFT:
		if (spr_index > 3) spr_index = 0;
		this->leftAnimation[spr_index]->Render(sence_x + off_x, sence_y + off_y);
		break;
	}
}


void Player::move(DIRE dire,float *timer,Box *box[],int map[8][9],int map_back[][8][9],int *step)
{
	this->map = map;
	if (!isMoving) {
		this->dire = dire;
		this->timer = timer;
		this->map_back = map_back;
		this->step = step;
		switch (this->dire)
		{
		case DIRE_UP: 
		{
			if (map[y-1][x] != 2 && !this->box)
			{
				if (map[y - 1][x] == 3) //������
				{
					if (map[y-2][x] == 2 || map[y - 2][x] == 3){//��������һ��Ϊǽ�ͻ����Ӿ��Ʋ���
						//���������Ʋ�����Ч
						stopBox(box, x , y-1);
						break;
					} 
					pushBox(box, x, y - 1);
				}
			std::thread t(&Player::moveUP, this);  //���߳��ƶ�
			t.detach();
			isMoving = true;
			}
			break;
		}
		case DIRE_RIGHT:
		{	
			if (map[y][x + 1] != 2 && !this->box)
			{
				if (map[y][x + 1] == 3)
				{
					if (map[y][x + 2] == 2 || map[y][x + 2] == 3) {
						//���������Ʋ�����Ч
						stopBox(box, x + 1, y);
						break;
					}
					pushBox(box, x + 1, y);
				}
				std::thread t(&Player::moveRight, this);
				t.detach();
				isMoving = true;
			}	
			break;
		}
		case DIRE_DOWN:
		{
			if (map[y+1][x]!=2 &&!this->box) //��Ϊǽ���ƶ�
			{
				if (map[y + 1][x] == 3) //������
				{
					if (map[y+2][x ] == 3 || map[y + 2][x] == 2) {//��������һ��Ϊǽ�ͻ����Ӿ��Ʋ���
						//���������Ʋ�����Ч
						stopBox(box, x, y+1);
						break;
					}
					pushBox(box, x,y + 1);
				}
				std::thread t(&Player::moveDown, this);
				t.detach();
				isMoving = true;
			}
			
			break;
		}
		case DIRE_LEFT:
			if (map[y][x - 1] != 2 && !this->box)
			{
				if (map[y][x - 1] == 3)
				{
					if (map[y][x - 2] == 2 || map[y][x - 2] == 3) {
					//���������Ʋ�����Ч
					stopBox(box, x - 1, y);
					break;
					}
					pushBox(box, x - 1, y);
				}
				std::thread t(&Player::moveLeft, this);
				t.detach();
				isMoving = true;
			}
			break;
		}
	}
	
}
void Player::findBox(Box *box[], int x, int y) {
	for (int i = 0; i < Box::box_count; i++) {
		if (box[i]->x == x&&box[i]->y == y)
		{
			this->box = box[i];
			break;
		}
	}
}
void Player::pushBox(Box *box[], int x, int y) //��ʼ������
{
	findBox(box, x, y);
	this->box->isMoving = true;
}
void Player::stopBox(Box *box[], int x, int y) {
	findBox(box,x,y);
	boxStopTime = *timer;
	if (!this->box->isMoving) {
		this->box->isMoving = true;
	std::thread t(&Player::stopBoxThread, this);  //�����߳�֪ͨ����
	t.detach();
	}
}
void Player::stopBoxThread() {
	Sleep(100);
	this->box->isMoving = false;
	this->box = NULL;
	
}
void Player::recodeMap()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 9; j++)
			map_back[*step][i][j] = map[i][j];
	map_back[*step][y][x] = 1;
}
DIRE Player::getDir()
{
	return this->dire;
}
void Player::moveUP()
{
	//��ʼ�ƶ�
	//��¼�ƶ�ʱ��ͼֵ
	recodeMap();
	(*step)++;
	bool isEnd;
	map[y - 2][x] == 4 ? isEnd = true : isEnd = false; //�ж��������ǲ����յ�
	while (sence_y > (y-1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_y -= speed;
			this->spr_index++;
			if (box)
			{
				box->sence_y = this->sence_y - map_side;
			}
			renderTime = *timer;
		}
		
	}
	//�ƶ�����
	y--;
	sence_y = y*map_side;
	isMoving = false;
	if (box) {//�����ƶ�����
		if (box->isDone) {
			map[box->y][box->x] = 4;
			box->isDone = false;
		}
		else
		{
			map[box->y][box->x] = 0;
		}
		if (isEnd)box->isDone = true;
		this->box->y--;
		this->box->isMoving = false;
		map[box->y][box->x] = 3;
		box = NULL;
	}
}
void Player::moveRight()
{
	//��ʼ�ƶ�
	//��¼�ƶ�ʱ��ͼֵ
	recodeMap();
	(*step)++;
	bool isEnd=false;
	map[y][x+2] == 4 ? isEnd = true : isEnd = false; //�ж��������ǲ����յ�
	while (sence_x < (x+ 1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_x += speed;
			//Utils::alertInt(this->spr_index);
			this->spr_index++;
			if (box)
			{
				box->sence_x=this->sence_x+map_side;
			}
			renderTime = *timer;
		}

	}
	//�ƶ�����
	x++;
	isMoving = false;
	if (box) {//�����ƶ�����
		if (box->isDone) {
			map[box->y][box->x] = 4;       //�����յ�
			box->isDone = false;
		}
		else
		{
			map[box->y][box->x] = 0;
		}
		if (isEnd) box->isDone = true;   //�����յ�
		this->box->x++;
		this->box->isMoving = false;
		map[box->y][box->x] = 3; //���µ�ͼ
		box = NULL;
	}
}

void Player::moveDown()
{
	//��ʼ�ƶ�
	//��¼�ƶ�ʱ��ͼֵ
	recodeMap();
	(*step)++;
	bool isEnd;
	map[y + 2][x]==4?isEnd=true:isEnd=false; //�ж��������ǲ����յ�
	while (sence_y < (y + 1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_y += speed;
			this->spr_index++;
			if (box)
			{
				box->sence_y = this->sence_y + map_side;
			}
			renderTime = *timer;
		}

	}
	//�ƶ�����
	y++;
	isMoving = false;
	if (box) {//�����ƶ�����
		if (box->isDone) {
			map[box->y][box->x] = 4;
			box->isDone = false;
		}
		else
		{
			map[box->y][box->x] = 0;
		}
		if (isEnd)box->isDone = true;		
		this->box->y++;
		this->box->isMoving = false;

		map[box->y][box->x] = 3;
		box = NULL;
	}
}
void Player::moveLeft()
{
	//��ʼ�ƶ�
	//��¼�ƶ�ʱ��ͼֵ
	recodeMap();
	(*step)++;
	bool isEnd = false;
	map[y][x - 2] == 4 ? isEnd = true : isEnd = false; //�ж��������ǲ����յ�
	while (sence_x > (x - 1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_x -= speed;
			this->spr_index++;
			if (box)        //��������ӣ����Ӻ���һ������
			{
				box->sence_x = this->sence_x - map_side;
			}
			renderTime = *timer;
		}

	}
	//�ƶ�����
	x--;
	sence_x = x*map_side;
	isMoving = false;
	if (box) {//�����ƶ�����
		if (box->isDone) {
			map[box->y][box->x] = 4;       //�����յ�
			box->isDone = false;
		}
		else
		{
			map[box->y][box->x] = 0;
		}
		if (isEnd) box->isDone = true;   //�����յ�
		this->box->x--;
		this->box->isMoving = false;
		map[box->y][box->x] = 3; //���µ�ͼ
		box = NULL;
	}
}
Player::~Player()
{
	delete(upAnimation);
	delete(downAnimation);
	delete(leftAnimation);
	delete(rightAnimation);
}

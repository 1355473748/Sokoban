#include "Player.h"
#include <stdio.h>


Player::Player(HTEXTURE tex,int map_side)
{
	this->upAnimation =new hgeAnimation(tex, 3, 1, 0, 0, 55, 80);
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

void Player::Render()//��Ⱦ��ǰ����
{
	switch (dire) {
	case DIRE_UP :
			this->upAnimation->Render(sence_x, sence_y-10);
			break;
	default:
		this->upAnimation->Render(sence_x, sence_y-10);
	}
	
}

void Player::update(int time)
{
	this->upAnimation->Update(time);
}

void Player::move(DIRE dire,float *timer,Box *box[],int map[10][15])
{
	this->map = map;
	if (!isMoving) {
		this->dire = dire;
		this->timer = timer;
		switch (this->dire)
		{
		case DIRE_UP: 
		{
			if (map[y-1][x] != 2)
			{
				if (map[y - 1][x] == 3) //������
				{
					if (map[y - 2][x] == 2) break; //��������һ��Ϊǽ�ͻ����Ӿ��Ʋ���
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
			if (map[y][x + 1] != 2)
			{
				if (map[y][x + 1] == 3)
				{
					if (map[y][x + 2] == 2 || map[y][x + 2] == 3)break;
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
			if (map[y+1][x]!=2) //��Ϊǽ���ƶ�
			{
				if (map[y + 1][x] == 3) //������
				{
					if (map[y + 2][x] ==2) break; //��������һ��Ϊǽ���ж�
					pushBox(box, x,y + 1);
				}
				std::thread t(&Player::moveDown, this);
				t.detach();
				isMoving = true;
			}
			
			break;
		}
		case DIRE_LEFT:
			if (map[y][x - 1] != 2)
			{
				if (map[y][x - 1] == 3)	pushBox(box, x - 1, y);
				std::thread t(&Player::moveLeft, this);
				t.detach();
				isMoving = true;
			}
			break;
		}
	}
	
}

void Player::pushBox(Box *box[], int x, int y) //��ʼ������
{
	for (int i = 0; i < Box::box_count;i++) {
		if (box[i]->x==x&&box[i]->y==y)
		{
			this->box = box[i];
			break;
		}
	}
	this->box->isMoving = true;
}

void Player::moveUP()
{
	upAnimation->Play();
	//��ʼ�ƶ�
	//��¼�ƶ�ʱ��ͼֵ
	bool isEnd;
	map[y - 2][x] == 4 ? isEnd = true : isEnd = false; //�ж��������ǲ����յ�
	while (sence_y > (y-1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_y -= speed;
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
	upAnimation->Stop();
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
	upAnimation->Play();
	//��ʼ�ƶ�
	//��¼�ƶ�ʱ��ͼֵ
	bool isEnd=false;
	map[y][x+2] == 4 ? isEnd = true : isEnd = false; //�ж��������ǲ����յ�
	while (sence_x < (x+ 1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_x += speed;
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
	upAnimation->Stop();
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
	upAnimation->Play();
	//��ʼ�ƶ�
	//��¼�ƶ�ʱ��ͼֵ
	bool isEnd;
	map[y + 2][x]==4?isEnd=true:isEnd=false; //�ж��������ǲ����յ�
	while (sence_y < (y + 1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_y += speed;
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
	upAnimation->Stop();
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
	upAnimation->Play();
	//��ʼ�ƶ�
	bool isEnd = false;
	map[y][x + 2] == 4 ? isEnd = true : isEnd = false; //�ж��������ǲ����յ�
	while (sence_x > (x - 1)*map_side)
	{
		if (*timer - renderTime > 0.1) {
			this->sence_x -= speed;
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
	upAnimation->Stop();
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
}

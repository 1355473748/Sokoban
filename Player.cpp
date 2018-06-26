#include "Player.h"
#include <stdio.h>


Player::Player(HTEXTURE tex,int map_side)
{
	this->upAnimation =new hgeAnimation(tex, 3, 1, 0, 0, 55, 80);
	this->map_side = map_side;
	this->speed = 20;
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

void Player::move(DIRE dire,Timer *timer)
{

	if (!isMoving) {
		this->dire = dire;
		this->timer = timer;
		switch (this->dire)
		{
		case DIRE_UP: 
		{
			std::thread t(&Player::moveUP, this);  //���߳��ƶ�
			t.detach();
			isMoving = true;
			break;
		}
		case DIRE_RIGHT:
		{	std::thread t(&Player::moveRight, this);
		t.detach();
		isMoving = true;
		break;
		}
		case DIRE_DOWN:
		{
			std::thread t(&Player::moveDown, this);
			t.detach();
			isMoving = true;
			break;
		}
		case DIRE_LEFT:
			std::thread t(&Player::moveLeft, this);
			t.detach();
			isMoving = true;
			break;
		}
	}
	
}


Box * Player::isBox(Box box)
{
	return &box;
}

void Player::pushBox(Box *box)
{
	this->box = box;
}

void Player::moveUP()
{
	upAnimation->Play();
//��ʼ�ƶ�
	while (sence_y > (y-1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_y -= speed;
			renderTime = timer->getTime();
		}
		
	}
	//�ƶ�����
	y--;
	sence_y = y*map_side;
	isMoving = false;
	upAnimation->Stop();
}

void Player::moveRight()
{
	upAnimation->Play();
	//��ʼ�ƶ�
	while (sence_x < (x+ 1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_x += speed;
			if (box)
			{
				box->sence_x=this->sence_x+map_side;
			}
			renderTime = timer->getTime();
		}

	}
	//�ƶ�����
	x++;
	sence_x = x*map_side; //������������
	isMoving = false;
	upAnimation->Stop();
	if (box) {
		//����һ���ƶ�����
		this->box->x++;
		this->box->sence_x=this->box->x*map_side; //������������
		box = NULL;
	}
}

void Player::moveDown()
{
	upAnimation->Play();
	//��ʼ�ƶ�
	while (sence_y < (y + 1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_y += speed;
			renderTime = timer->getTime();
		}

	}
	//�ƶ�����
	y++;
	sence_y = y*map_side;
	isMoving = false;
	upAnimation->Stop();
}
void Player::moveLeft()
{
	upAnimation->Play();
	//��ʼ�ƶ�
	while (sence_x > (x - 1)*map_side)
	{
		if (timer->getTime() - renderTime > 1) {
			this->sence_x -= speed;
			renderTime = timer->getTime();
		}

	}
	//�ƶ�����
	x--;
	sence_x = x*map_side;
	isMoving = false;
	upAnimation->Stop();
}
Player::~Player()
{
	delete(upAnimation);
}

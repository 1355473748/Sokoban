#include <hgesprite.h>
#pragma once
class Box //������
{
	friend class Player;
private:
	hgeSprite *sprite; //����ͼƬ
	hgeSprite *sprite_moving; //�ƶ�ʱͼƬ
	int map_side;//��ͼ����߳�
	int x, y;  //��ͼ����
	float sence_x, sence_y;//��������
	bool isMoving = 0;
public:
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	Box(hgeSprite *sprite, hgeSprite *sprite_moving, int map_side);
	void Render(); //��Ⱦ����
	~Box();
};


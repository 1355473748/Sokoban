#include <hgesprite.h>
#pragma once
class Box //������
{
	friend class Player;
private:
	hgeSprite *sprite; //����ͼƬ
	hgeSprite *sprite_moving; //�ƶ�ʱͼƬ
	hgeSprite *sprite_done; //���ʱͼƬ
	int map_side;//��ͼ����߳�
	int x, y;  //��ͼ����
	float sence_x, sence_y;//��������
	bool isMoving = 0;
	bool isDone=0; //�Ƿ����
public:
	static int box_count;       //��¼���Ӹ���
	static void clear();
	Box(hgeSprite * sprite, hgeSprite * sprite_moving, hgeSprite * sprite_done, int map_side);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void Render(float,float); //��Ⱦ����
	~Box();
};


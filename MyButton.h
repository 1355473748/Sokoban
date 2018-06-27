#pragma once
#include <hgesprite.h>
#include <thread>
#include "Timer.h"
class MyButton
{
private:
	bool status; //��Ϊ����
	float x, y;
	hgeSprite *sprite_up;
	hgeSprite *sprite_down;
	void(*click)();
	float updateTime;
public:
	MyButton(float x, float y, hgeSprite *sprite_up, hgeSprite *sprite_down,void click());
	void keyDown(float point_x, float point_y,float time);
	void stopThread(); //֪ͨ������Ч����
	void Render();
	// ֪ͨGUI����Ҽ����
	~MyButton();
};


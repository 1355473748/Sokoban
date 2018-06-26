/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/


#include "hge.h"
#include <hgesprite.h>
#include <hgeanim.h>
#include "Timer.h"
#include "Player.h"
#include "Utils.h"
#include <thread> 
#include"Box.h"
enum Map_TYPE //��ͼ����ö��
{
	MAP_FLLOR, MAP_PLAYER, MAP_WALL, MAP_BOX
};
//��ͼ
int const map_side = 64;
int const map_height = 10;
int const map_width = 15;
int map[15][10] = { 0 };
HGE *hge = 0;
//������Դ
HTEXTURE tex;
hgeSprite *sprite;
//����(24 * 58)
Player *player;
hgeSprite *sprite_player[10];
HTEXTURE tex_players;
hgeAnimation *player_animation;
int player_index = 0; //ͼƬ����
//�ذ�(64 * 64)
hgeSprite *sprite_floor[10];
//ǽ
hgeSprite *sprite_wall[10];
//����
Box *box;
hgeSprite *sprite_box[10];
//�յ�
hgeSprite *sprite_end_up[10];
hgeSprite *sprite_end_down[10];
//���ָ��
hgeSprite *sprite_point;
float point_x, point_y;
//ȫ�ּ�ʱ��
Timer timer;
bool FrameFunc()
{

	timer.run();//��¼
	hge->Input_GetMousePos(&point_x,&point_y);
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_W))
	{
		player->move(DIRE_UP,&timer);

	}
	if (hge->Input_GetKeyState(HGEK_D))
	{
		player->pushBox(box);
		player->move(DIRE_RIGHT, &timer);
	}
	if (hge->Input_GetKeyState(HGEK_S))
	{
		player->move(DIRE_DOWN, &timer);
	}
	if (hge->Input_GetKeyState(HGEK_A))
	{
		player->move(DIRE_LEFT, &timer);
	}

	player->update(1);
	return false;
}
// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	
	hge->Gfx_BeginScene();
	// Clear screen with black color
	hge->Gfx_Clear(0);
	
	for (int i = 0; i < map_width; i++)
		for (int j = 0; j < map_height; j++)
		{
			sprite_floor[2]->Render(i * map_side, j* map_side);
			switch (map[i][j])
			{
			case 0: //����
				break;
			case 1: //������
				break;
			case 2://��ǽ
				break;
			case MAP_BOX://������
				//box->Render();
				   //sprite_box[0]->Render(i * map_side, j* map_side);
				break;
			default:
				break;
			}

		}
	box->Render();
	player->Render();
	player_animation->Render(100, 100);
	player_animation->Update(100);
	//��Ⱦ���.
	sprite_point->Render(point_x,point_y);
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}
void init() {
	//��ʼ����ͼ
	map[0][0] = MAP_BOX;
	map[5][6] = MAP_BOX;
	map[5][4] = MAP_BOX;
	map[4][6] = MAP_BOX;
	map[4][4] = MAP_BOX;
	//������Դ
	tex = hge->Texture_Load("res/image/bj.jpg");
	tex_players = hge->Texture_Load("res/image/players.png");
	//�������
	player=new Player(tex_players,map_side);
	player->setDire(DIRE_UP);
	player->setX(0);
	player->setY(0);

	//��������
	sprite_box[0] = new hgeSprite(hge->Texture_Load("res/image/Crate_Beige.png"), 0, 0, 64, 64);
	sprite_box[6] = new hgeSprite(hge->Texture_Load("res/image/CrateDark_Beige"), 0, 0, 64, 64);
	box = new Box(sprite_box[0], sprite_box[6],map_side);
	box->setX(1);
	box->setY(0);
	map[box->getX()][box->getY()] = MAP_BOX;
	
	map[player->getX()][player->getY()] = MAP_PLAYER;


	player_animation = new hgeAnimation(tex_players, 3, 10,0, 0,55, 80);
	player_animation->Play();
	sprite = new hgeSprite(tex, 0, 0, 1000, 600);
	sprite_player[0] = new hgeSprite(hge->Texture_Load("res/image/Character2.png"), 0, 0, 42, 58);//��
	sprite_player[1] = new hgeSprite(hge->Texture_Load("res/image/Character3.png"), 0, 0, 42, 58);
	sprite_player[2] = new hgeSprite(hge->Texture_Load("res/image/Character4.png"), 0, 0, 42, 58);//��
	sprite_player[3] = new hgeSprite(hge->Texture_Load("res/image/Character5.png"), 0, 0, 42, 58);
	sprite_player[4] = new hgeSprite(hge->Texture_Load("res/image/Character6.png"), 0, 0, 42, 58);
	sprite_player[5] = new hgeSprite(hge->Texture_Load("res/image/Character7.png"), 0, 0, 42, 58);//��
	sprite_player[6] = new hgeSprite(hge->Texture_Load("res/image/Character8.png"), 0, 0, 42, 58);
	sprite_player[7] = new hgeSprite(hge->Texture_Load("res/image/Character9.png"), 0, 0, 42, 58);
	sprite_player[8] = new hgeSprite(hge->Texture_Load("res/image/Character10.png"), 0, 0, 42, 58);//��
	sprite_player[9] = new hgeSprite(hge->Texture_Load("res/image/Character11.png"), 0, 0, 42, 58);
	sprite_floor[0] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Concrete.png"), 0, 0, 64, 64);
	sprite_floor[1] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Dirt.png"), 0, 0, 64, 64);
	sprite_floor[2] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Grass.png"), 0, 0, 64, 64);
	sprite_floor[3] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Sand.png"), 0, 0, 64, 64);

	sprite_box[0] = new hgeSprite(hge->Texture_Load("res/image/Crate_Beige.png"), 0, 0, 64, 64);
	sprite_box[1] = new hgeSprite(hge->Texture_Load("res/image/Crate_Black.png"), 0, 0, 64, 64);
	sprite_box[2] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);
	sprite_box[3] = new hgeSprite(hge->Texture_Load("res/image/Crate_Brown.png"), 0, 0, 64, 64);
	sprite_point = new hgeSprite(hge->Texture_Load("res/image/cur.png"), 0, 0, 32, 32);
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	hge = hgeCreate(HGE_VERSION);

	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	// Set the window title
	hge->System_SetState(HGE_TITLE, "��������Ϸ");

	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENHEIGHT, map_height*map_side);
	hge->System_SetState(HGE_SCREENWIDTH, map_width*map_side);
	hge->System_SetState(HGE_FPS, 60); //ִ��60��Ϊһ��
	 // �Ƿ�ʹ������
	hge->System_SetState(HGE_USESOUND, false);
	if (hge->System_Initiate())
	{
		init();
		//����hge����(��ͣ�ĵ��ø��º�������Ⱦ����,ֱ�����º�������true)
		hge->System_Start();
	}
	else
	{
		// If HGE initialization failed show error message
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	//�ر�����
	hge->System_Shutdown();
	//�ͷ�ָ��
	hge->Release();

	return 0;
}
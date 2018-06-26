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
	MAP_FLLOR, MAP_PLAYER, MAP_WALL, MAP_BOX, MAP_END
};
enum GameState{ Start, Game }g_GameState;
//��ͼ
int const map_side = 64;
int const map_height = 10;
int const map_width = 15;
int map[10][15] = {
	{ 0,0,0,0,1,3,0,0,0,0,0,0,0,0,0 },
	{ 2,0,0,0,3,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,4,0,0,0,0,0,0,0,0,0,0 },
	{ 2,2,2,2,4,0,2,2,2,2,2,2,2,2,2},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,4,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,2,0,0,0,0,0,0,0 }
};
HGE *hge = 0;
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
Box *box[10];   
hgeSprite *sprite_box[10];
//�յ�
hgeSprite *sprite_end_up[10];
hgeSprite *sprite_end_down[10];
//���ָ��
hgeSprite *sprite_point;
float point_x, point_y;
//ȫ�ּ�ʱ��
float timer;
bool FrameFunc()
{
	timer=hge->Timer_GetTime();//ÿ�ε��ü�¼ʱ�䣬���ƶ��߳�֪��ʱ��
	hge->Input_GetMousePos(&point_x,&point_y);
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_W))
	{
		player->move(DIRE_UP,&timer,box, map);
	}
	if (hge->Input_GetKeyState(HGEK_D))
	{
		player->move(DIRE_RIGHT, &timer,box, map);
	}
	if (hge->Input_GetKeyState(HGEK_S))
	{
		player->move(DIRE_DOWN, &timer, box, map);
	}
	if (hge->Input_GetKeyState(HGEK_A))
	{
		player->move(DIRE_LEFT, &timer, box, map);
	}
	player->update(1);
	return false;
}
//��ʼ������Ⱦ
void startRender() {

}
//��Ⱦ��ͼ
void RendMap() {
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
		{
			sprite_floor[2]->Render(j * map_side, i* map_side);
			switch (map[i][j])
			{
			case 0:
				
				break;
			case 2:
				sprite_wall[0]->Render(j * map_side, i* map_side);
				break;
			case 4:
				sprite_end_up[0]->Render(j * map_side, i* map_side);
				break;
			}
		}
}
void GameRender(){
	switch (g_GameState)
	{
	case Start:
		startRender();
		break;
	case Game:
		//��Ⱦ��ͼ
		RendMap();
		//��Ⱦ����
		for (int i=0;i<Box::box_count;i++)
		{
			box[i]->Render();
		}
		//��Ⱦ����
		player->Render();
		break;
	}

}
bool RenderFunc()
{
	
	hge->Gfx_BeginScene();
	// Clear screen with black color
	hge->Gfx_Clear(0);
	
	GameRender();
	//��Ⱦ���.
	sprite_point->Render(point_x,point_y);
	hge->Gfx_EndScene();
	return false;
}
void level_init() {  //�ؿ���ʼ��
	Box::clear();
	//��ʼ����ͼ
// 	map[1][1] = MAP_WALL;
// 	map[2][2] = MAP_PLAYER;
	//��������
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
		{
			switch (map[i][j])
			{	
			case MAP_PLAYER: //�������	
				player = new Player(tex_players, map_side);
				player->setDire(DIRE_UP);         //�ؿ���ʼʱ��ҵķ���
				player->setX(j);
				player->setY(i);
				map[i][j] = 0; //���ü�¼���λ��
				break;
			case MAP_BOX: //��������
				int count = Box::box_count;
				box[count] = new Box(sprite_box[0], sprite_box[1], map_side);
				box[Box::box_count - 1]->setX(j);
				box[Box::box_count - 1]->setY(i);
				break;
			}
		}
}
void init() { //��ʼ����Ϸϵͳ
	
	//������Դ
	
	tex_players = hge->Texture_Load("res/image/players.png");
	sprite_floor[0] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Concrete.png"), 0, 0, 64, 64);
	sprite_floor[1] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Dirt.png"), 0, 0, 64, 64);
	sprite_floor[2] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Grass.png"), 0, 0, 64, 64);
	sprite_floor[3] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Sand.png"), 0, 0, 64, 64);

	sprite_box[0] = new hgeSprite(hge->Texture_Load("res/image/Crate_Beige.png"), 0, 0, 64, 64);
	sprite_box[1] = new hgeSprite(hge->Texture_Load("res/image/CrateDark_Beige.png"), 0, 0, 64, 64);
	sprite_box[2] = new hgeSprite(hge->Texture_Load("res/image/Crate_Black.png"), 0, 0, 64, 64);
	sprite_box[4] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);
	sprite_box[5] = new hgeSprite(hge->Texture_Load("res/image/Crate_Brown.png"), 0, 0, 64, 64);

	sprite_wall[0] = new hgeSprite(hge->Texture_Load("res/image/Wall_Brown.png"), 0, 0, 64, 64);

	sprite_end_up[0] = new hgeSprite(hge->Texture_Load("res/image/EndPoint_Blue.png"), 0, 0, 64, 64);
	sprite_point = new hgeSprite(hge->Texture_Load("res/image/cur.png"), 0, 0, 32, 32);
	g_GameState=Game;
	level_init();
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
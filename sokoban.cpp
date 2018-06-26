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
#include "Player.h"
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
hgeSprite *sprite_box[10];
//�յ�
hgeSprite *sprite_end_up[10];
hgeSprite *sprite_end_down[10];
int time = 0; //ʱ��
int times = 0; //ʱ�������
int oldTime = 0;
// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
int x = 5, y = 5;
bool FrameFunc()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_W))
	{
		if (time - oldTime > 1)
		{
			map[x][y] = 0;
			y--;
			map[x][y] = 1;
			oldTime = time;
		}

	}
	if (hge->Input_GetKeyState(HGEK_D))
	{
		if (time - oldTime > 1)
		{
			map[x][y] = 0;
			x++;
			map[x][y] = 1;
			oldTime = time;
		}

	}
	if (hge->Input_GetKeyState(HGEK_S))
	{
		if (time - oldTime > 1)
		{
			map[x][y] = 0;
			y++;
			map[x][y] = 1;
			oldTime = time;
		}
	}
	if (hge->Input_GetKeyState(HGEK_A))
	{
		if (time - oldTime > 1)
		{
			map[x][y] = 0;
			x--;
			player_index = 8;
			player_index = 9;
			map[x][y] = 1;
			oldTime = time;
		}
	}
	// Continue execution
	return false;
}
// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	times++;
	if (times >= 10) //100ms
	{
		time++;
		times = 0;
	}

	// Begin rendering quads.
	// This function must be called
	// before any actual rendering.
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
				sprite_player[player_index]->Render(i * map_side + 10, j* map_side);
				break;
			case 2://��ǽ
				break;
			case 3://������
				sprite_box[0]->Render(i * map_side, j* map_side);
				break;
			default:
				break;
			}

		}
	player->Render(map_side);
	player_animation->Render(100, 100);
	if (time - oldTime) {
		player_animation->Update(1);
		oldTime = time;
	}
	
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}
void init() {
	//��ʼ����ͼ
	map[5][5] = 1;
	map[5][6] = 3;
	map[5][4] = 3;
	map[4][6] = 3;
	map[4][4] = 3;
	//������Դ
	tex = hge->Texture_Load("res/image/bj.jpg");
	tex_players = hge->Texture_Load("res/image/players.png");

	//�������
	player=new Player(tex_players);
	player->setDire(DIRE_UP);
	player->setX(1);
	player->setY(1);



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

	sprite_box[0] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);
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
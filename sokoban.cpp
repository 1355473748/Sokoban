/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/
 //__vsnprintf���÷����ں��� "public: void __cdecl hgeFont::printf(float,float,int,char const *,...)" (? printf@hgeFont@@QAAXMMHPBDZZ) �б�����	sokoban	C : \Users\huanzi\Source\Repos\Sokoban\hgehelp.lib(hgefont.obj)	1


#include "hge.h"
#include <hgesprite.h>
#include <hgeanim.h>
#include "Timer.h"
#include "Player.h"
#include "Utils.h"
#include <thread> 
#include"Box.h"
#include <hgefont.h>
#include <hgeguictrls.h>
enum Map_TYPE //��ͼ����ö��
{
	MAP_FLLOR, MAP_PLAYER, MAP_WALL, MAP_BOX, MAP_END
};
enum GameState{ Start, Game }g_GameState;
//��ͼ
int const map_side = 64;
int const map_height = 8;
int const map_width = 12;
int const map_off_x = 0;
int const map_off_y = 0;
int map[10][15] = {
	{ 2,2,2,2,2,2,2,2,2,5,5,5,5,5,5},
	{ 2,1,0,4,0,0,0,0,2,5,5,5,5,5,5 },
	{ 2,0,0,3,0,0,0,0,2,5,5,5,5,5,5 },
	{ 2,0,0,0,0,0,0,0,2,5,5,5,5,5,5 },
	{ 2,0,0,0,0,0,0,0,2,5,5,5,5,5,5 },
	{ 2,0,0,0,0,0,0,0,2,5,5,5,5,5,5 },
	{ 2,0,0,0,0,0,0,0,2,5,5,5,5,5,5 },
	{ 2,2,2,2,2,2,2,2,2,5,5,5,5,5,5 }
};
HGE *hge = 0;
//����(24 * 58)
Player *player;
HTEXTURE tex_players;
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
float updateTime=0; //�ϴθ���ʱ��
//����
hgeSprite *sprite_backgroud;
hgeSprite *sprite_start;
//���ﶯ��
hgeSprite *sprite_man;
float man_x = 100, man_y = 200;
float man_time=0;
int man_status=0; //����
//����
hgeFont *font;
hgeGUIText *text;
//��ť
hgeGUIButton *but_start;
bool GameUpdate() {
	
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_W))
	{
		player->move(DIRE_UP, &timer, box, map);
	}
	if (hge->Input_GetKeyState(HGEK_D))
	{
		player->move(DIRE_RIGHT, &timer, box, map);
	}
	if (hge->Input_GetKeyState(HGEK_S))
	{
		player->move(DIRE_DOWN, &timer, box, map);
	}
	if (hge->Input_GetKeyState(HGEK_A))
	{
		player->move(DIRE_LEFT, &timer, box, map);
	}
	if (timer - updateTime > 0.1)
	{
		player->update(100);
	}
	return false;
}
bool StartUpdate() {
	if (hge->Timer_GetTime()-man_time>0.2)
	{
		if (man_y == 70) man_status = 1;
		if (man_y == 200) man_status = 0;
		man_status?man_y++:man_y--;
	}
	if (but_start->GetState())
	{
		Utils::alertInt(1);
	}
	but_start->Update(hge->Timer_GetDelta());
	return false;
}
bool FrameFunc()
{
	timer=hge->Timer_GetTime();//ÿ�ε��ü�¼ʱ�䣬���ƶ��߳�֪��ʱ��
	hge->Input_GetMousePos(&point_x, &point_y);
	switch (g_GameState)
	{
	case Start:
		return StartUpdate();
	case Game:
		return GameUpdate();
	}
	return false;
}
//��ʼ������Ⱦ
void startRender() {
	font->printf(100, 100, HGETEXT_CENTER, "hello");
	font->Render(100,100, HGETEXT_LEFT, "hello");
	text->Render();
	sprite_start->Render(0, 0);
	sprite_man->Render(man_x,man_y);
	but_start->Render();
}
//��Ⱦ��ͼ
void RendMap() {
	//sprite_backgroud->Render(0, 0);
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
		{
			if (map[i][j] == 5) continue;
			float x = j * map_side + map_off_x, y = i* map_side + map_off_y;
			map[i][j] == 2 ? sprite_wall[0]->Render(x,y ) : sprite_floor[2]->Render(x, y);
			if (map[i][j]==4) sprite_end_up[0]->Render(x, y);
			switch (map[i][j])
			{
			case 0:
				sprite_floor[2]->Render(x, y);
				break;
			case 2:
				sprite_wall[0]->Render(x, y);
				break;
			case 4:
				sprite_floor[2]->Render(x, y);
				sprite_end_up[0]->Render(x, y);
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
			box[i]->Render(map_off_x,map_off_y);
		}
		//��Ⱦ����
		player->Render(map_off_x,map_off_y);
		break;
	}
}
bool RenderFunc()
{
	
	hge->Gfx_BeginScene();
	// Clear screen with black color
	hge->Gfx_Clear(100);
	
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
				box[count] = new Box(sprite_box[0], sprite_box[1],sprite_box[2], map_side);
				box[Box::box_count - 1]->setX(j);
				box[Box::box_count - 1]->setY(i);
				break;
			}
		}
}
void init() { //��ʼ����Ϸϵͳ
	
	//������Դ
	font = new hgeFont("res/font/font1.fnt");
	text = new hgeGUIText(0,10,10,10,10,font);
	font->SetColor(100);
	font->SetScale(0.2);
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
	sprite_backgroud = new hgeSprite(hge->Texture_Load("res/image/background.jpg"), 0, 0, 1000,1000);
	sprite_start = new hgeSprite(hge->Texture_Load("res/image/start.jpg"), 0, 0,768, 512);
	sprite_man = new hgeSprite(hge->Texture_Load("res/image/man.png"), 0, 0, 82, 130);
	but_start = new hgeGUIButton(0,20,20,100,100,tex_players,20,20);
	but_start->SetMode(true);
	g_GameState=Start;
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
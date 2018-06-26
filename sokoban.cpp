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
enum Map_TYPE //地图类型枚举
{
	MAP_FLLOR, MAP_PLAYER, MAP_WALL, MAP_BOX, MAP_END
};
//地图
int const map_side = 64;
int const map_height = 10;
int const map_width = 15;
int map[15][10];
HGE *hge = 0;
//纹理资源
HTEXTURE tex;
hgeSprite *sprite;
//人物(24 * 58)
Player *player;
hgeSprite *sprite_player[10];
HTEXTURE tex_players;
hgeAnimation *player_animation;
int player_index = 0; //图片索引
//地板(64 * 64)
hgeSprite *sprite_floor[10];
//墙
hgeSprite *sprite_wall[10];
//箱子
Box *box[10];   
hgeSprite *sprite_box[10];
//终点
hgeSprite *sprite_end_up[10];
hgeSprite *sprite_end_down[10];
//鼠标指针
hgeSprite *sprite_point;
float point_x, point_y;
//全局计时器
Timer timer;
bool FrameFunc()
{

	timer.run();//记录
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

//渲染地图
void RendMap() {
	for (int i = 0; i < map_width; i++)
		for (int j = 0; j < map_height; j++)
		{
			//Utils::alertInt(map[i][j]);
			map[i][j]==MAP_WALL? sprite_wall[0]->Render(i * map_side, j* map_side): sprite_floor[2]->Render(i * map_side, j* map_side);//不是墙就画地板

		}
}
bool RenderFunc()
{
	
	hge->Gfx_BeginScene();
	// Clear screen with black color
	hge->Gfx_Clear(0);
	

	RendMap();
	//渲染箱子
	//渲染人物
	player->Render();

	//渲染鼠标.
	sprite_point->Render(point_x,point_y);
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}
void level_init() {  //关卡初始化
	Box::clear();
	//初始化地图
//  	int map [15][10] = {
//  		{2,0,0,0,0,0,0,0,0,0},
//  		{0,0,0,0,0,0,0,0,0,0},
// 		{ 0,0,0,0,0,0,0,0,0,0},
// 		{ 0,0,0,0,0,0,0,0,0,0},
// 		{ 0,0,0,0,0,0,0,0,0,0},
// 		{ 0,0,0,0,2,0,0,0,0,0},
// 		{ 0,0,0,0,0,0,0,0,0,0},
// 		{ 0,0,0,0,0,0,0,0,0,0},
// 		{ 0,0,0,0,0,0,0,0,0,0},
// 		{ 0,0,0,0,0,0,0,0,0,0}
//  	};
	map[1][1] = MAP_WALL;
	map[2][2] = MAP_PLAYER;
	//构建对象
	for (int i = 0; i < map_width; i++)
		for (int j = 0; j < map_height; j++)
		{
			switch (map[i][j])
			{
			case MAP_PLAYER: //构建玩家
				player = new Player(tex_players, map_side);
				player->setDire(DIRE_UP);         //关卡开始时玩家的方向
				player->setX(i);
				player->setY(j);
				break;
			case MAP_BOX: //构造箱子
				int count = Box::box_count;
				box[count] = new Box(sprite_box[0], sprite_box[6], map_side);
				box[Box::box_count - 1]->setX(i);
				box[Box::box_count - 1]->setY(j);
				break;
			}
		}
}
void init() { //初始化游戏系统
	
	//加载资源
	tex = hge->Texture_Load("res/image/bj.jpg");
	tex_players = hge->Texture_Load("res/image/players.png");
	player_animation = new hgeAnimation(tex_players, 3, 10,0, 0,55, 80);
	player_animation->Play();
	sprite = new hgeSprite(tex, 0, 0, 1000, 600);
	sprite_floor[0] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Concrete.png"), 0, 0, 64, 64);
	sprite_floor[1] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Dirt.png"), 0, 0, 64, 64);
	sprite_floor[2] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Grass.png"), 0, 0, 64, 64);
	sprite_floor[3] = new hgeSprite(hge->Texture_Load("res/image/GroundGravel_Sand.png"), 0, 0, 64, 64);

	sprite_box[1] = new hgeSprite(hge->Texture_Load("res/image/Crate_Black.png"), 0, 0, 64, 64);
	sprite_box[2] = new hgeSprite(hge->Texture_Load("res/image/Crate_Blue.png"), 0, 0, 64, 64);
	sprite_box[3] = new hgeSprite(hge->Texture_Load("res/image/Crate_Brown.png"), 0, 0, 64, 64);

	sprite_wall[0] = new hgeSprite(hge->Texture_Load("res/image/Wall_Brown.png"), 0, 0, 64, 64);
	sprite_point = new hgeSprite(hge->Texture_Load("res/image/cur.png"), 0, 0, 32, 32);

	level_init();
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	hge = hgeCreate(HGE_VERSION);

	// Set our frame function
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	// Set the window title
	hge->System_SetState(HGE_TITLE, "推箱子游戏");

	// Run in windowed mode
	// Default window size is 800x600
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENHEIGHT, map_height*map_side);
	hge->System_SetState(HGE_SCREENWIDTH, map_width*map_side);
	hge->System_SetState(HGE_FPS, 60); //执行60次为一秒
	 // 是否使用声音
	hge->System_SetState(HGE_USESOUND, false);
	if (hge->System_Initiate())
	{
		init();
		//启动hge引擎(不停的调用更新函数和渲染函数,直到更新函数返回true)
		hge->System_Start();
	}
	else
	{
		// If HGE initialization failed show error message
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	//关闭引擎
	hge->System_Shutdown();
	//释放指针
	hge->Release();

	return 0;
}
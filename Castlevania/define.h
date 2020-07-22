#pragma once

#pragma once
#include <fstream> 
#include <string>
#include <stdio.h>
#include <Windows.h>  
//#include <mmsystem.h>
#include <iostream>
#include <map>
#include "debug.h" 
#include <algorithm>
#include <d3dx9.h>
#include <stdlib.h>
#include <iomanip>
#include <d3d9.h>
#include <vector>
#include <iostream>
enum GType
{
	SIMON = 01,
	SIMON_DEATH = 02,
	//Weapon
	MORNINGSTAR = 03,
	DRAGGER = 04,
	HOLYWATER = 05,
	STOPWATCH = 06,
	FIREBALL = 07,
	THROWINGAXE = 8,
	CROSS = 9,
	//Enemy
	GHOST = 10,
	RAVEN = 11,
	BAT = 12,
	ALIEN = 13,
	KNIGHT = 14,
	SKELETON = 15,
	BIGBAT = 16,
	FLEAMAN = 17,
	//Obj
	BRICK = 18,
	TORCH = 19,
	CANDLE = 20,
	//Stair
	STAIRTOP = 21,
	STAIRBOT = 22,
	//Item
	REDMONEYBAG = 23,
	UPGRADEWEAPON = 24,
	HEART = 25,
	BIGHEART = 26,
	PURPLEMONEYBAG = 27,
	ROSARY = 28,
	MAGICCRYSTAL = 29,
	DOUBLESHOT = 30,
	TRIPLESHOT = 31,
	FORKCHOP = 32,
	IPOTION = 33,
	WHITEMONEYBAG = 34,
	MONEYBAG = 35,
	//Effect
	HIT = 36,
	BURN = 37,
	BRICKEFCT = 38,
	//Others
	BBOX = 39,
	BOARD = 40,
	RENDERBBOX = 41,
	RENDERBBOX1 = 42,
	HEALTH = 43,
	FONT = 44,
	HIDENOBJ = 45,
	BONE = 46,
	ELEVATOR = 47,
	CROWN=48,
	TREASURE=49,
	SECRETBRICK=50,
	NOTHING=51,
	SCENEINTRO=52,
	INTROBAT=53,
	MENUBAT=54,
	STARSHIP=55,
};


enum GState
{
	WALK=01,
	JUMP=02,
	ATTACK=03,
	STOP=04,
	SIT=05,
	ONSTAIR=06,
	DOWNSTAIR=07,
	HIDEFACE=8,
};

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania-NES"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define BACKGROUND_COLOR2 D3DCOLOR_XRGB(240,242,245)
#define SCREEN_WIDTH 530
#define SCREEN_HEIGHT 510
#define CellW (SCREEN_WIDTH/4.0f)
#define CellH (SCREEN_HEIGHT/4.0f)
#define MAX_FRAME_RATE 90
#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Textures.h"
#include "Game.h"
#include "debug.h"

using namespace std;

class CSprite
{
	RECT CurrentFrame;
	int TotalFrame,
		MapId,
		State;
	DWORD TimeAni,
		TotalTime,
		LastFrameTime,
		Currentime;
	
public:
	bool IsFinish;
	CTexture* texture;
	RECT GetRect();
	int GetmapId() { return MapId; }
	void SetmapId(int id) { MapId = id; CurrentFrame = texture->AnimationList[State].at(MapId); }
	int GetState() { return State;}
	void SetState(int S);
	int GetCurrentFrame() { return MapId; }
	void SelectFrame(int ID) { CurrentFrame = texture->AnimationList[State].at(ID - 1); }
	void Next();
	CSprite(CTexture* tex);
	void Draw(float x, float y, int Direc, int alpha=255);
	void DrawBoard(float x, float y);
	void DrawItem(float x, float y);
	
};

typedef CSprite* LPSPRITE;

/*
	Manage sprite database
*/
#include "Sprites.h"


RECT CSprite::GetRect()
{
	return CurrentFrame;
}

void CSprite::SetState(int S)
{
	//DebugOut(L"%d\n", S);
	State = S;  
	MapId = 0; 
	IsFinish = false;	
	CurrentFrame = texture->AnimationList[State].at(MapId); 
	TimeAni = texture->TimeperAni.at(State - 1).at(MapId); //lay thoi gian chuyen frame cua tung frame 
	LastFrameTime = GetTickCount64();
	return;
}


void CSprite::Next()
{
	MapId++;
	if (MapId == texture->AnimationList[State].size())
		MapId = 0;
	CurrentFrame = texture->AnimationList[State].at(MapId);
}

CSprite::CSprite(CTexture* tex)
{
	this->texture = tex;
	TotalTime = 0;
	MapId = 0;
	State = 1;//state mac dinh 
	TimeAni = 100;
	CurrentFrame = texture->AnimationList[State].at(0);
	LastFrameTime = GetTickCount64();
	IsFinish = false;
}

void CSprite::Draw(float x, float y, int Direc, int alpha)
{
	CurrentFrame = texture->AnimationList[State].at(MapId);
	DWORD now = GetTickCount64();
	TimeAni = texture->TimeperAni.at(State - 1).at(MapId);
	if ((now - LastFrameTime >= TimeAni))
	{
		LastFrameTime = now;
		MapId++;
		if (MapId == texture->AnimationList[State].size())
		{
			MapId = 0;
			IsFinish = true;
		}
	}
	CGame* game = CGame::GetInstance();
	if(Direc<0)
		game->Draw(x, y, texture->GetTex(), CurrentFrame, alpha);
	else
		game->DrawFilpX(x, y, texture->GetTex(), CurrentFrame, CurrentFrame.right - CurrentFrame.left, alpha);
}

void CSprite::DrawBoard(float x, float y)
{
	CGame* game = CGame::GetInstance();
	game->Draw(x, y-80, texture->GetTex(),CurrentFrame);
}

void CSprite::DrawItem(float x, float y)
{
	CGame* game = CGame::GetInstance();
	game->Draw(x, y - 80, texture->GetTex(), texture->AnimationList[1].at(0));
}


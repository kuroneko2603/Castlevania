#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Sprites.h"
#include "Camera.h"
using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

struct CCollisionEvent
{
	LPGAMEOBJECT obj;  //thong tin doi tuong
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny; 
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)  //kiem tra xem obj nao va cham truoc 
	{
		if(a->t < b->t)
			return true;
		return false;
	}
};

class CGameObject
{
protected:
	float x, Start_x;
	float y, Start_y;
	int Damage;
	float vy;
	float vx;
	int ID;
	float dx;
	float dy;
	DWORD dt;
	int Direc;
	int Hiden;
	int Health, Backup_health;
	int State;
	int GridL, GridR, GridT, GridB;
	CTexture* Texture;
	GType type;
	CSprite* sprite;
	bool IsGetHit;
	bool Activate;
	int Score;
	int w, h;
	DWORD TdeActivate;
public:
	bool DeadByOutcam;
	bool CanReborn;
	bool InGrid;
	CGameObject();
	~CGameObject();
	void SetPosition(float X, float Y) { this->Start_x = X; this->Start_y = Y; this->x = X, this->y = Y; }
	void GetPosition(float& X, float& Y) { X = this->x;  Y = this->y; }
	float GetX() { return x; }
	float GetY() { return y; }
	bool GetActivate() { return Activate; }
	int GetDirec() { return Direc; }
	void SetDirection(int d) { Direc = d; }
	void SetID(int id) { ID = id; }
	int GetID() { return ID; }
	void SetSize(int W, int H) { w = W; h = H; }
	virtual int GetW(){return w;}
	virtual int GetH() { return h; }
	void SetHiden(int Hid) { Hiden = Hid; }
	int GetHiden(){return Hiden;}
	int GetScore() { return Score; }
	void AddScore(int Scr) { Score += Scr; }
	CTexture* GetTex() { return Texture; }
	void GetSpeed(float& VX, float& VY){VX = vx;VY = vy;}
	void SetSpeed(float VX, float VY){vx = VX;vy = VY;}
	bool GetIsGethit() { return IsGetHit; }
	void SetState(int S) { State = S; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);
	bool isCollisionWithObj(CGameObject *obj);
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>*coObj=NULL);
	virtual void Render(Camera *cam);
	void RenderBBox(Camera *cam);
	GType GetType() { return type; }
	void GetStartInfo(float& Sx, float& Sy) { Sx = Start_x; Sy = Start_y; }
	virtual void SetIsGetHit(bool IH) { IsGetHit = IH; }
	CSprite* GetSprite() { return sprite; }
	int GetHealth() { return Health; }
	virtual void SubHealth(int Dame) { Health -= Dame; IsGetHit = true; if (Health <= 0) TdeActivate = GetTickCount64(); }
	virtual void SetHealth(int H) { Health = H; }
	virtual void Reborn(int S = 0) 
	{
		Health = 1;
		Activate = false;
		x = Start_x;
		y = Start_y;
	}
	bool ObjIsInCamera(Camera* cam);
	int GetDamage() { return Damage; }
	void SetGridPos(int GL, int GR, int GT, int GB)
	{
		GridL = GL;
		GridR = GR;
		GridT = GT;
		GridB = GB;
	}
	void GetGridPos(int& GL, int& GR, int& GT, int& GB)
	{
		GL = GridL;
		GR = GridR;
		GT = GridT;
		GB = GridB;
		if (Health <= 0)
		{
			GL = (int)(Start_x / CellW);
			GR = (int)((Start_x + w) / CellW);
			GT = (int)(Start_y / CellH);
			GB = (int)((Start_y + h) / CellH);
		}
	}
	void UpdateGridPos()
	{
		GridL = (int)(x / CellW);
		GridR = (int)((x + w) / CellW);
		GridT = (int)(y / CellH);
		GridB = (int)((y + h) / CellH);
	}
	DWORD GetTdeAvtivate() { return TdeActivate; }
};
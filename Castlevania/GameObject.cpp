#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	DeadByOutcam = false;
	Hiden = 0;
	Direc = 1;
	Health = 1;
	Score = 0;
	State = 1;
	vx = 0; vy = 0;
	x = 0; y = 320;
	InGrid = false;
	IsGetHit = false;
	CanReborn = false;
}

void CGameObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x+5;
	top = this->y;
	right = left +this->GetW()-5;
	bottom = top + this->GetH();
}

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

void CGameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)//co the va cham trong frame ke tiep
			coEvents.push_back(e);
		else
			delete e;
	}

	sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);//sap xep thu tu cac obj va cham 
}

void CGameObject::FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny)
{
	min_tx = 1.0f;  //sau khi qua sweepAABB neu t>0 & t<1 thi co va cham t<0 thi ko va cham
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) 
		{
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0) 
		{
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);  //neu xay ra va cham tuc la trong cOEvent co obj thoa man thi lay obj do cho vao de xu ly
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

bool CGameObject::isCollisionWithObj(CGameObject* obj)	// kt  AABB + Sweept AABB
{
	if (obj == NULL)
		return false;
	else
	{
		float l1, l2, b1, b2, r1, r2, t1, t2;
		this->GetBoundingBox(l1, t1, r1, b1);
		obj->GetBoundingBox(l2, t2, r2, b2);
		if (CGame::GetInstance()->CheckAABB(l1, t1, r1, b1, l2, t2, r2, b2))
			return true;
		LPCOLLISIONEVENT e = SweptAABBEx(obj);
		bool res = e->t > 0 && e->t <= 1.0f;
		SAFE_DELETE(e);
		return res;
	}
}

void CGameObject::Update(DWORD dt, vector <LPGAMEOBJECT>* coObj)
{	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

void CGameObject::Render(Camera * cam)
{
	if (sprite->GetState() != State)
	{
		sprite->SetState(State);
	}
	float xCam = cam->PossInCamera(x, y).x;
	float yCam = cam->PossInCamera(x, y).y;
	if (Health >= 1)
		this->sprite->Draw(xCam, yCam, Direc);
}

void CGameObject::RenderBBox(Camera * cam)
{
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = r - l;
	rect.bottom = b - t;
	float xCam = cam->PossInCamera(x, y).x;
	float yCam = cam->PossInCamera(x, y).y;
	if(Direc==-1)
		CGame::GetInstance()->Draw(xCam,yCam,CTextures::GetInstance()->GetTexture(GType::BBOX)->GetTex(),rect);
	else
		CGame::GetInstance()->DrawFilpX(xCam,yCam,CTextures::GetInstance()->GetTexture(GType::BBOX)->GetTex(),rect, rect.right- rect.left);
}
bool CGameObject::ObjIsInCamera(Camera* cam)
{
	//DebugOut(L"Check cam\n");
	float xCam = cam->PossInCamera(x, y).x;
	float yCam = cam->PossInCamera(x, y).y;
	return ((xCam <= SCREEN_WIDTH+20 && (xCam +this->GetW()) >= -10) && (yCam<=400 && (yCam+this->GetH())>=-10));
}
CGameObject::~CGameObject()
{
	SAFE_DELETE(sprite);
}
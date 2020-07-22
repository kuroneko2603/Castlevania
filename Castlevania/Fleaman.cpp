#include "Fleaman.h"

Fleaman::Fleaman(simon *S)
{
	type = GType::FLEAMAN;
	Texture = CTextures::GetInstance()->GetTexture(GType::FLEAMAN);
	sprite = new CSprite(Texture);
	Health = 1;
	Simon = S;
	Esc = false;
	RangeLeft = RangeRight = 200;
	Step = 0;
	CanReborn = true;
	Score = 200;
	ReadyTime = 0;
	nHit = 0;
	IsAttacking = false;
	IsJumping = false;
	Activate = false;
	HitBrick = false;
	AtkSimon = false;
	IsReturn = false;
	Ready = false;
	SetSize(32, 26);
	checkBrick = true;
}

void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	DWORD now = GetTickCount64();
	if (Simon->GetX() < x + RangeRight && Simon->GetX() > x - RangeLeft)
	{
		if (!Activate) 
		{
			Activate = true;
			IsAttacking = true;
			State = 2;
		}
	}
	if (!IsJumping && Activate)
	{
		vy = -0.1f;
		vx = Direc * 0.2f;
		IsJumping = true;
	}
	if (IsAttacking)
	{
		//waiting
		vy = 0.2f;
		vx = 0;
		if (Simon->GetX() > x)
			Direc = 1;
		else
			Direc = -1;
		if (!Ready)
		{
			//DebugOut(L"??\n");
			ReadyTime = now;
			Ready = true;
			vx = 0;
			vy = 0.2f;
		}
		if (now - ReadyTime >= 500 )
		{
			//finish waiting
			AtkSimon = true;
			Ready = false;
			IsJumping = true;
			vx = CalSpeed();
			if (!IsReturn)
				vy = -0.36f;
			else
				//atk again
				vy = -0.2f;
			IsAttacking = false;
		}
	}
	CGameObject::Update(dt);
	if (IsJumping || IsReturn)
		vy += 0.001f * dt;
	else
		if(!HitBrick)
			vy += 0.005f * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObject, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		if(ny!=-1 || !IsJumping)
			y += min_ty * dy + ny * 0.4f;
		if (nx != 0)
		{
			if (!HitBrick)
			{
				HitBrick = true;
				Backup_y = y - 5.0f;
				x += Direc*5;
				TimeHitBrick = now;
			}
			if (HitBrick && now - TimeHitBrick > 200)
			{
				IsJumping = true;
				vy = -0.4f;
				IsAttacking = false;
			}
			else
			{
				y = Backup_y;
				State = 3;
			}
		}
		if (ny == -1)
		{
			if (nx == 0)
			{
				HitBrick = false;
			}
			if (IsJumping)
				IsJumping = false;
			if (AtkSimon && !IsJumping)
			{
				IsJumping = true;
				vy = -0.35f;
				vx = Direc * 0.17f;
				AtkSimon = false;
			}
			if (!IsAttacking && nHit <= 3 && abs(x - Simon->GetX()) >= 100 && Activate)
			{
				Activate = false;
				Direc = -Direc;
				IsAttacking = true;
				IsReturn = true;
				nHit++;
				ReadyTime = now;
			}
		}
		else
			y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	for (UINT i = 0; i < coObject->size(); i++)
	{
		float l1, l2, b1, b2, r1, r2, t1, t2;
		this->GetBoundingBox(l1, t1, r1, b1);
		coObject->at(i)->GetBoundingBox(l2, t2, r2, b2);
		if (CGame::GetInstance()->CheckAABB(l1, t1, r1, b1, l2, t2, r2, b2))
		{
			if (now - TimeHitBrick > 200)
			{
				x +=Direc* 10;
				y -= 20;
				TimeHitBrick = now;
			}
			else
			{
				vx = 0;
				vy = 0;
			}			
		}
	}
	if (y < 0)
	{
		Health--;
	}
}

float Fleaman::CalSpeed()
{
	float a = 0.128f;
	float b = -5.632f;
	float c = -1 * abs(y - Simon->GetY());
	float delta = b * b - 4 * a * c;
	if ((abs(x - Simon->GetX()) - 20) / ((-1 * b + sqrt(delta)) / (2 * a)) / 16.0f>0.2f)
		return Direc * 0.2f;
	else
		return Direc*(abs(x - Simon->GetX()) - 20) / ((-1 * b + sqrt(delta)) / (2 * a)) / 16.0f;
}

void Fleaman::Render(Camera* cam)
{
	if (sprite->GetState() != State)
		sprite->SetState(State);
	CGameObject::Render(cam);
}

void Fleaman::Reborn(int S)
{
	DebugOut(L"Reborn %f\n", Start_y);
	State = 1;
	Health = 1;
	Esc = false;
	RangeLeft = RangeRight = 200;
	Step = 0;
	CanReborn = true;
	x = Start_x;
	Hiden = 0;
	vx = 0;
	vy = 0;
	y = Start_y - 20;
	Score = 200;
	ReadyTime = 0;
	nHit = 0;
	IsAttacking = false;
	IsJumping = false;
	Activate = false;
	HitBrick = false;
	AtkSimon = false;
	IsReturn = false;
	Ready = false;
	checkBrick = true;
}

Fleaman::~Fleaman()
{
}

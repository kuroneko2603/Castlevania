#include "Skeleton.h"

Skeleton::Skeleton(simon* S)
{
	//DebugOut(L"Im Skeleton\n");
	Simon = S;
	Damage = 1;
	Health = 1;
	//Direc = -1;
	Score = 200;
	RangeLeft = 150;
	RangeRight = 150;
	IsAutoGo = false;
	CanReborn= true;
	State = 1;
	vy = ENEMY_GRAVITY;
	type = GType::SKELETON;
	Texture = CTextures::GetInstance()->GetTexture(GType::SKELETON);
	SetSize(30, 64);
	sprite = new CSprite(Texture);
}

void Skeleton::Attack()
{
	IsAttacking = true;
	State = 2;
	sprite->SetState(2);
	vx = Direc*ENEMY_SPEED;
	vy =-ENEMY_JUMP_SPEED;
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((Simon->GetX() > (this->x - RangeLeft)) && (this->x + RangeRight > Simon->GetX()) && !IsJumping)
	{
		Activate = true;
		if (!IsAttacking)
		{
			
			Backup_x = x;
			IsAttacking = true;
			if (State != 2)
			{
				State = 2;
			}
			
		}
	}
	if (((Simon->GetX() < (this->x - RangeLeft)) || (this->x + RangeRight < Simon->GetX()))&& !IsJumping)
	{
		if (Simon->GetX() < (this->x - RangeLeft))
		{
			Direc = -1;
			vx = -ENEMY_SPEED;
		}
		if (this->x + RangeRight < Simon->GetX())
		{
			Direc = 1;
			vx = 0.18f;
		}
		IsAttacking = false;
	}
	if (IsAttacking)
	{
		if (GetTickCount64() - LastTimeAtk >= RTime * 800)
		{
			srand(time(NULL));
			RTime = rand() % 2 + 1;
			LastTimeAtk = GetTickCount64();
			Bone* bone = new Bone(Simon, CalvxForBone(), 0.36, x, y);
			LstBone.push_back(bone);
		}
	}
	if (IsAttacking && !IsJumping)
	{
		if (Simon->GetX() < this->x)
			Direc = -1;
		else
			Direc = 1;
	}

		if (Direc == 1 && (Simon->GetX() - this->x) > 130 && IsAttacking && !IsJumping)
		{
			vx = Direc * 0.09f;
			IsAttacking = false;
			AutoGoDistance = abs(Simon->GetX() - x) - 130 + 45;
			IsAutoGo = true;
			Backup_x = x;
		}
		else
			if (Direc == -1 && (this->x - Simon->GetX()) > 130 && IsAttacking && !IsJumping)
			{
				vx = Direc * 0.09f;
				IsAttacking = false;
				AutoGoDistance = abs(Simon->GetX() - x)- 130 + 45;
				IsAutoGo = true;
				Backup_x = x;
			}
		if (Direc == 1 && (Simon->GetX() - this->x) < 90 && IsAttacking && !IsJumping)
		{
			vx =  -0.09f;
			IsAttacking = false;
			AutoGoDistance = 90 - abs(Simon->GetX() - x) + 45;
			IsAutoGo = true;
			Backup_x = x;
		}
		else
			if (Direc == -1 && (this->x - Simon->GetX()) < 90 && IsAttacking && !IsJumping)
			{
				vx =  0.09f;
				IsAttacking = false;
				AutoGoDistance = 90 - abs(Simon->GetX() - x) + 45;
				IsAutoGo = true;
				Backup_x = x;
			}
	CGameObject::Update(dt);
	if (IsJumping)
		vy += ENEMY_GRAVITY_JUMP * dt;
	else
		vy += ENEMY_GRAVITY * dt;
	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i) != NULL)
			if (coObjects->at(i)->GetType() == GType::BRICK)
			{
				float l1, l2, b1, b2, r1, r2, t1, t2;
				this->GetBoundingBox(l1, t1, r1, b1);
				coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);
				if (CGame::GetInstance()->CheckAABB(l1, t1, r1, b1, l2, t2, r2, b2))
				{
					vy = -0.36;
					vx = Direc*ENEMY_SPEED;
				}
				listObject_Brick.push_back(coObjects->at(i));
			}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
		if (IsJumping == false)
		{
			//DebugOut(L"Jump\n");
			vy = -0.41f;
			IsJumping = true;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;		
		if (nx != 0)
		{
			if (!IsJumping)
				vx *= -1;
			if (IsJumping && vy == 0)
			{
			}
		}
		if (ny == -1)
		{
			y += min_ty * dy + ny * 0.005f;
			vy = 0.4f;
			IsJumping = false;
		}
		else
			y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
	if (IsAutoGo)
	{
		if (abs(x - Backup_x) >= AutoGoDistance)
			IsAutoGo = false;
	}
	for (int i = 0; i < LstBone.size(); i++)
		LstBone.at(i)->Update(dt);
	if (Activate && Health<=0)
		Sound::GetInstance()->Play(GSOUND::S_SKELETON, false);
}

void Skeleton::Render(Camera* cam)
{
	if (sprite->GetState() != State)
		sprite->SetState(State);
	for (int i = 0; i < LstBone.size(); i++)
		LstBone.at(i)->Render(cam);
	CGameObject::Render(cam);
}

float Skeleton::CalvxForBone()
{
	float a = 0.128f;
	float b = -5.632f;
	float c = -1 * abs(y - Simon->GetY());
	float delta = b * b - 4 * a * c;
	if(x<Simon->GetX())
		return (abs(x - Simon->GetX()) +5 ) / ((-1 * b + sqrt(delta)) / (2 * a)) / 16.0f;
	else
		return -1 * (abs(x - Simon->GetX())-20) / ((-1 * b + sqrt(delta)) / (2 * a)) / 16.0f;

}

void Skeleton::Reborn(int s)
{
	IsAutoGo = false;
	State = 1;
	vy = ENEMY_GRAVITY;
	vx = 0;
	IsAttacking = false;
	LastTimeAtk = 0;
	LstBone.clear();
	vx = 0;
	IsAutoGo = false;
	AutoGoDistance = RTime = 0;
	Activate = false;
	x = Start_x;
	y = Start_y;
	if (Simon->GetX() < this->x)
		Direc = -1;
	else
		Direc = 1;
}

Skeleton::~Skeleton()
{
}

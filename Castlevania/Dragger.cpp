#include "Dragger.h"

Dragger::Dragger()
{
	type = GType::DRAGGER;
	Damage = 1;
	TotalTime = 0;
	TimeExist = 8000;
	vx = DRAGGER_SPEED;
	vy = 0.12f;
	SetSize(32, 32);
	x = 0;
	y = 300;
	Texture = CTextures::GetInstance()->GetTexture(GType::DRAGGER);
	SetSize(DRAGGER_WIDTH, DRAGGER_HEIGHT);
	sprite = new CSprite(Texture);
}

Dragger::~Dragger()
{
}

void Dragger::AdjustPosition()
{
	if (Direc == -1)
	{
		this->x = x;
		this->y += 10;

	}
	else
	{
		this->x = x + 30;
		this->y += 10;
	}
}

void Dragger::Update(DWORD dt, vector<LPGAMEOBJECT>* ListEnemy, vector<LPGAMEOBJECT>* ListObj)
{
	if (IsFinish)
		return;
	else
	{
		x += vx * dt;
		for (int i = 0; i < ListEnemy->size(); i++)
		{
			if (ListEnemy->at(i) != NULL)
				if (isCollisionWithObj(ListEnemy->at(i)))
				{
					RandomItem(ListEnemy->at(i));
					ListEnemy->at(i)->SubHealth(Damage);
					IsFinish = true;
					return;
				}
		}
		for (int i = 0; i < ListObj->size(); i++)
		{
			if (ListObj->at(i) != NULL) {
				GType T = ListObj->at(i)->GetType();
				if (T != GType::BRICK && T != GType::HIDENOBJ && T != GType::STAIRTOP && T != GType::STAIRBOT && T != GType::SECRETBRICK)
					if (isCollisionWithObj(ListObj->at(i)))
					{
						RandomItem(ListObj->at(i));
						ListObj->at(i)->SubHealth(Damage);
						IsFinish = true;
						return;
					}
			}
		}
	}
}

void Dragger::Update(DWORD dt, vector<LPGAMEOBJECT>* ListObj)
{
	CGameObject::Update(dt);
	TotalTime += dt;
	if (TotalTime >= TimeExist)
	{
		SubHealth(1);
		return;
	}
	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < ListObj->size(); i++)
		if (ListObj->at(i) != NULL)
			if (ListObj->at(i)->GetType() == GType::BRICK)
				listObject_Brick.push_back(ListObj->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Dragger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = left + GetW() - 10;
	bottom = top + GetH();
}

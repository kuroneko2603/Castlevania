#include "Simon.h"

simon::simon(Camera* camera)
{
	vx = 0;
	vy = 0;
	Step = 0;
	Live = 3;
	Health = 16;
	Next_x = 0;
	Next_d = 1;
	HStage = 1;
	Next_y = 240;
	HeartCollect = 5;
	State = SIMON_IDLE;
	IsAutoGo = false;
	IsOnStair = false;
	Invisible = false;
	GetDoubleShot = false;
	UseStopWatch = false;
	OutStair = false;
	IsFinishTele = true;
	Score = HStage = HObj = 0;
	IsCollideWithStairBot = false;
	IsCollideWithStairTop = false;
	IsUpStair = IsDownStair = false;
	DirecDownStair = DirecUpStair = 0;
	SetSize(SIMON_BBWIDTH, SIMON_BBHEIGHT);
	Texture = CTextures::GetInstance()->GetTexture(GType::SIMON);
	IsWalking = IsAttacking = IsJumping = IsSitting = IsGetHigh = false;
	MapWeapon[GType::MORNINGSTAR] = new Morningstar();
	MapWeapon[GType::DRAGGER] = new Dragger();
	MapWeapon[GType::CROSS] = new Cross();
	MapWeapon[GType::THROWINGAXE] = new ThrowingAxe();
	MapWeapon[GType::STOPWATCH] = new StopWatch();
	MapWeapon[GType::HOLYWATER] = new HolyWater();
	TypeWeapon = GType::MORNINGSTAR;
	SubWeapon = GType::MORNINGSTAR;
	sprite = new CSprite(Texture);
	type = GType::SIMON;
	this->cam = camera;
	Direc = 1;
	CalTime();
}

simon::~simon()
{
}

void simon::SetHinfo(int S, int H)
{
	HStage = S;
	HObj = H;
}

void simon::Tele()
{

	x = Next_x;
	y = Next_y;
	if (!IsOnStair)
	{
		if (Direc < 0) vx = SIMON_WALK_SPEED;
		else vx = -SIMON_WALK_SPEED;
		Direc = Next_d;
	}
	cam->SetPosition(Next_x, 0.0f);
	cam->Update(1);
	IsFinishTele = false;
	if (!IsOnStair)
		SetSimonState(GState::STOP);
	if (IsJumping)
		y -= 40;
}

void simon::CollectSubWeapon(GType Sw)
{
	SubWeapon = Sw;
}

void simon::GetHidenObjinfo(int& S, int& H)
{
	S = HStage;
	H = HObj;
	IsCollideWithHobj = false;
}

void simon::SetSimonState(GState state)
{
	switch (state)
	{
	case GState::WALK:
	{
		vx = SIMON_WALK_SPEED * Direc;
		this->IsWalking = true;
		break;
	}
	case GState::JUMP:
	{
		if (IsJumping || IsSitting || IsAttacking)
			return;
		vy = -SIMON_JUMP_SPEED;
		IsJumping = true;
		IsSitting = false;
		break;
	}
	case GState::STOP:
	{
		if (IsAttacking || IsJumping)
			return;
		vx = 0;
		if (IsSitting && !IsCollideWithStairTop)//avoid overlapping
		{
			y -= PULL_UP;
		}
		IsSitting = false;
		IsWalking = false;
		break;
	}
	case GState::SIT:
	{
		if (IsSitting)
			return;
		else
		{
			if (!IsCollideWithStairTop) {
				//DebugOut(L"Sitting\n");
				y -= PULL_UP;
			}
		}
		IsWalking = false;
		IsSitting = true;
		break;
	}
	case GState::ATTACK:
	{
		if (IsOnStair && Step == 2)
			Step = 0;
		if (IsOnStair && Step != 0)
			return;
		if (!IsJumping)
			IsWalking = false;
		//xu ly bi lech toa do khi danh tren thang
		if (IsOnStair)
		{
			vx = 0;
			vy = 0;
			if (abs(x - Backup_x) > 8)
			{
				Backup_x += Direc * 16;
				if (y < Backup_y)
					Backup_y -= 16;
				else
					Backup_y += 16;
				x = Backup_x;
				y = Backup_y;
			}
			else
			{
				y = Backup_y;
				x = Backup_x;
			}

		}
		IsAttacking = true;
		break;
	}
	case GState::ONSTAIR:
	{
		if (IsCollideWithStairBot)
		{
			//DebugOut(L"Onstair bot\n");
			Direc = DirecUpStair;
			IsCollideWithStairBot = false;
		}
		IsOnStair = true;
		Backup_x = x;
		Backup_y = y;
		if (AutoGo_Distance != 0)
		{
			IsOnStair_Backup = true;
			IsOnStair = false;
			IsAutoGo = true;
			break;
		}
		if (Direc != DirecUpStair)
		{
			y += 22;
			//x += Direc * 16;
			Backup_x = x;
			Backup_y = y;
		}
		vx = 0; vy = 0;
		break;
	}
	case GState::HIDEFACE:
	{
		State = SIMON_HIDEFACE;
		return;
	}
	case GState::DOWNSTAIR:
	{
		IsOnStair = true;
		Backup_x = x;
		Backup_y = y;
		if (AutoGo_Distance != 0)
		{
			IsOnStair_Backup = true;
			IsOnStair = false;
			IsAutoGo = true;
			vy = 0;
			break;
		}
		if (IsCollideWithStairTop)
		{
			y = AutoGo_Destination_y + 8;
			//DebugOut(L"y= %f\n", y);
			Direc = -DirecDownStair;
			IsCollideWithStairTop = false;
		}

		if (Direc != DirecDownStair)
		{
			//y += 16;
			//x += Direc * 16;
			Backup_x = x;
			Backup_y = y;
		}
		vx = 0; vy = 0;
		break;
	}
	}
}


void simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x + 12;
	top = this->y;
	right = left + GetW() - 20;
	if ((IsJumping && !IsAttacking && vy < 0.1f) || (IsSitting))
		bottom = top + SIMON_SITTING_BBOX;
	else
		bottom = top + SIMON_BBHEIGHT;
}

void simon::CalTime()
{
	TimeOnStair = 0;
	TimeFromLAtk = 0;
	AtkTime = 0;
	TimeForSubWeapon = 0;
	GethighTime = 0;
	for (int i = 0; i < sprite->texture->TimeperAni.at(SIMON_ATTACK - 1).size(); i++)
		AtkTime += sprite->texture->TimeperAni.at(SIMON_ATTACK - 1).at(i);
	for (int i = 0; i < sprite->texture->TimeperAni.at(SIMON_ATTACK - 1).size() - 1; i++)
		TimeForSubWeapon += sprite->texture->TimeperAni.at(SIMON_ATTACK - 1).at(i);
	for (int i = 0; i < sprite->texture->TimeperAni.at(SIMON_GETHIGH - 1).size(); i++)
		GethighTime += sprite->texture->TimeperAni.at(SIMON_GETHIGH - 1).at(i);
}

void simon::SwitchWeapon()
{
	DWORD now = GetTickCount64();
	if (now - TimeUseSubWeapon <= 500)
	{
		TypeWeapon = GType::MORNINGSTAR;
		return;
	}
	if (MapWeapon[GType::MORNINGSTAR]->GetIsFinish() == false)
	{
		TypeWeapon = GType::MORNINGSTAR;
		return;
	}
	if (MapWeapon[SubWeapon]->GetIsFinish() == false)
	{
		if (GetDoubleShot)
		{
			if (SubWeapon == GType::DRAGGER && HeartCollect > 0)
			{
				if (WeaponDShot == NULL || WeaponDShot->GetType() != DRAGGER)
					WeaponDShot = new Dragger();
				if (WeaponDShot->GetIsFinish() == true)
				{
					HeartCollect--;
					WeaponDShot->Attack(x, y, Direc);
					TimeUseSubWeapon = now;
					return;
				}
			}
			if (SubWeapon == GType::CROSS && HeartCollect > 0)
			{
				if (WeaponDShot == NULL || WeaponDShot->GetType() != CROSS)
					WeaponDShot = new Cross();
				if (WeaponDShot->GetIsFinish() == true) {
					HeartCollect--;
					WeaponDShot->Attack(x, y, Direc);
					TimeUseSubWeapon = now;
					return;
				}
			}
			if (SubWeapon == GType::THROWINGAXE && HeartCollect > 0)
			{
				if (WeaponDShot == NULL || WeaponDShot->GetType() != GType::THROWINGAXE)
					WeaponDShot = new ThrowingAxe();
				if (WeaponDShot->GetIsFinish() == true) {
					HeartCollect--;
					WeaponDShot->Attack(x, y, Direc);
					TimeUseSubWeapon = now;
					return;
				}
			}
		}
		TypeWeapon = GType::MORNINGSTAR;
		return;
	}
	else
	{
		TimeUseSubWeapon = now;
		if (SubWeapon == GType::DRAGGER && HeartCollect > 0)
		{
			HeartCollect--;
			TypeWeapon = SubWeapon;
			return;
		}
		if (SubWeapon == GType::CROSS && HeartCollect > 0)
		{
			HeartCollect--;
			TypeWeapon = SubWeapon;
			return;
		}
		if (SubWeapon == GType::STOPWATCH && HeartCollect > 2)
		{
			HeartCollect -= 2;
			TStopWatch = GetTickCount64();
			UseStopWatch = true;
		}
		if (SubWeapon == GType::THROWINGAXE && HeartCollect > 0)
		{
			HeartCollect--;
			TypeWeapon = SubWeapon;
			return;
		}
		if (SubWeapon == GType::HOLYWATER && HeartCollect > 0)
		{
			HeartCollect--;
			TypeWeapon = SubWeapon;
			return;
		}
		else
			TypeWeapon = GType::MORNINGSTAR;
	}
	return;
}

void simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj, vector<LPGAMEOBJECT>* coEnemy, vector<LPGAMEOBJECT>* coItem)
{
	DWORD now = GetTickCount64();
	if (IsDie)
	{
		if (now - TDie <= 2000)
			return;
		else
		{
			IsDie = false;
			IsReborn = true;
			return;
		}
	}
	if (UseRosary && now - TRosary >= 50)
	{
		UseRosary = false;
	}
	if (Invisible && now - TInvisible >= 5000)
	{
		Sound::GetInstance()->Play(GSOUND::S_IPOTIONEND, false);
		Invisible = false;
	}
	if (UseStopWatch && now - TStopWatch >= 6000)
	{
		UseStopWatch = false;
	}
	vector<LPGAMEOBJECT> list_Brick;
	list_Brick.clear();
	for (UINT i = 0; i < coObj->size(); i++)
		if (coObj->at(i) != NULL) {
			coObj->at(i)->InGrid = false;
			if (coObj->at(i)->GetType() == GType::BRICK || coObj->at(i)->GetType() == GType::ELEVATOR || coObj->at(i)->GetType() == GType::SECRETBRICK)
			{
				list_Brick.push_back(coObj->at(i));
				if (coObj->at(i)->GetType() == GType::ELEVATOR)
				{
					LPCOLLISIONEVENT e = SweptAABBEx(coObj->at(i));
					bool res = e->t > 0 && e->t <= 1.0f;
					if (res && vx == 0) {
						float tmp;
						coObj->at(i)->GetSpeed(vx, tmp);
					}
				}
			}
			else
			{
				if (coObj->at(i)->GetType() == GType::HIDENOBJ && !IsGetHurt && coObj->at(i)->GetDirec() == Direc)
				{
					if (isCollisionWithObj(coObj->at(i)))
					{
						IsCollideWithHobj = true;
						HidenObj* tmpobj = static_cast<HidenObj*>(coObj->at(i));
						if (tmpobj->GetStage() < GType::CROWN)
						{
							tmpobj->GetSimonPosition(Next_x, Next_y, Next_d);//next position
							SetHinfo(tmpobj->GetStage(), tmpobj->GetHiden());
						}
						else
						{
							SetHinfo(tmpobj->GetStage(), tmpobj->GetHiden());
							tmpobj->GetBonusInfo(Bonus_x, Bonus_y, Bonus_type);
							coObj->at(i)->SubHealth(1);
						}
					}
				}
				if (coObj->at(i)->GetType() == GType::STAIRBOT && !IsJumping)
				{
					float l1, l2, b1, b2, r1, r2, t1, t2;
					this->GetBoundingBox(l1, t1, r1, b1);
					coObj->at(i)->GetBoundingBox(l2, t2, r2, b2);
					bool res = CGame::GetInstance()->CheckAABB(l1, t1, r1, b1, l2, t2, r2, b2);
					if (res)
					{
						BotId = i;
						if (!IsOnStair && IsUpStair)
						{
							//DebugOut(L"%d %d\n", Direc, DirecOnStair);
							DirecUpStair = coObj->at(i)->GetDirec();
							IsCollideWithStairBot = true;
							if (!IsAutoGo)
							{
								AutoGo_Distance = coObj->at(i)->GetX() - x;
								AutoGo_Destination = coObj->at(i)->GetX() - 27;
							}
						}
						if (IsDownStair && DirecDownStair == coObj->at(i)->GetDirec())
						{
							//DebugOut(L"Correct2\n");
							Backup_x = x;
							Backup_y = y;
							IsDownStair = false;
							IsCollideWithStairTop = false;
							IsOnStair = false;
							IsWalking = false;
							DirecDownStair = 0;
							DirecDownStair = 0;
							vy = 99999;
							y += -10;
							Step = 0;
							OutStair = true;
						}
					}
					else
						if (BotId == i)
							IsCollideWithStairBot = false;
				}
				if (coObj->at(i)->GetType() == GType::STAIRTOP && !IsJumping)
				{
					float l1, l2, b1, b2, r1, r2, t1, t2;
					this->GetBoundingBox(l1, t1, r1, b1);
					coObj->at(i)->GetBoundingBox(l2, t2, r2, b2);
					if (CGame::GetInstance()->CheckAABB(l1, t1, r1, b1, l2, t2, r2, b2))
					{
						if (IsSitting) {
							IsSitting = false;
							y += PULL_UP;
						}
						TopId = i;
						if (!IsOnStair && IsDownStair)
						{
							//DebugOut(L"%d %d\n", Direc, DirecOnStair);
							AutoGo_Destination_y = coObj->at(i)->GetY();
							DirecDownStair = coObj->at(i)->GetDirec();
							IsCollideWithStairTop = true;
							if (!IsAutoGo)
							{
								if (coObj->at(i)->GetDirec() == 1) {
									AutoGo_Distance = coObj->at(i)->GetX() - x;
									AutoGo_Destination = coObj->at(i)->GetX() - 6;
								}
								else {
									AutoGo_Distance = coObj->at(i)->GetX() - x + 33;
									AutoGo_Destination = coObj->at(i)->GetX();
								}
							}
						}

						if (IsUpStair && DirecUpStair == coObj->at(i)->GetDirec())
						{
							//DebugOut(L"correct\n");
							Backup_x = x;
							Backup_y = y;
							IsUpStair = false;
							IsCollideWithStairBot = false;
							IsOnStair = false;
							IsWalking = false;
							vy = 99999;
							y += -10;
							DirecUpStair = 0;
							DirecDownStair = 0;
							Step = 0;
							OutStair = true;
						}


					}
					else
						if (TopId == i)
							IsCollideWithStairTop = false;
				}

			}
			//	DebugOut(L"%d %d\n", DirecDownStair, DirecUpStair);
		}
	if (IsAutoGo)
	{
		//DebugOut(L"go\n");
		IsWalking = true;
		State = SIMON_WALK;
		if (AutoGo_Distance < 0)
			Direc = -1;
		else
			Direc = 1;
		vx = Direc * SIMON_WALK_SPEED;
		//di qua khoang cach
		if (Direc == -1 && (x + vx * dt < AutoGo_Destination))
		{
			x = AutoGo_Destination;
			//DebugOut(L"left\n");
		}
		if (Direc == 1 && (x + vx * dt > AutoGo_Destination))
		{
			x = AutoGo_Destination;
			//DebugOut(L"right\n");
		}
		if (x == AutoGo_Destination)
		{
			IsAutoGo = false;
			AutoGo_Distance = 0;
			IsWalking = false;
			if (IsOnStair_Backup)
			{
				if (IsUpStair)
					SetSimonState(GState::ONSTAIR);
				else
					SetSimonState(GState::DOWNSTAIR);
			}
		}
	}
	else
		if (IsOnStair)
		{
			//DebugOut(L"Stair\n");
			if (!IsFinishTele) {
				Backup_x = x;
				Backup_y = y;
			}
			if (IsAttacking)
			{
				if (State != SIMON_UP_STAIR_ATTACK && State != SIMON_DOWN_STAIR_ATTACK)
				{
					if (IsDownStair)
						State = SIMON_DOWN_STAIR_ATTACK;
					if (IsUpStair)
						State = SIMON_UP_STAIR_ATTACK;
					TimeFromLAtk = GetTickCount64();
					if (TypeWeapon == GType::MORNINGSTAR)
						MapWeapon[TypeWeapon]->Attack(this->x, this->y, this->Direc);
				}
				else
					if (GetTickCount64() - TimeFromLAtk >= AtkTime)
					{
						IsAttacking = false;
						if (IsUpStair)
							State = SIMON_UP_STAIR_IDLE;
						if (IsDownStair)
							State = SIMON_DOWN_STAIR_IDLE;
						MapWeapon[GType::MORNINGSTAR]->SetFinish(true);
					}
					else
						if (GetTickCount64() - TimeFromLAtk >= TimeForSubWeapon)
							if (TypeWeapon != GType::MORNINGSTAR && MapWeapon[GType::MORNINGSTAR]->GetIsFinish() == true)
								MapWeapon[TypeWeapon]->Attack(this->x, this->y, this->Direc);
			}
			else
				if (IsWalking == true)
				{
					if (Step == 1)
					{
						if (IsUpStair)
						{
							State = SIMON_UP_STAIR;
						}
						if (IsDownStair)
						{
							State = SIMON_DOWN_STAIR;
						}
					}
					if (Step == 2)
					{
						if (IsUpStair)
						{
							State = SIMON_UP_STAIR_IDLE;
						}
						if (IsDownStair)
						{
							State = SIMON_DOWN_STAIR_IDLE;
						}
					}
					if (abs(x - Backup_x) >= 8.0f && Step == 1)
						Step++;
					if ((abs(x - Backup_x) >= 16 || abs(y - Backup_y) >= 16) && IsFinishTele)
					{
						Step++;
						if (IsUpStair)
						{
							x -= DirecUpStair * (abs(x - Backup_x) - 16.0f);
							y += (abs(y - Backup_y) - 16.0f);
						}
						if (IsDownStair)
						{
							x += DirecDownStair * (abs(x - Backup_x) - 16.0f);
							y -= (abs(y - Backup_y) - 16.0f);
						}
						Backup_y = y;
						Backup_x = x;
						if (FirstStep) {
							FirstStep = false;
						}
					}
				}
				else
				{
					if (IsUpStair)
						State = (SIMON_UP_STAIR_IDLE);
					else
						if (!FirstStep)
							State = SIMON_DOWN_STAIR_IDLE;
						else
							State = SIMON_DOWN_STAIR;
				}
		}
		else {
			if (IsGetHigh)
			{
				Backup_x = x;
				Backup_y = y;
				IsWalking = IsAttacking = IsSitting = IsJumping = false;//dg high thi ko dc lam gi :v
				if (State != SIMON_GETHIGH)
				{
					Timegethigh = GetTickCount64();
					State = SIMON_GETHIGH;
				}
				if (GetTickCount64() - Timegethigh >= GethighTime)
				{
					IsGetHigh = false;
					State = SIMON_IDLE;
				}
			}
			else
				if (IsGetHurt)
				{
					IsWalking = IsJumping = IsAttacking = IsSitting = false;
					if (State != SIMON_HURT)
					{
						State = SIMON_HURT;
						if (!IsJumping)
							vy = -SIMON_VY_HURT;
					}
					vx = -Direc * 0.14f;
				}
				else
					if (IsAttacking)
					{
						if (IsSitting)
						{
							if (State != SIMON_JUMP_ATTACK)
							{
								State = SIMON_JUMP_ATTACK;
								TimeFromLAtk = GetTickCount64();
								if (TypeWeapon == GType::MORNINGSTAR)
									MapWeapon[TypeWeapon]->Attack(this->x, this->y, this->Direc);
							}
							else
								if (GetTickCount64() - TimeFromLAtk >= AtkTime)
								{
									IsAttacking = false;
									State = SIMON_JUMP_STATE;
									MapWeapon[GType::MORNINGSTAR]->SetFinish(true);
								}
								else
								{
									if (GetTickCount64() - TimeFromLAtk >= TimeForSubWeapon)
									{
										if (TypeWeapon != GType::MORNINGSTAR && MapWeapon[GType::MORNINGSTAR]->GetIsFinish() == true)
										{
											MapWeapon[TypeWeapon]->Attack(this->x, this->y, this->Direc);
										}
									}
								}
						}
						else
						{
							if (State != SIMON_ATTACK)
							{
								State = SIMON_ATTACK;
								TimeFromLAtk = GetTickCount64();
								if (TypeWeapon == GType::MORNINGSTAR)
									MapWeapon[TypeWeapon]->Attack(this->x, this->y, this->Direc);
							}
							else
								if (GetTickCount64() - TimeFromLAtk >= AtkTime)
								{
									IsAttacking = false;
									State = SIMON_IDLE;
									MapWeapon[GType::MORNINGSTAR]->SetFinish(true);
								}
								else
								{
									if (GetTickCount64() - TimeFromLAtk >= 240)
									{
										if (TypeWeapon != GType::MORNINGSTAR && MapWeapon[GType::MORNINGSTAR]->GetIsFinish() == true)
										{
											MapWeapon[TypeWeapon]->Attack(this->x, this->y, this->Direc);
										}
									}
								}
						}
					}
					else
					{
						if (IsSitting)
						{
							if (IsJumping || IsAttacking)
								return;
							else
							{
								State = SIMON_JUMP_STATE;
								vy = 9999.0f;//ngoi ngay moi dep
							}
						}
						else
						{
							if (IsWalking)
							{
								if (IsJumping)
								{
									if (vy < 0.16f)
										State = SIMON_JUMP_STATE;
									else
										State = SIMON_IDLE;
								}
								else
								{
									if (State != SIMON_WALK)
										State = SIMON_WALK;
								}
							}
							else
								if (IsJumping)
								{
									if (vy < 0.18f)
										State = SIMON_JUMP_STATE;
									else
										State = SIMON_IDLE;
								}
								else
								{
									State = SIMON_IDLE;
								}
						}
					}
		}
	if (!IsGetHigh)
	{
		dx = vx * dt;
		dy = vy * dt;
		if (IsJumping || (IsGetHurt && !IsOnStair))
			vy += SIMON_GRAVITY_JUMP * dt;
		else
			if (!IsOnStair)
				vy += SIMON_GRAVITY * dt;

		//Xet va cham 
		vector <LPCOLLISIONEVENT> coEvents;
		vector <LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		if (!IsOnStair)
			CalcPotentialCollisions(&list_Brick, coEvents);
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{

			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			if (nx != 0)
			{
				//vx = 0;
			}
			if (!IsSitting)
			{
				//DebugOut(L"Not\n");
				x += min_tx * dx + nx * 0.4f;
			}
			if (ny == -1)
			{
				y += min_ty * dy + ny * 0.4f;
				if (!OutStair && !IsOnStair)
					vy = SIMON_GRAVITY * dt;
			}
			else {
				y += dy;
			}
			if (ny == -1)
			{
				if (IsJumping)//dg nhay cham dat thi dung lai 
				{
					IsJumping = false;
				}
				if (IsGetHurt)
				{
					//DebugOut(L"F gethurt\n");
					IsGetHurt = false;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	//simon phai o trong camera
	float Cam_BL, Cam_BR, Cam_BT, Cam_BB;
	this->cam->GetBoundary(Cam_BL, Cam_BR, Cam_BT, Cam_BB);
	if (x <= cam->GetX() - 10.0f)
		x = cam->GetX() - 10.0f;
	if (x >= Cam_BR + SCREEN_WIDTH - 50)
		x = Cam_BR + SCREEN_WIDTH - 50;
	if (y > 1000)
	{
		Health = 0;
		IsGetHurt = false;
		vx = 0; vy = 0;
	}
	//update va cham item
	for (UINT i = 0; i < coItem->size(); i++)
		if (coItem->at(i) != NULL && !IsAttacking)
			if (isCollisionWithObj(coItem->at(i)))
			{
				switch (coItem->at(i)->GetType())
				{
				case GType::UPGRADEWEAPON:
				{
					if (!IsJumping) {
						Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
						MapWeapon[GType::MORNINGSTAR]->Upgrade();
						IsGetHigh = true;
						coItem->at(i)->SubHealth(1);
						coItem->at(i) = NULL;
						break;
					}
				}
				case GType::HEART:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTHEART, false);
					HeartCollect += 1;
					break;
				}
				case GType::BIGHEART:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTHEART, false);
					HeartCollect += 5;
					break;
				}
				case GType::DOUBLESHOT:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
					if (SubWeapon != GType::MORNINGSTAR)
						GetDoubleShot = true;
					break;
				}
				case GType::TRIPLESHOT:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
					break;
				}
				case GType::CROWN:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
					Score += 2000;
					break;
				}
				case GType::TREASURE:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
					Score += 1000;
					break;
				}
				case GType::MAGICCRYSTAL:
				{
					Sound::GetInstance()->Stop(GSOUND::S_BOSS);
					Sound::GetInstance()->Play(GSOUND::S_STAGECLEAR, false);
					GameOver = true;
					break;
				}
				case GType::ROSARY:
				{
					Sound::GetInstance()->Play(GSOUND::S_ROSARY, false);
					UseRosary = true;
					TRosary = now;
					break;
				}
				case GType::FORKCHOP:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
					Health += 6;
					if (Health > 16)
						Health = 16;
					break;
				}
				case GType::MONEYBAG:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
					Score += 200;
					break;
				}
				case GType::IPOTION:
				{
					Sound::GetInstance()->Play(GSOUND::S_IPOTIONSTART, false);
					Invisible = true;
					TInvisible = now;
					break;
				}
				default:
				{
					Sound::GetInstance()->Play(GSOUND::COLLECTITEM, false);
					if (coItem->at(i)->GetType() != SubWeapon)
					{
						if (GetDoubleShot)
							GetDoubleShot = false;
						MapWeapon[SubWeapon]->SetHitTime(0);
					}
					GType Sw = coItem->at(i)->GetType();
					CollectSubWeapon(Sw);
					break;
				}
				}
				if (coItem->at(i) != NULL && coItem->at(i)->GetType() != GType::UPGRADEWEAPON)
				{
					coItem->at(i)->SubHealth(1);
					coItem->at(i) = NULL;
				}
			}
	if (Step == 3)
	{
		Step = 0;
		vx = 0;
		vy = 0;
		IsWalking = false;
	}
	if (OutStair)
		OutStair = false;
	if (!IsFinishTele)
		IsFinishTele = true;
	//va cham quai 
	for (int i = 0; i < coEnemy->size(); i++)
	{
		if (coEnemy->at(i) != NULL )
		{
			coEnemy->at(i)->InGrid = false;
			if (isCollisionWithObj(coEnemy->at(i)) && !Invisible && coEnemy->at(i)->GetActivate())
			{
				Sound::GetInstance()->Play(GSOUND::S_HURT, false);
			/*	Health -= coEnemy->at(i)->GetDamage();
				Invisible = true;
				TInvisible = now;
				MapWeapon[GType::MORNINGSTAR]->SetFinish(true);
				if (!IsOnStair)
				{
					IsGetHurt = true;
					SetSimonState(STOP);
				}
				MapWeapon[GType::MORNINGSTAR]->SetFinish(true);*/
			}
		}
	}
	if (Health <= 0 && !IsGetHurt)
	{
		vx = 0;
		vy = 0;
		State = SIMON_DEATH;
		Sound::GetInstance()->Play(GSOUND::LOSELIFE, false);
		IsDie = true;
		TDie = now;
		Die();
		return;
	}
	//update vu khi
	if (WeaponDShot != NULL)
	{
		WeaponDShot->Update(dt, coEnemy, coObj);
		if (isCollisionWithObj(WeaponDShot) && WeaponDShot->GetType() == GType::CROSS && WeaponDShot->Special)
			WeaponDShot->SetFinish(true);
	}
	for (auto& objWeapon : MapWeapon)
	{
		if (objWeapon.second->GetIsFinish() == false)
		{
			if (objWeapon.first == GType::MORNINGSTAR)
			{
				objWeapon.second->SetPosition(x, y);
				objWeapon.second->AdjustPosition();
			}
			objWeapon.second->Update(dt, coEnemy, coObj);
			if (isCollisionWithObj(objWeapon.second) && objWeapon.second->GetType() == GType::CROSS && objWeapon.second->Special)
			{
				objWeapon.second->SetFinish(true);
			}
		}
	}
}
void simon::AutoGo(DWORD dt)
{
	IsWalking = true;
	State = SIMON_WALK;
	if (AutoGo_Distance < 0)
		Direc = -1;
	else
		Direc = 1;
	x += Direc * 0.1 * dt;
	if (Direc == -1 && (x + vx * dt < AutoGo_Destination))
		x = AutoGo_Destination;
	if (Direc == 1 && (x + vx * dt > AutoGo_Destination))
		x = AutoGo_Destination;
	if (x == AutoGo_Destination)
	{
		IsAutoGo = false;
		AutoGo_Distance = 0;
		IsWalking = false;
		if (IsOnStair_Backup)
			if (IsUpStair)
				SetSimonState(GState::ONSTAIR);
			else
				SetSimonState(GState::DOWNSTAIR);
	}
}
void simon::Render(Camera* cam)
{
	if (sprite->GetState() != State)
		sprite->SetState(State);
	D3DXVECTOR3 p = cam->PossInCamera(x, y);
	if (!Invisible)
		sprite->Draw(p.x, p.y, Direc);
	else
		sprite->Draw(p.x, p.y, Direc, 180);
	if (WeaponDShot != NULL && WeaponDShot->GetIsFinish() == false)
		WeaponDShot->Render(cam);
	for (auto& objWeapon : MapWeapon)
	{
		if (objWeapon.second->GetIsFinish() == false)
		{
			objWeapon.second->Render(cam);
		}
	}
}

void simon::SetIsGetHurt(bool T)
{
	if (Invisible)
		return;
	Sound::GetInstance()->Play(GSOUND::S_HURT, false);
	Invisible = true;
	TInvisible = GetTickCount64();
	MapWeapon[GType::MORNINGSTAR]->SetFinish(true);
	if (!IsOnStair)
	{
		IsGetHurt = true;
		SetSimonState(STOP);
	}
	MapWeapon[GType::MORNINGSTAR]->SetFinish(true);
}

void simon::ReBorn(int St)
{
	DebugOut(L"Reborn\n");
	vx = 0;
	vy = 0;
	Step = 0;
	Health = 16;
	HeartCollect = 5;
	State = SIMON_IDLE;
	SubWeapon = GType::MORNINGSTAR;
	IsAutoGo = false;
	IsOnStair = false;
	Invisible = false;
	UseStopWatch = false;
	OutStair = false;
	IsJumping = false;
	IsFinishTele = true;
	IsGetHurt = IsGetHit = false;
	TypeWeapon = GType::MORNINGSTAR;
	SubWeapon = GType::MORNINGSTAR;
	Score = HStage = HObj = 0;
	IsCollideWithStairBot = false;
	IsAttacking = false;
	IsCollideWithStairTop = false;
	IsUpStair = IsDownStair = false;
	DirecDownStair = DirecUpStair = 0;
	switch (St)
	{
	case 1:
		Next_x = 0;
		Next_y = 240;
		Next_d = 1;
		break;
	case 2:
		Next_x = 0;
		Next_y = 260;
		Next_d = 1;
		break;
	case 3:
		Next_x = 910;
		Next_y = 160;
		Next_d = -1;
		break;
	case 4:
		Next_x = 1472;
		Next_y = 240;
		Next_d = -1;
		break;
	case 5:
		Next_x = 78;
		Next_y = 252;
		Next_d = 1;
		break;
	case 6:
		Next_x = 0;
		Next_y = 80;
		Next_d = 1;
		break;
	default:
		break;
	}
	Tele();
	cam->SetIsFollowSimon(true);
	IsReborn = false;
}

void simon::Die()
{
	Health = 16;
	if (Live >= 1)
	{
		Live--;
		MapWeapon[GType::MORNINGSTAR]->SetLv(0);
	}
	else
		GameOver = true;
}

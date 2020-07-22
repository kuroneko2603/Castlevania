#include "SceneGame.h"

SceneGame::SceneGame()
{
	cam = new Camera();
	Stage = 1;
	Simon = new simon(cam);
	grid = new Grid(Simon);
	nGhost = 3;
	map = new Map();
	LoadResources();
	TimeRemain = 300;
	TotalTime = 0;
	SwitchStage = false;
	BossStage = false;
	Sound::GetInstance()->Play(GSOUND::S_SCENE, true);
	Ghost* ghost1 = new Ghost();
	ghost1->SetPosition(10, 250);
	Ghost* ghost2 = new Ghost();
	ghost2->SetPosition(50, 250);
	Ghost* ghost3 = new Ghost();
	ghost3->SetPosition(90, 250);
	ListGhost.push_back(ghost1);
	ListGhost.push_back(ghost2);
	ListGhost.push_back(ghost3);
}

SceneGame::~SceneGame()
{
}

void SceneGame::KeyState(BYTE* state)
{
	if (BossStage)
		return;
	if (Simon->IsGetHigh)
		return;
	if (Simon->IsJumping && Simon->IsWalking)//dg nhay thi ko xet phim 
		return;
	if (Simon->IsGetHurt)
		return;
	if (Simon->IsAttacking)//dg tan cong ko xet phim
	{
		float VX, VY;
		Simon->GetSpeed(VX, VY);
		Simon->SetSpeed(0, VY);
		return;
	}
	if (!Simon->IsJumping)
		if (CGame::GetInstance()->IsKeyDown(DIK_UP) && Simon->IsAttacking == false)
		{
			Simon->IsDownStair = false;
			Simon->IsUpStair = true;
			if (!Simon->IsOnStair) //chua len thang
			{
				//DebugOut(L"up stair\n");
				if (Simon->IsCollideWithStairBot)
				{
					Simon->SetSimonState(GState::ONSTAIR);
				}
			}
			else //len thang r
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (Simon->DirecUpStair == 0)
					{
						Simon->DirecUpStair = Simon->DirecDownStair;
						Simon->DirecDownStair = 0;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() != Simon->DirecUpStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					Simon->SetDirection(Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, -0.07f);
				}
			}
		}
		else
			if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) && Simon->IsAttacking == false)
			{
				Simon->IsUpStair = false;
				Simon->IsDownStair = true;
				if (!Simon->IsOnStair)
				{

					if (Simon->IsCollideWithStairTop)
					{
						//DebugOut(L"go down %d\n", Simon->DirecDownStair);
						Simon->FirstStep = true;
						Simon->IsDownStair = true;
						Simon->SetSimonState(GState::DOWNSTAIR);
					}
				}
				else
				{
					if (Simon->Step == 0 || Simon->Step == 3)
					{
						if (Simon->DirecDownStair == 0)
						{
							if (Simon->DirecUpStair == 0)
								return;
							Simon->DirecDownStair = Simon->DirecUpStair;
						}
						Simon->DirecUpStair = 0;
						Simon->IsWalking = true;
						Simon->Step = 1;
						if (Simon->GetDirec() == Simon->DirecDownStair)
						{
							//	DebugOut(L"Direc change\n");
							Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
							Simon->Backup_Position();
						}
						Simon->SetDirection(-Simon->DirecDownStair);
						Simon->SetSpeed(Simon->GetDirec() * 0.07f, 0.07f);
					}
				}
			}
	if (CGame::GetInstance()->IsKeyDown(DIK_LEFT) && Simon->IsOnStair)
	{
		if (Simon->IsUpStair)
		{
			if (Simon->DirecUpStair == 1)
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsDownStair)
					{
						Simon->IsUpStair = false;
						Simon->IsDownStair = true;
						Simon->DirecDownStair = Simon->DirecUpStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() == Simon->DirecDownStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					if (!Simon->IsUpStair)
						Simon->SetDirection(-1 * Simon->DirecDownStair);
					else
						Simon->SetDirection(-Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, 0.07f);
				}
			}
			else
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsUpStair)
					{
						Simon->IsUpStair = true;
						Simon->IsDownStair = false;
						Simon->DirecUpStair = Simon->DirecDownStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() != Simon->DirecUpStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					Simon->SetDirection(Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, -0.07f);
				}
			}
		}
		else
		{
			if (Simon->DirecDownStair == 1)
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsDownStair)
					{
						Simon->IsUpStair = false;
						Simon->IsDownStair = true;
						Simon->DirecDownStair = Simon->DirecUpStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() == Simon->DirecDownStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					if (!Simon->IsUpStair)
						Simon->SetDirection(-1 * Simon->DirecDownStair);
					else
						Simon->SetDirection(-Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, 0.07f);
				}
			}
			else
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsUpStair)
					{
						Simon->IsUpStair = true;
						Simon->IsDownStair = false;
						Simon->DirecUpStair = Simon->DirecDownStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() != Simon->DirecUpStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					Simon->SetDirection(Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, -0.07f);
				}
			}
		}
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT) && Simon->IsOnStair)
	{
		if (Simon->IsUpStair)
		{
			if (Simon->DirecUpStair == -1)
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsDownStair)
					{
						Simon->IsUpStair = false;
						Simon->IsDownStair = true;
						Simon->DirecDownStair = Simon->DirecUpStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() == Simon->DirecDownStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					if (!Simon->IsUpStair)
						Simon->SetDirection(-1 * Simon->DirecDownStair);
					else
						Simon->SetDirection(-Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, 0.07f);
				}
			}
			else
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsUpStair)
					{
						Simon->IsUpStair = true;
						Simon->IsDownStair = false;
						Simon->DirecUpStair = Simon->DirecDownStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() != Simon->DirecUpStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					Simon->SetDirection(Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, -0.07f);
				}
			}
		}
		else
		{
			if (Simon->DirecDownStair == -1)
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsDownStair)
					{
						Simon->IsUpStair = false;
						Simon->IsDownStair = true;
						Simon->DirecDownStair = Simon->DirecUpStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() == Simon->DirecDownStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					if (!Simon->IsUpStair)
						Simon->SetDirection(-1 * Simon->DirecDownStair);
					else
						Simon->SetDirection(-Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, 0.07f);
				}
			}
			else
			{
				if (Simon->Step == 0 || Simon->Step == 3)
				{
					if (!Simon->IsUpStair)
					{
						Simon->IsUpStair = true;
						Simon->IsDownStair = false;
						Simon->DirecUpStair = Simon->DirecDownStair;
					}
					Simon->IsWalking = true;
					Simon->Step = 1;
					if (Simon->GetDirec() != Simon->DirecUpStair)
					{
						Simon->SetPosition(Simon->GetBackup_x() + Simon->GetDirec() * 10, Simon->GetBackup_y());
						Simon->Backup_Position();
					}
					Simon->SetDirection(Simon->DirecUpStair);
					Simon->SetSpeed(Simon->GetDirec() * 0.07f, -0.07f);
				}
			}
		}
	}
	if (Simon->IsOnStair)
		return;
	if (Simon->IsAutoGo)
		return;
	if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) && !Simon->IsJumping && !Simon->IsCollideWithStairTop)
		Simon->SetSimonState(SIT);
	else
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			Simon->SetDirection(-1);
			Simon->SetSimonState(GState::WALK);
		}
		else
			if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
			{
				Simon->SetDirection(1);
				Simon->SetSimonState(GState::WALK);
			}
			else
			{
				if (!Simon->IsOnStair)
					Simon->SetSimonState(GState::STOP);
			}


}

void SceneGame::OnKeyDown(int KeyCode)
{
	if (BossStage)
		return;
	if (Simon->IsAutoGo)
		return;
	if (Simon->IsGetHigh)
		return;
	if (Simon->IsGetHurt)
		return;
	if (Simon->IsAttacking)
		return;
	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(CGame::GetInstance()->GetWinHandler());
	if (Simon->IsWalking && Simon->IsJumping)
	{
		//return;
	}
	if (KeyCode == DIK_SPACE)
	{
		if (Simon->IsOnStair)
			return;
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT) || CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			//Simon->SetSimonState(GState::STOP);
			Simon->SetSimonState(GState::WALK);
		}
		Simon->SetSimonState(GState::JUMP);
		if (KeyCode == DIK_A)
			Simon->SetSimonState(GState::ATTACK);
	}
	if (KeyCode == DIK_A)
	{
		//DebugOut(L"Attack\n");
		if (CGame::GetInstance()->IsKeyDown(DIK_UP))
			Simon->SwitchWeapon();
		else
			Simon->UseMorningStar();
		Simon->SetSimonState(GState::ATTACK);
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_1))
	{
		Stage = 1;
		Simon->ReBorn(1);
		LoadResources();
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_2))
	{
		Stage = 2;
		Simon->ReBorn(2);
		LoadResources();
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_3))
	{
		Stage = 3;
		Simon->ReBorn(3);
		LoadResources();
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_4))
	{
		Stage = 4;
		Simon->ReBorn(4);
		LoadResources();
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_5))
	{
		Stage = 5;
		Simon->ReBorn(5);
		LoadResources();
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_6))
	{
		Stage = 6;
		Simon->ReBorn(6);
		LoadResources();
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_7))
	{
		int a = Simon->GetSubWeapon_Type();
		GType Sw;
		switch (a)
		{
		case 3:
			Sw = GType::DRAGGER;
			break;
		case 4:
			Sw = GType::HOLYWATER;
			break;
		case 5:
			Sw = GType::STOPWATCH;
			break;
		case 6:
			Sw = GType::THROWINGAXE;
			break;
		case 8:
			Sw = GType::CROSS;
			break;
		default:
			Sw = GType::DRAGGER;
			break;
		}
		Simon->CollectSubWeapon(Sw);
	}
	if (CGame::GetInstance()->IsKeyDown(DIK_8))
		Simon->SetHeartCollect(100);
}

void SceneGame::OnKeyUp(int KeyCode)
{
	if (BossStage)
		return;
	if (Simon->IsGetHurt) {
		return;
	}
	if (Simon->IsAttacking) {
		return;
	}
	if (Simon->IsOnStair)
		return;
	if (Simon->IsJumping)
		return;
	if (KeyCode == DIK_DOWN && !Simon->IsJumping && (Simon->IsDownStair && !Simon->IsCollideWithStairTop))
	{
		//DebugOut(L"Stop\n");
		Simon->SetSimonState(GState::STOP);
	}
}

void SceneGame::LoadResources()
{
	ListItem.clear();
	ListEnemy_S.clear();
	grid->ClearGrid();
	float simonX, simonY, camBL, camBR, camBT, camBB;
	map->SetMap(Stage);
	map->ReadMap(camBL, camBR, camBT, camBB, grid);
	//grid->OutFile();
	cam->SetBoundary(camBL, camBR, camBT, camBB);
	map->Drawmap(cam);
	Simon->Tele();
	float cx, cy;
	Simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2 - 40;
	cam->SetPosition(cx, 0.0f);
	if (cam->GetX() > camBR)
		cam->SetPosition(camBR, 0);
	grid->GetListObj1(ListObj, ListEnemy, cam);
	TimeRemain = 300;
	Sound::GetInstance();
}

void SceneGame::InitGame()
{
}

void SceneGame::Update(DWORD dt)
{
	if (Simon->UseRosary)
		Change_background = true;
	else
		Change_background = false;
	if (Simon->IsCollideWithHobj)
	{
		int tmpS;
		int HObj;
		Simon->GetHidenObjinfo(tmpS, HObj);
		if (tmpS < GType::CROWN) {
			DebugOut(L"Switch\n");
			Stage = tmpS;
			SwitchStage = true;
			LoadResources();
			return;
		}
		else
		{
			float Bx, By;
			int BType;
			Simon->GetBonusInfo(Bx, By, BType);
			ListItem.push_back(grid->GetNewObj(BType, 1, Bx, By));
		}
	}
	if (Simon->IsReborn)
	{
		Simon->ReBorn(Stage);
		LoadResources();
	}
	ListObj_S.clear();
	List_Brick.clear();
	for (UINT i = 0; i < ListObj.size(); i++)
	{
		if (ListObj[i] != NULL)
		{
			if (ListObj[i]->GetIsGethit())
			{
				if (ListObj[i]->GetType() != GType::HIDENOBJ) {
					Hit* hit = new Hit(ListObj[i]->GetX() + 14, ListObj[i]->GetY() + 4);
					ListEffect.push_back(hit);
				}
			}
			if (ListObj[i]->GetHealth() > 0) {
				ListObj[i]->Update(dt);
				if (ListObj[i]->GetType() == GType::BRICK)
					List_Brick.push_back(ListObj[i]);
			}
			else
			{
				if (ListObj[i]->GetType() != GType::HIDENOBJ) {
					Burn* burn = new Burn(ListObj[i]->GetX() + 8, ListObj[i]->GetY() + 6);
					BrokenBrick* bb = new BrokenBrick(ListObj[i]->GetX() + 8, ListObj[i]->GetY() + 6);
					if (ListObj[i]->GetType() != GType::SECRETBRICK)
						ListEffect.push_back(burn);
					else
						ListEffect.push_back(bb);
					if (ListObj[i]->GetHiden() != 0)
					{
						ListItem.push_back(grid->GetNewObj(ListObj[i]->GetHiden(), 1, ListObj[i]->GetX(), ListObj[i]->GetY() + 5));
					}
				}
				ListObj[i] = NULL;
			}
		}
	}
	for (UINT i = 0; i < ListEnemy.size(); i++)
	{
		if (ListEnemy[i] != NULL)
		{
			if (ListEnemy[i]->GetIsGethit())
			{
				Hit* hit = new Hit(ListEnemy[i]->GetX() + 4, ListEnemy[i]->GetY() + 4);
				ListEnemy[i]->SetIsGetHit(false);
				if (boss == NULL && ListEnemy[i]->GetType() == GType::BIGBAT)
				{
					boss = ListEnemy[i];
					board->SetBoss(boss);
				}
				ListEffect.push_back(hit);
			}
			if (Simon->UseRosary)
				ListEnemy[i]->SetHealth(0);
			if (ListEnemy[i]->GetHealth() > 0)
			{
				//DebugOut(L"no\n");
				if (!Simon->UseStopWatch && !Simon->IsGetHigh)
				{
					GType T = ListEnemy[i]->GetType();
					ListEnemy[i]->Update(dt, &List_Brick);
					ListEnemy[i]->UpdateGridPos();
					if (!ListEnemy[i]->ObjIsInCamera(cam) && ListEnemy[i]->GetActivate() && T != GType::KNIGHT)
					{
						//DebugOut(L"Out cam\n");
						ListEnemy[i]->DeadByOutcam = true;
						ListEnemy[i]->SetHealth(0);
					}
					if (ListEnemy[i] != NULL)
						grid->push_backGrid(ListEnemy[i]);
				}
			}
			else
			{
				GType type = ListEnemy[i]->GetType();
				if (!ListEnemy[i]->DeadByOutcam)
				{
					Simon->AddScore(ListEnemy[i]->GetScore());
					Burn* burn = new Burn(ListEnemy[i]->GetX() + 8, ListEnemy[i]->GetY() + 6);
					ListEffect.push_back(burn);
					if (ListEnemy[i]->GetHiden() != 0)
					{
						ListItem.push_back(grid->GetNewObj(ListEnemy[i]->GetHiden(), 1, ListEnemy[i]->GetX(), ListEnemy[i]->GetY() - 10));
					}
				}
				float Sx, Sy;
				int l, r, t, b;
				int id = ListEnemy[i]->GetID();
				ListEnemy[i]->GetGridPos(l, r, t, b);
				ListEnemy[i]->GetStartInfo(Sx, Sy);
				if (type != GType::GHOST)
				{
					ListEnemy_S.push_back(grid->GetNewObj(type, id, Sx, Sy, 1, 1, 1, 0, l, r, t, b));
					ListEnemy[i] = NULL;
				}
				else
				{
					nGhost--;
					DebugOut(L"%d\n", nGhost);
					ListEnemy[i] = NULL;
					tCreate = GetTickCount64();
				}
			}
		}
	}
	if (Stage != 6)
		for (UINT i = 0; i < ListEnemy_S.size(); i++)
		{
			if (ListEnemy_S[i] != NULL)
				if (!ListEnemy_S[i]->ObjIsInCamera(cam) && ListEnemy_S[i]->GetType() != GType::GHOST)
				{
					float Sx, Sy;
					int l, r, t, b;
					ListEnemy_S[i]->GetGridPos(l, r, t, b);
					ListEnemy_S[i]->GetStartInfo(Sx, Sy);
					grid->push_backGrid(grid->GetNewObj(ListEnemy_S[i]->GetType(), ListEnemy_S[i]->GetID(), Sx, Sy, 1, 1, 1, 0, l, r, t, b));
					ListEnemy_S[i] = NULL;
				}
		}
	else
	{
		if (nGhost < 3 && GetTickCount64()- tCreate>1000 && Simon->GetX()<1020)
		{
			DebugOut(L"Create ghost\n");
			Ghost* ghost = new Ghost();
			float vx, vy, y;
			y = 250;
			Simon->GetSpeed(vx, vy);
			if (vx >= 0)
			{
				if (Simon->GetX() <= 320)
				{
					srand(time(NULL));
					int result = rand() % 10 + 1;
					if (result < 7)
						y = 250.0f;
					else
						y = 150.0f;
				}
				ghost->SetPosition(cam->GetX()+510, y);
				ghost->SetDirection(-1);
			}
			else
			{
				ghost->SetPosition(cam->GetX(), y);
				ghost->SetDirection(1);
			}
			ghost->SetID(10);
			ListEnemy.push_back(ghost);
			grid->push_backGrid(ghost);
			nGhost++;
			tCreate = GetTickCount64();
		}
	}
	for (UINT i = 0; i < ListItem.size(); i++)
	{
		if (ListItem[i] != NULL)
			if (ListItem.at(i)->GetHealth() > 0)
			{
				ListItem.at(i)->Update(dt, &List_Brick);
			}
			else
			{
				if (ListItem[i]->GetType() != GType::MAGICCRYSTAL)
					ListItem.at(i) = NULL;
			}
	}
	for (UINT i = 0; i < ListEffect.size(); i++)
		if (ListEffect.at(i)->getFinish() == false)
			ListEffect.at(i)->Update(dt);
	Simon->Update(dt, &ListObj, &ListEnemy, &ListItem);
	float cx, cy;
	Simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2 - 40;
	if (Stage == 6 && Simon->GetX() >= 1020 && !cam->ReachDes)
	{

		BossStage = true;
		Simon->SetSimonState(GState::STOP);
		cam->AutoGoStart(1024 - cam->GetX());
	}
	if (BossStage && cam->ReachDes)
	{
		Sound::GetInstance()->Stop(GSOUND::S_SCENE);
		BossStage = false;
		Sound::GetInstance()->Play(GSOUND::S_BOSS, true);
	}
	if (cam->GetIsFollowSimon())
		cam->SetPosition(cx, 0.0f);
	cam->Update(dt);
	grid->GetListObj1(ListObj, ListEnemy, cam);
	TotalTime += dt;
	if (TotalTime >= 1000 && TimeRemain > 0)
	{
		TimeRemain--;
		TotalTime -= 1000;
	}
	if (Simon->Getlive() == 0 || Simon->GameOver)
	{
		Sound::GetInstance()->Stop(GSOUND::S_SCENE);
		SceneManager::GetInstance()->SetScene(new SceneIntro());
	}
}
void SceneGame::Render()
{
	map->Drawmap(cam);
	for (UINT i = 0; i < ListObj.size(); i++)
		if (ListObj[i] != NULL)
			ListObj[i]->Render(cam);
	for (UINT i = 0; i < ListItem.size(); i++)
		if (ListItem.at(i) != NULL) {
			ListItem.at(i)->Render(cam);
		}
	Simon->Render(cam);
	/*if(Stage==6)
		for (UINT i = 0; i < 3; i++)
			ListGhost[i]->Render(cam);*/
	for (UINT i = 0; i < ListEnemy.size(); i++)
		if (ListEnemy[i] != NULL)
			ListEnemy[i]->Render(cam);
	for (UINT i = 0; i < ListEffect.size(); i++)
		if (ListEffect.at(i)->getFinish() == false)
			ListEffect.at(i)->Render(cam);
	board->Render(Simon, TimeRemain, Stage);
}

#include "Grid.h"

void Grid::push_backGrid(LPGAMEOBJECT obj, bool Check)
{
	int left;
	int right;
	int top;
	int bot;
	obj->GetGridPos(left, right, top, bot);
	ofs << obj->GetType() << " " << left << " " <<right<<" "<<top<<" "<<bot << "\n";
	if (obj->GetType() >= GType::GHOST && obj->GetType() <= GType::FLEAMAN) 
	{
		for (int i = left; i <= right; i++)
			for (int j = top; j <= bot; j++)
				moveObjGrid[i][j].push_back(obj);
	}
	else
	{
		if (obj->GetType() == GType::BRICK)
			for (int i = left; i <= right; i++)
				for (int j = top; j<= bot; j++)
				{
					unMoveObjGrid[i][j].push_back(obj);
				}
		else
			unMoveObjGrid[left][top].push_back(obj);

	}
}

void Grid::GetListObj1(vector<CGameObject*>& LstObj, vector<CGameObject*>& LstEnemy, Camera* cam)
{
	int top = (int)(cam->GetY() / CellH);
	int bottom = (int)((cam->GetY() + SCREEN_HEIGHT) / CellH);
	int left = (int)((cam->GetX() - 30) / CellW);
	int right = (int)((cam->GetX() + SCREEN_WIDTH) / CellW);
	if (top == backup_top && bottom == backup_bot && left == backup_left && right == backup_right)
		return;
	backup_top = top;
	backup_bot = bottom;
	backup_left = left;
	backup_right = right;
	LstObj.clear();
	LstEnemy.clear();
	for (int i = left; i <= right; i++) {
		for (int j = top; j < bottom; j++)
		{
			for (int k = 0; k < unMoveObjGrid[i][j].size(); k++)
			{
				if (unMoveObjGrid[i][j].at(k) != NULL && unMoveObjGrid[i][j].at(k)->GetHealth() > 0)
				{
					if (!unMoveObjGrid[i][j].at(k)->InGrid) {
						LstObj.push_back(unMoveObjGrid[i][j].at(k));
						unMoveObjGrid[i][j].at(k)->InGrid = true;
					}
				}
			}
			for (int k = 0; k < moveObjGrid[i][j].size(); k++)
			{
				if (moveObjGrid[i][j].at(k) != NULL && moveObjGrid[i][j].at(k)->GetHealth() > 0)
				{
					int X = (int)(moveObjGrid[i][j].at(k)->GetX() / CellW);
					if (!moveObjGrid[i][j].at(k)->InGrid)
					{
						LstEnemy.push_back(moveObjGrid[i][j].at(k));
						moveObjGrid[i][j].at(k)->InGrid = true;
					}
				}
			}
			moveObjGrid[i][j].clear();
		}
	}
}

void Grid::InsertGrid(int type,int id, float x, float y, int w, int h, int d, int HidenObj, int l, int r, int t, int b)
{
	CGameObject* object = GetNewObj(type,id, x, y, w, h, d, HidenObj,l,r,t,b);
	if (object == NULL)
		return;
	push_backGrid(object);
}

void Grid::Update(DWORD dt, Camera* cam)
{
	int top = (int)(cam->GetY() / CellH);
	int bottom = (int)((cam->GetY() + SCREEN_HEIGHT) / CellH);
	int left = (int)(cam->GetX() / CellW);
	int right = (int)((cam->GetX() + SCREEN_WIDTH) / CellW);
	if (top == top || bottom != backup_bot || left != backup_left || right != backup_right)
	{
		backup_top = top;
		backup_bot = bottom;
		backup_left = left;
		backup_right = right;
		LstBrick.clear();
		LstObj.clear();
		LstEnemy_Incam.clear();
		for (int i = left; i <= right; i++)
			for (int j = top; j < bottom; j++)
			{
				for (int k = 0; k < unMoveObjGrid[i][j].size(); k++)
				{
					if (unMoveObjGrid[i][j].at(k) != NULL)
					{
						if (unMoveObjGrid[i][j].at(k)->GetIsGethit())
						{
							Hit* hit = new Hit(unMoveObjGrid[i][j].at(k)->GetX() + 14, unMoveObjGrid[i][j].at(k)->GetY() + 4);
							LstEffect.push_back(hit);
						}
						if (unMoveObjGrid[i][j].at(k)->GetHealth() > 0)
						{
							unMoveObjGrid[i][j].at(k)->Update(dt);
							if (!unMoveObjGrid[i][j].at(k)->InGrid) {
								LstObj.push_back(unMoveObjGrid[i][j].at(k));
								unMoveObjGrid[i][j].at(k)->InGrid = true;
							}
							if (unMoveObjGrid[i][j].at(k)->GetType() == GType::BRICK)
								LstBrick.push_back(unMoveObjGrid[i][j].at(k));
						}
						else
						{
							Burn* burn = new Burn(unMoveObjGrid[i][j].at(k)->GetX() + 8, unMoveObjGrid[i][j].at(k)->GetY() + 6);
							LstEffect.push_back(burn);
							if (unMoveObjGrid[i][j].at(k)->GetHiden() != 0)
							{
								LstItem.push_back(GetNewObj(unMoveObjGrid[i][j].at(k)->GetHiden(),1, unMoveObjGrid[i][j].at(k)->GetX(), unMoveObjGrid[i][j].at(k)->GetY()));
							}
							unMoveObjGrid[i][j].at(k) = NULL;
						}
					}
				}
				for (int k = 0; k < moveObjGrid[i][j].size(); k++)
				{
					if (moveObjGrid[i][j].at(k) != NULL) {
						if (moveObjGrid[i][j].at(k)->GetIsGethit())
						{
							DebugOut(L"Hit\n");
							Hit* hit = new Hit(moveObjGrid[i][j].at(k)->GetX() + 14, moveObjGrid[i][j].at(k)->GetY() + 4);
							LstEffect.push_back(hit);
						}
						if (moveObjGrid[i][j].at(k)->GetHealth() > 0)
						{
							//DebugOut(L"%d\n", LstBrick.size());
							int X = (int)(moveObjGrid[i][j].at(k)->GetX() / CellW);
							if (moveObjGrid[i][j].at(k)->ObjIsInCamera(cam) && !moveObjGrid[i][j].at(k)->InGrid) {
								LstEnemy_Incam.push_back(moveObjGrid[i][j].at(k));
								moveObjGrid[i][j].at(k)->InGrid = true;
							}
							else
								moveObjGrid[i][j].at(k)->SubHealth(moveObjGrid[i][j].at(k)->GetHealth());
						}
						else {
							Burn* burn = new Burn(moveObjGrid[i][j].at(k)->GetX(), moveObjGrid[i][j].at(k)->GetY());
							LstEffect.push_back(burn);
							if (moveObjGrid[i][j].at(k)->GetHiden() != 0)
							{
								LstItem.push_back(GetNewObj(moveObjGrid[i][j].at(k)->GetHiden(),1, moveObjGrid[i][j].at(k)->GetX(), moveObjGrid[i][j].at(k)->GetY()));
							}
							moveObjGrid[i][j].at(k) = NULL;
						}
					}
				}
				moveObjGrid[i][j].clear();
			}
	}
	for (int k = 0; k < LstItem.size(); k++)
	{
		if (LstItem.at(k) != NULL) {
			if (LstItem.at(k)->GetHealth() > 0)
				LstItem.at(k)->Update(dt, &LstBrick);
			else
				LstItem.at(k) = NULL;
		}
	}
	for (int k = 0; k < LstEffect.size(); k++)
	{
		if (LstEffect.at(k)->getFinish() == false)
			LstEffect.at(k)->Update(dt);
	}
	//DebugOut(L"%d\n", LstItem.size());
	//DebugOut(L"%d\n", LstEnemy_Incam.size());
	Simon->Update(dt, &LstObj, &LstEnemy_Incam, &LstItem);
	for (int k = 0; k < LstEnemy_Incam.size(); k++)
	{
		LstEnemy_Incam.at(k)->Update(dt, &LstBrick);
		push_backGrid(LstEnemy_Incam.at(k));
	}
}

void Grid::Render(Camera* cam)
{
	for (UINT i = 0; i < LstObj.size(); i++)
		LstObj[i]->Render(cam);
	for (UINT i = 0; i < LstItem.size(); i++)
		if (LstItem.at(i) != NULL)
			LstItem.at(i)->Render(cam);
	Simon->Render(cam);
	for (UINT i = 0; i < LstEnemy_Incam.size(); i++)
		LstEnemy_Incam[i]->Render(cam);
	for (UINT i = 0; i < LstEffect.size(); i++)
		if (LstEffect.at(i)->getFinish() == false)
			LstEffect.at(i)->Render(cam);
}

CGameObject* Grid::GetNewObj(int type,int id, float x, float y, int w, int h, int d, int HiObj, int l, int r, int t, int b)
{
	LPGAMEOBJECT object;
	switch (type)
	{
	case GType::GHOST:
	{
		Ghost* ghost = new Ghost();
		ghost->SetPosition(x, y);
		ghost->SetDirection(d);
		ghost->SetID(id);
		ghost->SetGridPos(l, r, t, b);
		return ghost;
	}
	case GType::SECRETBRICK:
	{
		SecretBrick* brick = new SecretBrick(x, y, d);
		brick->SetHiden(HiObj);
		brick->SetID(id);
		brick->SetGridPos(l, r, t, b);
		return brick;
	}
	case GType::NOTHING:
	{
		return NULL;
	}
	case GType::TORCH:
	{
		Torch* torch = new Torch();
		torch->SetPosition(x, y);
		torch->SetHiden(HiObj);
		torch->SetID(id);
		torch->SetGridPos(l, r, t, b);
		return torch;
	}
	case GType::CANDLE:
	{
		Candle* candle = new Candle();
		candle->SetPosition(x, y);
		candle->SetHiden(HiObj);
		candle->SetID(id);
		candle->SetGridPos(l, r, t, b);
		return candle;
	}
	case GType::DRAGGER:
	{
		Dragger* dragger = new Dragger();
		dragger->SetPosition(x, y);
		dragger->SetID(id);
		dragger->SetGridPos(l, r, t, b);
		return dragger;
	}
	case GType::CROSS:
	{
		Cross* cross = new Cross();
		cross->SetPosition(x, y);
		cross->SetID(id);
		cross->SetGridPos(l, r, t, b);
		return cross;
	}
	case GType::STOPWATCH:
	{
		StopWatch* stopwatch = new StopWatch();
		stopwatch->SetPosition(x, y);
		stopwatch->SetID(id);
		stopwatch->SetGridPos(l, r, t, b);
		return stopwatch;
	}
	case GType::THROWINGAXE:
	{
		ThrowingAxe* throwingaxe = new ThrowingAxe();
		throwingaxe->SetPosition(x, y);
		throwingaxe->SetID(id);
		throwingaxe->SetGridPos(l, r, t, b);
		return throwingaxe;
	}
	case GType::HOLYWATER:
	{
		HolyWater* holywater = new HolyWater();
		holywater->SetPosition(x, y);
		holywater->SetID(id);
		holywater->SetGridPos(l, r, t, b);
		return holywater;
	}
	case GType::HEART:
	{
		Heart* heart = new Heart(1);
		heart->SetPosition(x, y);
		heart->SetID(id);
		heart->SetGridPos(l, r, t, b);
		return heart;
	}
	case GType::BIGHEART:
	{
		Heart* heart = new Heart(5);
		heart->SetPosition(x, y);
		heart->SetID(id);
		heart->SetGridPos(l, r, t, b);
		return heart;
	}
	case GType::DOUBLESHOT:
	{
		DoubleShot* doubleshot = new DoubleShot();
		doubleshot->SetPosition(x, y);
		doubleshot->SetID(id);
		doubleshot->SetGridPos(l, r, t, b);
		return doubleshot;
	}
	case GType::TRIPLESHOT:
	{
		TripleShot* tripleshot = new TripleShot();
		tripleshot->SetPosition(x, y);
		tripleshot->SetID(id);
		tripleshot->SetGridPos(l, r, t, b);
		return tripleshot;
	}
	case GType::ROSARY:
	{
		Rosary* rosary = new Rosary();
		rosary->SetPosition(x, y);
		rosary->SetID(id);
		rosary->SetGridPos(l, r, t, b);
		return rosary;
	}
	case GType::FORKCHOP:
	{
		ForkChop* forkchop = new ForkChop();
		forkchop->SetPosition(x, y);
		forkchop->SetID(id);
		forkchop->SetGridPos(l, r, t, b);
		return forkchop;
	}
	case GType::IPOTION:
	{
		InvisibilityPotion* ipotion = new InvisibilityPotion();
		ipotion->SetPosition(x, y);
		ipotion->SetID(id);
		ipotion->SetGridPos(l, r, t, b);
		return ipotion;
	}
	case GType::REDMONEYBAG:
	{
		MoneyBag* moneybag = new MoneyBag(1);
		moneybag->SetPosition(x, y);
		moneybag->SetID(id);
		moneybag->SetGridPos(l, r, t, b);
		return moneybag;
	}
	case GType::PURPLEMONEYBAG:
	{
		MoneyBag* moneybag = new MoneyBag(2);
		moneybag->SetPosition(x, y);
		moneybag->SetID(id);
		moneybag->SetGridPos(l, r, t, b);
		return moneybag;
	}
	case GType::WHITEMONEYBAG:
	{
		MoneyBag* moneybag = new MoneyBag(3);
		moneybag->SetPosition(x, y);
		moneybag->SetID(id);
		moneybag->SetGridPos(l, r, t, b);
		return moneybag;
	}
	case GType::MONEYBAG:
	{
		MoneyBag* moneybag = new MoneyBag(4);
		moneybag->SetPosition(x, y);
		moneybag->SetID(id);
		moneybag->SetGridPos(l, r, t, b);
		return moneybag;
	}
	case GType::MAGICCRYSTAL:
	{
		MagicCrystal* magiccrystal = new MagicCrystal();
		magiccrystal->SetPosition(1172, 72);
		magiccrystal->SetID(id);
		magiccrystal->SetGridPos(l, r, t, b);
		return magiccrystal;
	}
	case GType::UPGRADEWEAPON:
	{
		UpgradeWhip* upgradewhip = new UpgradeWhip();
		upgradewhip->SetPosition(x, y);
		upgradewhip->SetID(id);
		upgradewhip->SetGridPos(l, r, t, b);
		return upgradewhip;
	}
	case GType::BRICK:
	{
		Brick* brick = new Brick(w, h);
		brick->SetPosition(x, y);
		brick->SetID(id);
		brick->SetGridPos(l, r, t, b);
		return brick;
	}
	case GType::CROWN:
	{
		Crown* crown = new Crown();
		crown->SetPosition(x, y);
		crown->SetID(id);
		crown->SetGridPos(l, r, t, b);
		return crown;
	}
	case GType::TREASURE:
	{
		Treasure* treasure = new Treasure();
		treasure->SetPosition(x, y);
		treasure->SetID(id);
		treasure->SetGridPos(l, r, t, b);
		return treasure;
	}
	case GType::HIDENOBJ:
	{
		HidenObj* HObject = new HidenObj(w, h, d, HiObj);
		HObject->SetPosition(x, y);
		HObject->SetID(id);
		HObject->SetGridPos(l, r, t, b);
		return HObject;
	}
	case GType::STAIRBOT:
	{
		StairBottom* stairbot = new StairBottom();
		stairbot->SetPosition(x, y);
		stairbot->SetDirection(d);
		stairbot->SetID(id);
		stairbot->SetGridPos(l, r, t, b);
		return stairbot;
	}
	case GType::STAIRTOP:
	{
		StairTop* stairtop = new StairTop();
		stairtop->SetPosition(x, y);
		stairtop->SetDirection(d);
		stairtop->SetID(id);
		stairtop->SetGridPos(l, r, t, b);
		return stairtop;
	}
	case GType::SKELETON:
	{
		Skeleton* skeleton = new Skeleton(Simon);
		skeleton->SetPosition(x, y);
		skeleton->SetDirection(d);
		skeleton->SetHiden(HiObj);
		skeleton->SetID(id);
		skeleton->SetGridPos(l, r, t, b);
		return skeleton;
	}
	case GType::FLEAMAN:
	{
		Fleaman* fleaman = new Fleaman(Simon);
		fleaman->SetPosition(x, y);
		fleaman->SetDirection(d);
		fleaman->SetHiden(HiObj);
		fleaman->SetID(id);
		fleaman->SetGridPos(l, r, t, b);
		return fleaman;
	}
	case GType::KNIGHT:
	{
		Knight* knight = new Knight(Simon);
		knight->SetPosition(x, y);
		knight->SetDirection(d);
		knight->SetHiden(HiObj);
		knight->SetID(id);
		knight->SetGridPos(l, r, t, b);
		return knight;
	}
	case GType::RAVEN:
	{
		Raven* raven = new Raven(Simon);
		raven->SetPosition(x, y);
		raven->SetHiden(HiObj);
		raven->SetDirection(d);
		raven->SetID(id);
		raven->SetGridPos(l, r, t, b);
		return raven;
	}
	case GType::BAT:
	{
		Bat* bat = new Bat(Simon);
		bat->SetPosition(x, y);
		bat->SetHiden(HiObj);
		bat->SetDirection(d);
		bat->SetID(id);
		bat->SetGridPos(l, r, t, b);
		return bat;
	}
	case GType::BIGBAT:
	{
		BigBat* bat = new BigBat(Simon);
		bat->SetPosition(x, y);
		bat->SetHiden(HiObj);
		bat->SetDirection(d);
		bat->SetID(id);
		bat->SetGridPos(l, r, t, b);
		return bat;
	}
	case GType::ALIEN:
	{
		Alien* alien = new Alien(Simon);
		alien->SetPosition(x, y);
		alien->SetDirection(d);
		alien->SetHiden(HiObj);
		alien->SetID(id);
		alien->SetGridPos(l, r, t, b);
		return alien;
	}
	case GType::ELEVATOR:
	{
		Elevator* elevator = new Elevator();
		elevator->SetPosition(x, y);
		elevator->SetDirection(d);
		elevator->SetID(id);
		elevator->SetGridPos(l, r, t, b);
		return elevator;
	}
	}
	return NULL;
}

void Grid::ClearGrid()
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 100; j++) {
			cell[i][j].clear();
			moveObjGrid[i][j].clear();
			unMoveObjGrid[i][j].clear();
		}
	LstObj.clear();
	LstItem.clear();
	LstEffect.clear();
	LstEnemy_Incam.clear();
	backup_bot = backup_top = backup_left = backup_right = -1;
}
#pragma once
#include"Ghost.h"
#include "Skeleton.h"
#include"Heart.h"
#include"UpgradeWhip.h"
#include"Torch.h"
#include"Dragger.h"
#include"BigBat.h"
#include "Brick.h"
#include"SecretBrick.h"
#include"Camera.h"
#include "Burn.h"
#include "Crown.h"
#include"Treasure.h"
#include "Hit.h"
#include "Elevator.h"
#include "HidenObj.h"
#include "StairBottom.h"
#include "StairTop.h"
#include "Fleaman.h"
#include "Raven.h"
#include "Knight.h"
#include "Candle.h"
#include "StopWatch.h"
#include "DoubleShot.h"
#include "TripleShot.h"
#include "ThrowingAxe.h"
#include "HolyWater.h"
#include "Rosary.h"
#include "InvisibilityPotion.h"
#include "ForkChop.h"
#include "MagicCrystal.h"
#include "MoneyBag.h"
#include "Cross.h"
#include "Bat.h"
#include "Alien.h"
#include "Simon.h"

class Grid
{
	ofstream ofs;
	simon* Simon;
	int CellWidth, CellHeight;
	vector<CGameObject*> cell[20][100];
	vector<LPGAMEOBJECT> LstEnemy_Incam;
	vector<LPGAMEOBJECT> LstEnemy_Outcam;
	vector<LPGAMEOBJECT> LstBrick;
	vector<LPGAMEOBJECT> LstObj;
	vector <Effect*>LstEffect;
	vector<LPGAMEOBJECT> LstItem;
	int backup_top, backup_bot, backup_left, backup_right;
	unordered_map< int, unordered_map<int, vector<LPGAMEOBJECT>> > unMoveObjGrid;
	unordered_map< int, unordered_map<int, vector<LPGAMEOBJECT>> > moveObjGrid;
public:
	void push_backGrid(LPGAMEOBJECT obj, bool Check= false);
	Grid(simon * S)
	{
		ofs.open("output.txt", ios::out);
		Simon = S;
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 100; j++)
				cell[i][j].clear();
	}
	~Grid() {}
	void GetListObj1(vector<CGameObject*>& LstObj, vector<CGameObject*>& LstEnemy, Camera* cam);
	void InsertGrid(int type,int id, float x, float y, int w=1, int h=1, int d = 1, int HiObj = 0, int l = 0, int r = 0, int t = 0, int b = 0);
	void Update(DWORD dt, Camera * cam);
	void Render(Camera* cam);
	CGameObject* GetNewObj(int type,int id, float x, float y, int w=1, int h=1, int d = 1, int HiObj = 0, int l=0, int r=0, int t=0, int b=0);
	void ClearGrid();
	void OutFile()
	{
		for(int i=0; i<=(1020/CellW); i++)
			for(int j=0; j<=(384/CellH); j++)
				for(int k=0; k<unMoveObjGrid[i][j].size(); k++)
					ofs << i <<" "<<j<<" "<< unMoveObjGrid[i][j].at(k)->GetID() << "\n";
		return;
	}
};


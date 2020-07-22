#pragma once
#include"Scene.h"
#include"Simon.h"
#include"Brick.h"
#include"Ghost.h"
#include"Torch.h"
#include"UpgradeWhip.h"
#include"debug.h"
#include "Board.h"
#include "Heart.h"
#include "Map.h"
#include"SceneIntro.h"
#include "BrokenBrick.h"
#include "Burn.h"
#include "Hit.h"
class SceneGame:public Scene
{
	vector<CGameObject*> ListEnemy, ListEnemy_S;
	vector<CGameObject*> ListItem;
	vector <LPGAMEOBJECT> ListGhost;
	vector<CGameObject*> ListObj, ListObj_S, List_Brick;
	vector<Effect*>ListEffect;
	Camera* cam;
	simon* Simon;
	Map *map;
	DWORD tCreate;
	Grid* grid;
	Board *board = new Board();
	int TimeRemain;
	DWORD TotalTime;
	int Stage;
	int nGhost;
	float xG, yG;
	bool SwitchStage;
	bool BossStage;
	bool Checker;
	CGameObject* boss;
public :
	SceneGame();
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();
	void InitGame();
	void Update(DWORD dt);
	void Render();

	~SceneGame();
};


#pragma once
#include"GameObject.h"
#include"Morningstar.h"
#include"StopWatch.h"
#include "ThrowingAxe.h"
#include "HolyWater.h"
#include"Dragger.h"
#include "Cross.h"
#include "HidenObj.h"
#define SIMON_BBWIDTH 60
#define SIMON_BBHEIGHT 63
#define SIMON_IDLE 1
#define SIMON_WALK 2
#define SIMON_JUMP_STATE 3
#define SIMON_ATTACK 4
#define SIMON_JUMP_ATTACK 5
#define SIMON_DEATH 14	
#define SIMON_GETHIGH 6
#define SIMON_UP_STAIR 7
#define SIMON_DOWN_STAIR 8
#define SIMON_UP_STAIR_IDLE 9
#define SIMON_DOWN_STAIR_IDLE 10
#define SIMON_UP_STAIR_ATTACK 11
#define SIMON_DOWN_STAIR_ATTACK 12
#define SIMON_HURT 13
#define SIMON_HIDEFACE 15
#define SIMON_SITTING_BBOX 45
#define SIMON_WALK_SPEED 0.15f
#define SIMON_JUMP_SPEED 0.36f
#define SIMON_VY_HURT 0.25f
#define SIMON_VX_HURT 0.15f
#define SIMON_GRAVITY 0.005f 
#define SIMON_GRAVITY_JUMP 0.001f 
#define PULL_UP 18.0f

class simon : public CGameObject
{
	Camera*	 cam;
	unordered_map<GType, Weapon*>MapWeapon;
	unordered_map<GType, Weapon*>MapWeaponTShot;
	unordered_map<GType, Weapon*>MapWeaponDShot;

	Weapon* WeaponDShot;
	Weapon* WeaponTShot;
	GType	TypeWeapon,
			SubWeapon;

	float	Backup_x,
			Backup_y,
			Backup_d,
			Next_x,
			Next_y,
			Bonus_x,
			Bonus_y,
			AutoGo_Distance,
			AutoGo_Destination,
			AutoGo_Destination_y;

	int		HeartCollect,
			Live,
			Bonus_type,
			HStage,
			HObj,
			BotId,
			Next_d,
			TopId;

	DWORD	TimeFromLAtk,
			AtkTime,
			GethighTime,
			TStopWatch,
			TRosary,
			TGetHurt,
			TInvisible,
			TDie,
			Timegethigh,
			TimeOnStair,
			TimeUseSubWeapon,
			TimeForSubWeapon;

	bool	IsOnStair_Backup,
			UseSubWeapon,
			JustTele,
			AllowAtk;
public:

	int		Step,
			DirecUpStair,
			DirecDownStair;

	bool	IsAttacking,
			GetDoubleShot,
			UseStopWatch,
			UseRosary,
			Invisible,
			IsDie,
			IsReborn,
			IsJumping,
			IsSitting,
			IsWalking,
			IsGetHurt,
			IsGetHigh,
			IsUpStair,
			IsDownStair,
			IsOnStair,
			FirstStep,
			IsCollideWithStairBot,
			IsCollideWithStairTop,
			IsCollideWithBrick,
			IsAutoGo,
			OutStair,
			IsFinishTele,
			GameOver,
			IsCollideWithHobj;
	void	SetAutoGoDes(float X) { IsAutoGo = true; AutoGo_Destination = X; AutoGo_Distance = AutoGo_Destination-x; };
	int		GetHeart() { return HeartCollect; }
	void	SetSubWeapon(GType W) { SubWeapon = W; };
	GType	GetSubWeapon() { return SubWeapon; }
	LPGAMEOBJECT GetSubWeapon_Obj() { if (SubWeapon != GType::MORNINGSTAR) return MapWeapon[SubWeapon]; else return NULL; }
	int		Getlive() { return Live; }
	void	CalTime();
	void	SwitchWeapon();//kiem tra+chuyen doi vu khi
	void	UseMorningStar() { TypeWeapon = GType::MORNINGSTAR; }
	simon(Camera *camera);
	~simon();
	void	SetHinfo(int S, int H);
	void	Tele();
	void	CollectSubWeapon(GType Sw);
	GType	GetSubWeapon_Type() { return SubWeapon; }
	void	GetHidenObjinfo(int &S,int &H);
	float	GetBackup_y() { return Backup_y; }
	float	GetBackup_x() { return Backup_x; }
	void	Backup_Position() { Backup_x = x; Backup_y = y; }
	void	SetSimonState(GState state);
	void	GetBonusInfo(float& Bx, float& By, int& Btype) { Bx = Bonus_x; By = Bonus_y; Btype = Bonus_type; }
	void	SetSpeeds(int d) { vx = abs(vx) * d; if(d!=0) Direc = d; }
	void	GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void	Update(DWORD dt, vector<LPGAMEOBJECT> *coObj, vector <LPGAMEOBJECT>* coEnemy, vector <LPGAMEOBJECT>*coItem);
	void	AutoGo(DWORD dt);
	void	Render( Camera * cam);
	void	SetIsGetHurt(bool T);
	void	ReBorn(int St);
	void	Die();
	void	SetHeartCollect(int H) { HeartCollect = H; }
};
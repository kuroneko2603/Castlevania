#pragma once
#include "Game.h"
#include "DSutil.h"
#include <atlstr.h>
#include <unordered_map>
enum GSOUND {
	S_WHIP=1,
	S_HIT=2,
	S_AXE=3,
	COLLECTITEM=4,
	COLLECTHEART=5,
	S_SCENE=6,
	BROKENBRICK=7,
	S_HURT =8,
	S_ROSARY=9,
	S_CROSS =10,
	S_DAGGER=11,
	S_IPOTIONSTART=12,
	S_IPOTIONEND=13,
	DISPLAYTREASURE=14,
	COLLECTTREASURE=15,
	INTROMUSIC=16,
	LOSELIFE=17,
	S_SKELETON=18,
	S_BOSS=19,
	S_STAGECLEAR=20,
};
class Sound
{
private:
	unordered_map<int, CSound*> LstSound;
	CSoundManager *DSManager;
public:
	static Sound* Instance;
	static Sound* GetInstance();
	void Init();
	Sound();
	void AddSound(int type, LPTSTR filepath);
	void Play(GSOUND Type, bool Replay);
	bool IsPlaying(GSOUND T)
	{
		return LstSound[T]->IsSoundPlaying();
	}
	void Stop(GSOUND type)
	{
		LstSound[type]->Stop();
	}
	void LoadResources();
	~Sound(){}
};


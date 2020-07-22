#pragma once
#include "Enemy.h"
class Alien : public Enemy
{
	int Step;
public:
	Alien(simon * S);
	void Update(DWORD dt, vector <LPGAMEOBJECT>* coObject = NULL);
	void Render(Camera* cam);
	~Alien() {}
};


#pragma once
#include "Effect.h"
#define BURN_WIDTH 42
#define BURN_HEIGHT 44
class Burn:public Effect
{
	int count;
public:
	Burn(float X, float Y);
	~Burn() {}
};


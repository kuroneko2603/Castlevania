#include "StarShip.h"

void StarShip::Update(DWORD dt)
{
	x += -0.01 * dt;
	Direc = -1;
}

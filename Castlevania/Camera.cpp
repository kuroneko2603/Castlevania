#include "Camera.h"

Camera::~Camera()
{
}

void Camera::Update(DWORD dt)
{
	if (IsFollowSimon)
	{
		//DebugOut(L"fol simon \n");
		//vx = -0.18f;
	}
	x += vx * dt;
	if (IsAutoGoX)
	{
		if (abs(x - Backup_x) >= AutoGoDistance)
		{
			x -= (abs(x - Backup_x) - AutoGoDistance);
			IsAutoGoX = false;
			ReachDes = true;
			vx = 0;
		}
	}
	if (x <= BLeft)
		x = BLeft;
	if (x >= BRight)
	{
		x = BRight;
		if (IsAutoGoX)
		{
			IsAutoGoX = false;
			ReachDes = true;
			vx = 0;
		}
	}
}

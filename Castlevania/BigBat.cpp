#include "BigBat.h"

BigBat::BigBat(simon* S)
{
	type = GType::BIGBAT;
	Des = new HidenObj(1, 1, 1);
	Texture = CTextures::GetInstance()->GetTexture(type);
	sprite = new CSprite(Texture);
	SetSize(44, 60);
	vx = 0;
	vy = 0;
	Health = 16;
	Activate = false;
	Simon = S;
	P = -1;
}

void BigBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{

	float SimonX, SimonY;
	SimonX = Simon->GetX();
	SimonY = Simon->GetY();
	DWORD now = GetTickCount64();
	if (Simon->GetX() >= 1310.0f && !Activate)
	{
		DebugOut(L"%f %f\n", x, y);
		Activate = true;
		State = 2;
		vx = 0;
		vy = 0;
		TimeWait = now;
	}
	if (!Activate)
		return;
	if (P == 7 && isCollisionWithObj(Des))
	{
		P = -1;
		TimeWait = now;
	}
	if (P == -1 && now - TimeWait >= 500)
	{
		P = 0;
	}
	if (P == 0)
	{
		DebugOut(L"%f %f\n", x, y);
		DebugOut(L"0\n");
		if (SimonX > x)
		{
			des_x = SimonX - 150;
			if (des_x + 40 < cam->GetX())
				des_x = SimonX + 150;
		}
		else {
			des_x = SimonX + 150;
		
		}
		des_y = SimonY - 100;
		Des->SetPosition(des_x, des_y);
		CalRef1();
		if (des_x > x)
			vx = 0.12f;
		else
			vx = -0.12f;
		srand(time(NULL));
		int result = rand() % 10 + 1;
		if (result >= 2)
			P = 1;
		else
			P = 5;
		DebugOut(L"%f %f\n", Des->GetX(), Des->GetY());
	}
	if (P == 1 && isCollisionWithObj(Des))
	{
		DebugOut(L"1\n");
		CalRef();
		backup_x = x;
		backup_y = y;
		srand(time(NULL));
		int result = rand() % 10 + 1;
		DebugOut(L"re %d\n", result);
		if(result<=8)
		{
			P = 3;
			if (Simon->GetX() > x)
				des_x = Simon->GetX() + 80;
			else
				des_x = Simon->GetX() - 80;
			des_y = CalY(des_x);
			Des->SetPosition(des_x, des_y);
		}
		else
		{
			P = 2;
			if (Simon->GetX() > x)
				des_x = Simon->GetX() - 50;
			else
				des_x = Simon->GetX() + 50;
			des_y = CalY(des_x);
			Des->SetPosition(des_x, des_y);
		}
		if (des_x > x)
			vx = 0.2f;
		else
			vx = -0.2f;
		DebugOut(L"%f %f\n", Des->GetX(), Des->GetY());
	}
	if (P == 2 && isCollisionWithObj(Des))
	{
		DebugOut(L"2\n");
		des_x = backup_x;
		des_y = backup_y;
		Des->SetPosition(des_x, des_y);
		if (des_x > x)
			vx = 0.1f;
		else
			vx = -0.1f;
		P = 8;
		CalRef1();
		DebugOut(L"%f %f\n", Des->GetX(), Des->GetY());
	}
	if (P == 3 && isCollisionWithObj(Des))
	{
		DebugOut(L"3\n");
		des_x = cam->GetX() + SCREEN_WIDTH - 10;
		des_y = des_y - 20;
		Des->SetPosition(des_x, des_y);
		CalRef1();
		if (des_x > x)
			vx = 0.2f;
		else
			vx = -0.2f;
		P = 4;
		DebugOut(L"%f %f\n", Des->GetX(), Des->GetY());
		if (y > SimonY)
		{
			FireBall* fireball = new FireBall(Simon, x, y, SimonX, SimonY);
			LstFireBall.push_back(fireball);
			P = 9;
			Des->SetPosition(backup_x, backup_y);
			if (backup_x > x)
				vx = 0.1f;
			else
				vx = -0.1f;
			CalRef1();
		}
	}
	if (P == 4 && isCollisionWithObj(Des))
	{
		DebugOut(L"4\n");
		des_x = des_x - 180;
		if (des_x < 0)
			des_x = 0;
		des_y = des_y - 100;
		Des->SetPosition(des_x, des_y);
		CalRef1();
		if (des_x > x)
			vx = 0.2f;
		else
			vx = -0.2f;
		P = 6;
		DebugOut(L"%f %f\n", Des->GetX(), Des->GetY());

	}
	if (P == 5 && isCollisionWithObj(Des))
	{
		DebugOut(L"5\n");
		srand(time(NULL));
		int result = rand() % 10 + 1;
		des_x = cam->GetX()+20;
		if (des_x == Start_x)
			des_x -= 60;
		des_y = des_y + result*10;
		Des->SetPosition(des_x, des_y);
		CalRef1();
		if (des_x > x)
			vx = 0.2f;
		else
			vx = -0.2f;
		DebugOut(L"%f %f\n", Des->GetX(), Des->GetY());
		P = 6;
	}
	if (P == 6 && isCollisionWithObj(Des))
	{
		DebugOut(L"6\n");
		des_x = Start_x;
		des_y = des_y;
		Start_y = des_y;
		Des->SetPosition(des_x, des_y);
		CalRef1();
		if (des_x > x)
			vx = 0.2f;
		else
			vx = -0.2f;
		TimeWait = now;
		IsWaiting = true;
		DebugOut(L"%f %f\n", Des->GetX(), Des->GetY());
	}
	if (P == 6 && IsWaiting && now- TimeWait>=900)
	{
		P = 7;
		IsWaiting = false;
	}
	if (P == 8 && isCollisionWithObj(Des))
	{
		P = 0;
	}
	if (P == 9 && isCollisionWithObj(Des))
	{
		P = 0;
	}
	for (int i = 0; i < LstFireBall.size(); i++)
		LstFireBall[i]->Update(dt);
	if (P == -1 || IsWaiting)
		return;
	if (P == 3 || P==2 ) 
	{
		x += dt * vx;
		y = CalY(x);
	}
	else
	{
		if (abs(y - CalY1(x + dt * vx)) < abs(x- (x+dt*vx)))
		{
			x += dt * vx;
			y = CalY1(x);
		}
		else
		{
			if (Des->GetY() > y)
				y += 0.1f * dt;
			else
				y += -0.1f * dt;
			x = CalX1(y);
		}
	}
	if (x < cam->GetX() - 5 || Des->GetY()<-5 || Des->GetY()>= SCREEN_HEIGHT)
		P = 0;
}

void BigBat::CalRef()
{
	float X, Y;
	X = Simon->GetX();
	Y = Simon->GetY();
	a = 1.0f * (y - Y) / (x * x - 2.0f * x * X + X * X);
	b = -2.0f * a * X;
	c = Y + a * X * X;
	//DebugOut(L"%f %f %f %f %f\n", a, b, c, X, Y);
}

float BigBat::CalY(float X)
{
	//DebugOut(L"%f %f\n",x, (a * x * x + b * x + c));
	return a * X * X + b * X + c;
}

void BigBat::CalRef1()
{
	a1 = (Des->GetY() - y) / (Des->GetX() - x);
	b1 = y - a1 * x;
}

float BigBat::CalY1(float X)
{
	return a1 * X + b1;
}

float BigBat::CalX1(float Y)
{
	return (Y-b1)/a1;
}

void BigBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 8;
	right = left + 80;
	top = y;
	bottom = y + 44;
}

void BigBat::Render(Camera* Cam)
{
	cam = Cam;
	if (sprite->GetState() != State)
	{
		sprite->SetState(State);
	}
	//RenderBBox(cam);
	float xCam = cam->PossInCamera(x, y).x;
	float yCam = cam->PossInCamera(x, y).y;
	if (Health >= 1)
		this->sprite->Draw(xCam, yCam, Direc);
	Des->Render(cam);
	for (int i = 0; i < LstFireBall.size(); i++)
		LstFireBall[i]->Render(cam);
}

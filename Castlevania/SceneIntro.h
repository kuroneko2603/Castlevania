#pragma once
#include"Brick.h"
#include"Scene.h"
#include"MenuBat.h"
#include"StarShip.h"
#include"IntroBat.h"
#include"Simon.h"
#include"SceneGame.h"
#include"Brick.h"
#include"Font.h"
class SceneIntro :public Scene
{
	Font* font;
	simon* Simon;
	CSprite* sprite;
	MenuBat* menubat;
	StarShip* starship;
	IntroBat* introbat1;
	IntroBat* introbat2;
	int StateScene, StateText;
	bool PressKey;
	DWORD PressKeyT, ShowText;
	Camera* cam;
	Brick* brick;
	Sound* sound;
public:
	SceneIntro();
	void Update(DWORD dt);
	void KeyState(BYTE* state) {
		if (PressKey)
			return;
		if (CGame::GetInstance()->IsKeyDown(DIK_SPACE))
		{
			PressKey = true;
			PressKeyT = GetTickCount64();
			return;
		}
	}
	void OnKeyDown(int KeyCode) {}
	void OnKeyUp(int KeyCode) {}
	void LoadResources() {}
	void Render() {
		if (StateScene == 1)
		{
			sprite->DrawBoard(1, 0);
			menubat->Render(cam);
			if(StateText==1)
				font->Render(140, 250, "press space to play");
		}
		else
		{
			sprite->SetState(2);
			sprite->DrawBoard(2,20);
			introbat1->Render(cam);
			introbat2->Render(cam);
			starship->Render(cam);
			Simon->Render(cam);
		}
	}
	~SceneIntro() {}

};


#include "SceneIntro.h"

SceneIntro::SceneIntro()
{
	font = new Font();
	cam = new Camera();
	cam->SetBoundary(0, 0, 0, 0);
	Simon = new simon(cam);
	Simon->SetSpeed(-0.15f, 0.0f);
	Simon->SetPosition(500, 280);
	Simon->SetDirection(-1);
	Simon->SetAutoGoDes(225.0f);
	StateScene = StateText = 1;
	menubat = new MenuBat();
	starship = new StarShip();
	introbat1 = new IntroBat(1);
	introbat2 = new IntroBat(-1);
	sound = Sound::GetInstance();
	sprite = new CSprite(CTextures::GetInstance()->GetTexture(GType::SCENEINTRO));
	brick = new Brick(512, 32);
	brick->SetPosition(0, 402);
	introbat1->SetPosition(50, 50);
	introbat2->SetPosition(100, 20);
	starship->SetPosition(450, 20);
}

void SceneIntro::Update(DWORD dt)
{
	DWORD now = GetTickCount64();
	if (StateScene == 1)
	{
		if (PressKey)
		{
			if (now - ShowText >= 500 && StateText==0)
			{
				ShowText = now;
				StateText = 1;
			}
			if (now - ShowText >= 200 && StateText==1)
				StateText = 0;
			if (now - PressKeyT >= 3000)
			{
				StateScene = 2;
				sound->Play(GSOUND::INTROMUSIC, false);
			}
		}
	}
	else
	{
		if (Simon->IsAutoGo)
		{
			Simon->AutoGo(dt);
		}
		else
		{
			Simon->SetSimonState(GState::HIDEFACE);
			
		}
		introbat1->Update(dt);
		introbat2->Update(dt);
		starship->Update(dt);
		if (!sound->IsPlaying(GSOUND::INTROMUSIC))
			SceneManager::GetInstance()->SetScene(new SceneGame());
	}
}

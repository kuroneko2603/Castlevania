#pragma once
#include "define.h"

class Scene
{
public:
	Scene();
	bool Change_background;
	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	
	virtual void LoadResources();
	virtual void Update(DWORD dt);
	virtual void Render();

	virtual ~Scene();

};


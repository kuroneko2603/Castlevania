#pragma once
#include "Scene.h" 
#include "define.h" 

class SceneManager:public Scene
{
private:
	static SceneManager* Instance;

public:
	Scene* scene;
	SceneManager() {}
	~SceneManager() {}

	static SceneManager* GetInstance()
	{
		if (Instance != NULL)
			return Instance;
		else
		{
			Instance = new SceneManager();
			return Instance;
		}
	}
	void SetScene(Scene* x)
	{
		Scene* tmp = scene;
		scene = x;
		SAFE_DELETE(tmp);
	}
	void LoadResources() { scene->LoadResources(); }
	void Update(DWORD dt) { scene->Update(dt); }
	void Render() { scene->Render(); }
	Scene* GetScene()	{	return scene;}
	void KeyState(BYTE* state) { scene->KeyState(state); }
	void OnKeyDown(int KeyCode) { scene->OnKeyDown(KeyCode); }
	void OnKeyUp(int KeyCode) { scene->OnKeyUp(KeyCode); }

};


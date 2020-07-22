#pragma once
#include"define.h"
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
	Manage texture database
*/
class CTexture
{
	LPDIRECT3DTEXTURE9 texture;
public:
	unordered_map <int, vector<RECT>> AnimationList;
	vector<vector<DWORD>>TimeperAni;
	CTexture(LPDIRECT3DTEXTURE9 tex,unordered_map<int, vector<RECT>> Animap,vector<vector<DWORD>> TimeSet);
	~CTexture()
	{
		if (texture != NULL)
			texture->Release();
	}
	LPDIRECT3DTEXTURE9 GetTex() { return texture; }
};

class CTextures
{
	static CTextures* __instance;
	unordered_map< int, CTexture*> TexList;
	unordered_map<int, LPDIRECT3DTEXTURE9>TexMap;
public:
	CTextures();
	void Add(int type, CTexture* texture);
	void AddTexMap(int id, LPCSTR Filename, int R=255, int G=0, int B=255);
	LPDIRECT3DTEXTURE9 GetTex(int id) { return TexMap[id]; }
	CTexture* GetTexture(GType type);
	static CTextures* GetInstance();
	void GetInfoFromFile(LPCSTR Filename);
	void UnLoad()
	{
		TexMap.clear();
		TexList.clear();
	}
};
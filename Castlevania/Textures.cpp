#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"

CTextures* CTextures::__instance = NULL;

CTextures::CTextures()
{
	GetInfoFromFile("textures\\LTextures.txt");
}

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
		return __instance;
}

void CTextures::GetInfoFromFile(LPCSTR Filename)
{
	ifstream ifs(Filename, ios::in);
	int nTexture;//tong so tex
	ifs >> nTexture;
	for (int i = 0; i < nTexture; i++)
	{
		int idTex;
		ifs >> idTex;
		string filePath;
		ifs >> filePath;
		LPCSTR FilePath = filePath.c_str();
		int R, G, B;
		ifs >> R >> G >> B;
		this->AddTexMap(idTex, FilePath, R, G, B);
	}
	int NObj;//tong so obj 
	ifs >> NObj;
	for (int i = 0; i < NObj; i++)
	{
		int type,//la loai obj nao
			Texid,
			NState;//so state cua obj
		ifs >> type;
		ifs >> Texid;
		ifs >> NState;
		DebugOut(L"%d %d %d\n", type, Texid, NState);
		vector<RECT> Frame;
		unordered_map<int, vector<RECT>> AniSet;
		vector<vector<DWORD>>timeset;
		for (int j = 0; j < NState; j++)//chay cho tung state
		{
			DWORD time;
			int State;
			int NFrame;//so frame cua moi state
			ifs >> State >> NFrame;
			DebugOut(L"%d %d \n",State, NFrame);
			vector<DWORD>anitimeset;
			for (int k = 0; k < NFrame; k++)
			{
				RECT r;
				int ftime;
				ifs >> r.left >> r.top >> r.right >> r.bottom >> ftime;
				Frame.push_back(r);
				anitimeset.push_back(ftime);
				DebugOut(L"%d %d %d %d %d\n", r.left, r.right, r.top, r.bottom, ftime);
			}
			AniSet[State] = Frame;
			Frame.clear();
			timeset.push_back(anitimeset);
		}
		CTexture* textmp = new CTexture(this->GetTex(Texid), AniSet, timeset);
		Add(type, textmp);
	}
	ifs.close();
}

void CTextures::Add(int type, CTexture* texture)
{
	TexList[type] = texture;
}

void CTextures::AddTexMap(int id, LPCSTR Filename, int R, int G, int B)
{
	LPDIRECT3DTEXTURE9 tex;
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(Filename, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: \n");
		return;
	}
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileExA(
		d3ddv,								// Pointer to Direct3D device object
		Filename,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(R, G, B),
		&info,
		NULL,
		&tex);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	DebugOut(L"[INFO] Texture loaded Ok: id=%d,\n",id);
	TexMap[id] = tex;
}

CTexture* CTextures::GetTexture(GType type)
{
	int tmp = type;
	return TexList[tmp];
}

CTexture::CTexture(LPDIRECT3DTEXTURE9 tex,unordered_map<int, vector<RECT>> Animap, vector<vector<DWORD>> TimeSet)
{
	texture = tex;
	AnimationList = Animap;
	TimeperAni = TimeSet;
}

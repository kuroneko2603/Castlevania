#include "Map.h"

void Map::ReadMap(float &BL, float &BR, float &BT, float &BB, Grid * grid)
{
	ifstream ifs(MapLink, ios::in);
	ifs >> MapRow >> MapColumn;
	//lay tilemap tu linkmap
	for (int i = 0; i < MapRow; i++)
		for (int j = 0; j < MapColumn; j++)
			ifs >> TileMap[i][j];
	ifs >> BL >> BR >> BT >> BB;
	int nObj;//so loai obj co trong map
	ifs >> nObj;
	for (int i = 0; i < nObj; i++)
	{
		int Type;//loai obj
		ifs >> Type;
		int NoType;//so doi tuong thuoc obj do
		ifs >> NoType;
		for (int j = 0; j < NoType; j++)
		{
			int idObj, xObj, yObj, dObj, objHiden, width, height, left, right, top, bot;
			ifs >> idObj >> xObj >> yObj >> dObj >> width >> height >> objHiden >> left >> right >> top >> bot;
			grid->InsertGrid(Type, idObj, xObj, yObj, width, height, dObj, objHiden, left, right, top, bot);
		}
	}
	ifs.close();
}

void Map::Drawmap( Camera * cam)
{
	RECT r;
	int FrameW = TexW / TexColumn;
	int FrameH = TexH / TexRow;
	//DebugOut(L"%d %d \n", FrameW, FrameH);
	for (int i = 0; i < MapRow; i++)
	{
		for (int j = 0; j < MapColumn; j++)
		{
			int IdFrame = TileMap[i][j];
			int h = i * FrameH - cam->GetY();
			r.left = (IdFrame - 1)%TexColumn * FrameW;
			r.top = (IdFrame - 1)/TexColumn* FrameH;
			r.right = r.left + FrameW;
			r.bottom = r.top + FrameH;
			CGame::GetInstance()->Draw(j * FrameW - cam->GetX(), i * FrameH - cam->GetY(), tex, r);
		}
		//DebugOut(L"\n");
	}
}

void Map::SetMap(int Id)
{
	mapId = Id;
	string TexLink;
	ifstream ifs("textures//MapInfo.txt", ios::in);
	ifs >> nMap;
	if (Id > nMap)
		return;
	for (int i = 0; i < mapId; i++)
	{
		ifs >> MapLink;
		//ifs >> MapRow >> MapColumn;
		ifs >> TexLink;
		ifs >> TexRow >> TexColumn;
	}
	//Lay texture tu linktex
	LPCSTR FName = TexLink.c_str();
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(FName, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed\n");
		return;
	}
	TexH = info.Height;
	TexW = info.Width;
	//DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", info.Height,info.Width);
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	result = D3DXCreateTextureFromFileExA(
		d3ddv,								// Pointer to Direct3D device object
		FName,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&tex);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	DebugOut(L"[INFO] Maptile loaded Ok\n");
	ifs.close();
}

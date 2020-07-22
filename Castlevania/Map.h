#pragma once
#include "Game.h"
#include "Sprites.h"
#include "Camera.h"
#include "Grid.h"
class Map
{
	LPDIRECT3DTEXTURE9 tex;
	int TexRow, TexColumn, MapRow, MapColumn;
	UINT TexW, TexH;
	int mapId;
	int TileMap[100][100];
	char* FileName;
	string MapLink;
	int nMap;
public:
	Map() {};
	~Map() {};
	void ReadMap(float& BL, float& BR, float& BT, float& BB, Grid* grid);
	void Drawmap(Camera *cam);
	void SetMap(int Id);
};


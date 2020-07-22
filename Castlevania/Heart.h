#pragma once
#define HEART_WIDTH 16 
#define HEART_HEIGHT 16
#define BIGHEART_WIDTH 24
#define BIGHEART_HEIGHT 20
#include "Item.h"
class Heart :public Item
{
	int size;
public:
	Heart(int S);
	~Heart() {};
	int GetW();
	int GetH();
	int GetSize() { return size; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj);
};


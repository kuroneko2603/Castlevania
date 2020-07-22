#pragma once
#define	UWHIP_WIDTH 32
#define UWHIP_HEIGHT 32
#include "Item.h"
class UpgradeWhip:public Item
{
public:
	UpgradeWhip();
	~UpgradeWhip() {}
	int GetW() { return UWHIP_WIDTH; }
	int GetH() { return UWHIP_HEIGHT; }
};


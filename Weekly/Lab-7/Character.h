#pragma once
#include <iostream>

using namespace std;

//What could we do better...?
class Character
{
public:
	// hp
	int hp;
	// armor
	int armor;
	// position
	int posX;
	int posY;
	// size
	int w;
	int h;

	Character(int hp, int a, int posX, int posY, int w, int h);

	//calculates damage and applies it on the character
	void calcdam(int dinphysic, int dinmagic, int dtype, int moveid, bool cr, bool heal);
	void Faint(bool afterSelfDamage);
	virtual void DoThing() = 0;
};
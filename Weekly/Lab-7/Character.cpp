#include "Character.h"

Character::Character(int hp, int a, int posX, int posY, int w, int h)
{
}

void Character::Faint(bool afterSelfDamage)
{
	if (afterSelfDamage)
	{
		cout << "You've fainted!";
	}
	else
	{
		cout << "You have been defeated!";
	}
}

void Character::calcdam(int dinphysic, int dinmagic, int dtype, int moveid, bool cr, bool heal)
{
	// checks if moveid is the move ID for "no damage", if so then dont do damage
	if (moveid == -1)
	{
		return;
	}

	// checks if moveid is the move ID for "revive", if so then revive
	if (moveid == 4 && hp <= 0)
	{
		hp = 1;
	}

	// if healing then magic damage is actually healing
	if (heal)
	{
		dinmagic = -dinmagic;
	}

	//if critical hit
	if (cr)
	{
		hp -= dinphysic * 2 * (1.0f / armor);
	}
	else
	{
		hp -= dinphysic * (1.0f / armor);
	}

	hp -= dinmagic;

	// health check
	if (hp < 0)
	{
		hp = 0;
		Faint(false); // Wait... Faint(false)? What does this mean? Does it mean don't faint? 
	}
}

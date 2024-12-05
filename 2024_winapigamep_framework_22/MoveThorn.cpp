#include "pch.h"
#include "MoveThorn.h"

MoveThorn::MoveThorn()
{
	SetMapSize({ 4, 1 });
	
	SetTile({ 0, 0 }, 30);
	SetTile({ 1, 0 }, 28);
	SetTile({ 2, 0 }, 29);
	SetTile({ 3, 0 }, 30);
}

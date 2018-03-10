#include "BombUp.h"

BombUp::BombUp(int image, const Math::Vector2& pos)
	:PowerUp(true, image,  pos)
{

}

BombUp::~BombUp()
{

}

void BombUp::Collect(Player & player)
{
	player.bombLimit += 1;
	if (player.bombLimit >= player.kMaxBombs)
	{
		player.bombLimit = player.kMaxBombs;
	}
}

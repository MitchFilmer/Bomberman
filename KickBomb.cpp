#include "KickBomb.h"

KickBomb::KickBomb(int image, const Math::Vector2& pos)
	:PowerUp(true, image, pos)
{

}

KickBomb::~KickBomb()
{

}

void KickBomb::Collect(Player & player)
{
	player.SetKick(true);
}

#include "FireUp.h"

	FireUp::FireUp(int image, const Math::Vector2& pos)
		:PowerUp(true, image,  pos)
	{

	}

	FireUp::~FireUp()
	{
	
	}

	void FireUp::Collect(Player & player)
	{
		player.firePower += 1;
	}

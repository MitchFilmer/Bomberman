#include "PowerUp.h"
#include "XEngine.h"

int PowerUp::spriteIndex = -1;

PowerUp::PowerUp(bool state, int image, Math::Vector2 pos) : mIsActive(state), mPosition(pos), mSprite(image)
{
}

void PowerUp::Collect(Player& player)
{

}


void PowerUp::Render( )
{
	X::DrawSprite(mSprite, mPosition);
}



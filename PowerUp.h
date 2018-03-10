#ifndef POWERUP_HEADER_H
#define POWERUP_HEADER_H

#include "XEngine.h"
#include "Player1.h"

using namespace X;

class Player;
class Tile;

class PowerUp
{
public:
	PowerUp(bool state, int image, Math::Vector2 pos);
	virtual ~PowerUp() {}

	virtual void Collect(Player& player) = 0;
	void Render();
	bool IsActive()						{ return mIsActive; }
	Math::Vector2 GetPosition()			{ return mPosition; }
	Math::Rect GetBoundingRect() const	{ return Math::Rect(mPosition.x, mPosition.y, mPosition.x + 32, mPosition.y + 32); }
	static int spriteIndex;

private:
	int mSprite;
	Math::Vector2 mPosition;
	bool mIsActive = false;
	const Tile* mTile = nullptr;

};
#endif // !POWERUP_HEADER_H
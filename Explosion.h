#ifndef EXPLOSION_HEADER_H
#define EXPLOSION_HEADER_H

#include "XEngine.h"

using namespace X;

class Explosion
{
public:
	Explosion();
	~Explosion();

	void Initialize();
	void Activate();
	bool IsActive() { return mIsActive; }
	void Update(float deltaTime);
	void Render();
	void SetPosition(Math::Vector2 pos) { mPosition = pos; }
	void SetSprite(int spriteNumber)	{ mSpriteNumber = spriteNumber; }
	Math::Rect GetBoundingRect() const	{ return Math::Rect(mPosition.x, mPosition.y, mPosition.x + 32.0f, mPosition.y + 32.0f); }

private:
	bool mIsActive = false;
	const float mFixedExplosionTime = 0.5f;
	float mActiveExplosionTime = mFixedExplosionTime;	
	Math::Vector2 mPosition;
	int mSpriteNumber;
};

#endif // !EXPLOSION_HEADER_H

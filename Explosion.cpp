#include "Explosion.h"

using namespace std;


Explosion::Explosion()
{
	
}

Explosion::~Explosion()
{

}

void Explosion::Initialize()
{
	
}

void Explosion::Update(float deltaTime)
{
	mActiveExplosionTime -= deltaTime;
	if (mActiveExplosionTime < 0.0f)
	{
		mIsActive = false;
	}
}

void Explosion::Render()
{
	X::DrawSprite(mSpriteNumber, mPosition);
}

void Explosion::Activate()
{
	mIsActive = true;
	mActiveExplosionTime = mFixedExplosionTime;
}
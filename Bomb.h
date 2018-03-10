#ifndef BOMB_HEADER_H
#define BOMB_HEADER_H

#include "XEngine.h"

class Player;
class Tile;

using namespace X;

class Bomb
{
public:
	Bomb(const Player& _player);
	~Bomb();

	const char* bombSprite[2] = { "Bomb1.png", "Bomb2.png" };
	int bombImage[2];

	void Initialize();
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	void Render();
	void Explode();

	bool IsActive()									{ return mActive; }
	void SetPower(int pwr)							{ mPower = pwr; }
	void SetVelocity(Math::Vector2 vel)				{ mVelocity = vel; }
	void SetDirection(Math::Vector2 dir)			{ mVelocity = dir * mSpeed; }
	void SetPosition(const Math::Vector2& pos)		{ mPosition = pos; }
	void SetCenter(const Math::Vector2& pos)		{ mPosition = pos - Math::Vector2 (16.0f, 16.0f); }

	Math::Vector2 GetPosition() const				{ return mPosition; }
	Math::Vector2 GetVelocity()						{ return mVelocity; }
	Math::Vector2 GetCenter() const					{ return mPosition + Math::Vector2(16.0f, 16.0f); }

	Math::Rect GetBoundingRect() const				{ return Math::Rect(0.0f, 0.0f, 32.0f, 32.0f); }
	void Activate(int pwr, bool state, Tile* tile);

	void SetMoving(bool state)						{ mIsMoving = state; }
	bool IsMoving()									{ return mIsMoving; }

	int animateFrame = 0;
	float animateTimer = 1.5f;

	void SetTile(Tile* tile)						{ mTile = tile;}

private:
	Math::Vector2 mPosition;
	Math::Vector2 mVelocity;
	float mSpeed = 150.0f;
	float mBombTimer = 3.f;
	int mPower;
	bool mActive = false;
	const Player& player;
	Tile* mTile = nullptr;
	bool mIsMoving = false;
};
#endif
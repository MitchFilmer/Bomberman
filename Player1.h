#ifndef PLAYER1_HEADER_H
#define PLAYER1_HEADER_H
#include "XEngine.h"
#include "Bomb.h"
#include "Tile.h"
using namespace X;

class Game;

class Player
{
public:
	Player(Game& game, int upKey, int downKey, int leftKey, int rightKey, int bombKey);
	int down[4];
	int up[4];
	int left[4];
	int right[4];

	void Initialize(int _down[4], int _left[4], int _up[4], int _right[4]);

	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	void Render();
	void Destroy();
	void SetVelocity(const Math::Vector2 vel) { mVelocity = vel; }

	bool IsActive()							{ return mIsActive; }
	Math::Vector2 GetPosition()				{ return mPosition; }
	float GetPosX()							{ return mPosition.x; }
	float GetPosY()							{ return mPosition.y; }
	Math::Vector2 GetTilePosition()			{ return Math::Vector2 (mPosition.x / 32, mPosition.y / 32); }
	Math::Rect GetBoundingRect() const		{ return Math::Rect(mPosition.x, mPosition.y+ (height*0.5f), mPosition.x + width , mPosition.y + height); }
	Math::Vector2 GetCenter() const			{ return mPosition + Math::Vector2(10, 20);}
	Math::Vector2 GetHalfDim() const		{ return Math::Vector2(width*.5f, 10); }
	Math::Vector2 GetVelocity() const		{ return mVelocity; }
	Game& GetGame() const					{ return mGame; }

	void SetPosX(float x)					{ mPosition.x = x; }
	void SetPosY(float y)					{ mPosition.y = y; }
	
	void SetKick(bool state)				{ mHasKick = state; }
	bool CanKick()							{ return mHasKick; }
	int firePower = 2;
	int bombLimit = 1;
	mutable int activeBombs = 0;
	static const int kMaxBombs = 5;
	Bomb bombArr[kMaxBombs];
	int mBombIndex = 0;

	int upKey;
	int downKey;
	int leftKey;
	int rightKey;
	int bombKey;

	enum class AnimationState
	{
		Idol = 0,
		MovingUp = 1,
		MovingDown = 2,
		MovingLeft = 3,
		MovingRight = 4,
	};

	float animTimer = 1;
	int animFrame = 0;
	AnimationState animState = AnimationState::Idol;
	AnimationState prevAnimSate = animState;
	bool justPlacedBomb = false;

private:
	bool mHasKick = false;
	float mSpeed;
	bool mIsActive = true;
	Math::Vector2 mPosition;
	Math::Vector2 mVelocity;
	int width;
	int height;	
	Game& mGame;
};

#endif // !PLAYER1_HEADER_H
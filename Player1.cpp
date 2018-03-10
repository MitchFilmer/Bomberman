#include "Player1.h"
#include "Game.h"

Player::Player(Game& game, int _upKey, int _downKey, int _leftKey, int _rightKey, int _bombKey)
	: bombArr {*this, *this, *this, *this, *this}
	, mGame(game)
{
	mPosition.x = 30.0f;
	mPosition.y = 30.0f;
	width = 18.0f;
	height = 30.0f;
	firePower = 2;
	mSpeed = 100.0f;

	upKey = _upKey;
	downKey = _downKey;
	leftKey = _leftKey;
	rightKey = _rightKey;
	bombKey = _bombKey;
}

void Player::Initialize(int _down[4], int _left[4], int _up[4], int _right[4])
{
	memcpy(down, _down, 4 * sizeof(int));
	memcpy(left, _left, 4 * sizeof(int));
	memcpy(right, _right, 4 * sizeof(int));
	memcpy(up, _up, 4 * sizeof(int));

	for (int i = 0; i < kMaxBombs; i++)
	{
		bombArr[i].Initialize();
	}
}

void Player::Update(float deltaTime)
{
	if (mIsActive)
	{
		// =========================== UP
		if (X::IsKeyDown(upKey))
		{
			animState = AnimationState::MovingUp;
			mVelocity.x = 0.0f;
			mVelocity.y = -mSpeed;
		}

		// =========================== LEFT
		else if (X::IsKeyDown(leftKey))
		{
			animState = AnimationState::MovingLeft;
			mVelocity.x = -mSpeed;
			mVelocity.y = 0.0f;
		}

		// =========================== DOWN
		else if (X::IsKeyDown(downKey))
		{
			animState = AnimationState::MovingDown;
			mVelocity.x = 0.0f;
			mVelocity.y = mSpeed;
		}

		// =========================== RIGHT
		else if (X::IsKeyDown(rightKey))
		{
			animState = AnimationState::MovingRight;
			mVelocity.x = mSpeed;
			mVelocity.y = 0.0f;
		}

		// =========================== ANIMATION FRAME CONTROLLER
		if (prevAnimSate != animState)
		{
			prevAnimSate = animState;
			animTimer = 0;
		}
		else
		{
			animTimer += deltaTime;
			if (animTimer > .2f)
			{
				animFrame++;
				animTimer = 0;
				if (animFrame > 3)
				{
					animFrame = 0;
				}
			}
		}

		// =========================== PLACE BOMBS
		if (X::IsKeyPressed(bombKey) && activeBombs < bombLimit)
		{
			activeBombs++;

			int tileX = GetCenter().x / 32;
			int tileY = GetCenter().y / 32;

			Tile* tile = &mGame.GetTile(tileX, tileY);
			bombArr[mBombIndex].Activate(firePower, true, tile);
			mBombIndex = (mBombIndex + 1) % kMaxBombs;
			justPlacedBomb = true;

		}
		for (int i = 0; i < kMaxBombs; i++)
		{
			if (bombArr[i].IsActive())
			{
				bombArr[i].Update(deltaTime);
			}
		}
	}
}

void Player::Render()
{
	for (int i = 0; i < kMaxBombs; i++)
	{
		if (bombArr[i].IsActive())
		{
			bombArr[i].Render();
		}
	}
	if (mIsActive)
	{
		switch (animState)
		{
		case AnimationState::Idol:
			X::DrawSprite(down[0], mPosition);
			break;
		case AnimationState::MovingUp:
			X::DrawSprite(up[animFrame], mPosition);
			break;
		case AnimationState::MovingDown:
			X::DrawSprite(down[animFrame], mPosition);
			break;
		case AnimationState::MovingLeft:
			X::DrawSprite(left[animFrame], mPosition);
			break;
		case AnimationState::MovingRight:
			X::DrawSprite(right[animFrame], mPosition);
			break;
		}
	}
}


void Player::Destroy()
{
	mIsActive = false;
}

void Player::PostUpdate(float deltaTime)
{
	mPosition += mVelocity * deltaTime; 
	mVelocity = Math::Vector2::Zero();

	for (int i = 0; i < kMaxBombs; i++)
	{
		if (bombArr[i].IsActive())
		{
			bombArr[i].PostUpdate(deltaTime);
		}
	}
}

#include "Bomb.h"
#include "Explosion.h"
#include "Player1.h"
#include "Tile.h"
#include "Game.h"

using namespace X;

Bomb::Bomb(const Player& _player)
	: player(_player)
{
	Math::Vector2 mPosition;
	mBombTimer = 3.0f;
	animateTimer = 1.5f;
	mPower = _player.firePower;
	mActive = false;
}

Bomb::~Bomb()
{

}

void Bomb::Initialize()
{
	for (int i = 0; i < 2; i++)
	{
		bombImage[i] = X::LoadTexture(bombSprite[i]);
	}
}

void Bomb::Update(float deltaTime)
{
	animateTimer += deltaTime;
	if (animateTimer > .4f)
	{		
		animateTimer = 0;
		animateFrame ^= 1;
	}


	mBombTimer -= deltaTime;
	if (mBombTimer <= 0.0f)
	{
		Explode();		
	}
	

}

void Bomb::PostUpdate(float deltaTime)
{
	if (mIsMoving)
	{
		mPosition += mVelocity * deltaTime;
	}

}

void Bomb::Render()
{
	X::DrawSprite(bombImage[animateFrame], mPosition);
}

void Bomb::Activate(int pwr, bool state, Tile* tile)
{
	mPower = pwr;
	mActive = state;
	mTile = tile;
	mTile->SetBombType(this);
	mPosition = mTile->GetPosition();
	mBombTimer = 3.f;
	mIsMoving = false;
}

void Bomb::Explode()
{
	X::PlayAudio(player.GetGame().quack_id, false, 1.0f, 1.0f, 0.5f);
	player.activeBombs--;
	mTile->SetPassableType(Tile::floor);
	player.GetGame().RegisterExplosion(mPosition, mPower);
	mActive = false;
	mIsMoving = false;
}


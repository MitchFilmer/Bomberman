#include "Tile.h"

int Tile::floor = -1;
int Tile::destructibles = -1;

Tile::Tile()
{
	spriteNum = 0;
	position.x = 0.0f;
	position.y = 0.0f;
	width = 32;
	height = 32;
	mType = Type::Passable;
	mPowerUpIndex = -1;
}

Tile::Tile(int sprite, float x, float y, int w, int h, bool f)
{
	spriteNum = sprite;
	position.x = x;
	position.y = y;
	width = w;
	height = h;
	mType = Type::Passable;
	mPowerUpIndex = -1;
}

void Tile::SetPassableType(int sprite)
{
	mType = Type::Passable;
	spriteNum = sprite;
	mBomb = nullptr;
	mPowerUpIndex = -1;
}

void Tile::SetPowerType(int sprite, int powerUpIndex)
{
	mType = Type::Powerup;
	spriteNum = sprite;
	mPowerUpIndex = powerUpIndex;
}
int Tile::GetSprite() const
{
	return spriteNum;
}

float Tile::GetHalfWidth() const
{
	return static_cast<float>(width) * 0.5f;
}

float Tile::GetHalfHeight() const
{
	return static_cast<float>(height) * 0.5f;
}

Math::Vector2 Tile::GetPosition() const
{
	return position;
}

void Tile::SetSprite(int n)
{
	spriteNum = n;
}

void Tile::SetPosX(int x)
{
	position.x = x;
}

void Tile::SetPosY(int y)
{
	position.y = y;
}
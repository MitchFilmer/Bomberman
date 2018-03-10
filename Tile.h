#ifndef  TILE_HEADER_H
#define TILE_HEADER_H
#include <XEngine.h>

using namespace X;

class Bomb;
class PowerUp;

class Tile
{
public:
	enum class Type
	{
		Passable,
		Indestructable,
		Destructible,
		Bomb,
		Powerup

	};

public:
	Tile();
	Tile(int sprite, float x, float y, int w, int h, bool f);
	~Tile() {}

	int GetSprite() const;
	float GetHalfWidth() const;
	float GetHalfHeight() const;
	Type GetType() const { return mType; }
	Math::Vector2 GetPosition() const;
	Math::Rect GetBoundingRect() const { return Math::Rect(position.x, position.y, position.x + width, position.y + height); }
	Bomb* GetBomb() const { return mBomb; }
	int GetPowerUpIndex() const { return mPowerUpIndex; }

	void SetPassableType(int spriteNum);
	void SetPowerType(int spriteNum, int powerUpIndex);
	void SetType(Type type) const { mType = type; }
	void SetBombType(Bomb* bomb) const 
	{
		mType = Tile::Type::Bomb; 
		mBomb = bomb; 
	}
	void SetSprite(int);
	void SetPosX(int x);
	void SetPosY(int y);

	static int floor;
	static int destructibles;

private:

	mutable Type mType;
	Math::Vector2 position;
	int spriteNum;
	int width;
	int height;

	int mPowerUpIndex;
	mutable Bomb* mBomb = nullptr;

};

#endif // !TILE_HEADER_H
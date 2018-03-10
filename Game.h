#ifndef GAME_HEADER
#define GAME_HEADER
#include "XEngine.h"
#include "Player1.h"
#include "MemoryManager.h"
#include "Explosion.h"
#include "FireUp.h"
#include "BombUp.h"
#include "KickBomb.h"
#include <vector>


using namespace X;

class Game
{
public:
	Game();
	void GameInitialize();
	void Update(float deltaTime);
	void Render();

	void MakeMap(int maxExplodableTiles = 115);

	void Collision(float deltaTime);

	void SetWallTile(char w)		{ wall = w; }
	void SetFloorTile(char f)		{ floor = f; }
	void SetExplodableTile(char e)	{ explodable = e; }
	int GetWallTile()				{ return wall; }
	int GetFloorTile()				{ return floor; }
	int GetExplodeTile()			{ return explodable; }

	void RegisterExplosion(Math::Vector2 mPosition, int mPower);

	Tile& GetTile(int x, int y)		{ return pTile[y*numCols + x]; }

	Explosion& GetNextExplosion()	{ return mExplosionArr[(mExplosionIndex + 1) % kMaxExplosions]; }
	void ActiveNextExplosion()		{ mExplosionArr[(++mExplosionIndex) % kMaxExplosions].Activate();  }

	const char* wallTile = "BrickGrass.png";
	const char* explodeTile = "QmarkGrass.png";
	const char* floorTile = "grassBG.png";
	int wall;
	int explodable;
	int floor;
	static const int numPlayers = 2;

	Player* players[numPlayers];
	MemoryManager* pMemMan;

	static const int kMaxPowerUps = 8;
	int powerUpIndex = 0;
	PowerUp *powerUp[kMaxPowerUps] = { nullptr };

	static const int kMaxExplosions = 400;
	Explosion mExplosionArr[kMaxExplosions];
	int mExplosionIndex = -1;

	Tile* pTile;
	int numRows = 15;
	int numCols = 15;

	// ==== AUDIO ======
	int quack_id;
	const char* quack = "Quack.mp3";

};

#endif // !GAME_HEADER
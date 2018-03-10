#include "Game.h"

namespace
{
	int bgm_id;
	const char* audiopath = "../Data/Sounds";
	const char* bgm = "BGM.mp3";


	const char* p1DownSprite[4] = { "BDown1.png", "BDown2.png", "BDown1.png", "BDown3.png" };
	const char* p1UpSprite[4] = { "BUp1.png", "BUp2.png", "BUp1.png", "BUp3.png" };
	const char* p1LeftSprite[4] = { "BLeft1.png", "BLeft2.png", "BLeft1.png", "BLeft3.png" };
	const char* p1RightSprite[4] = { "BRight1.png", "BRight2.png", "BRight1.png", "BRight3.png" };

	const char* p2DownSprite[4] = { "RDown1.png", "RDown2.png", "RDown1.png", "RDown3.png" };
	const char* p2UpSprite[4] = { "RUp1.png", "RUp2.png", "RUp1.png", "RUp3.png" };
	const char* p2LeftSprite[4] = { "RLeft1.png", "RLeft2.png", "RLeft1.png", "RLeft3.png" };
	const char* p2RightSprite[4] = { "RRight1.png", "RRight2.png", "RRight1.png", "RRight3.png" };

	const char* midFireSprite = { "FireMid.png" };
	const char* upFireSprite[2] = { "FireMidUp.png", "FireTop.png" };
	const char* downFireSprite[2] = { "FireMidDown.png", "FireBot.png" };
	const char* leftFireSprite[2] = { "FireMidLeft.png", "FireLeft.png" };
	const char* rightFireSprite[2] = { "FireMidRight.png", "FireRight.png" };

	const char* fireUpSprite = { "FireUp.png" };
	const char* bombUpSprite = { "BombUp.png" };
	const char* kickBombSprite = { "KickBomb.png" };


	int midFire;
	// up, right, down, left
	int dirFire[4][2];

	int fireUpPWR;
	int bombUpPWR;
	int kickPWR;

	// free function
	Math::Vector2 GetExpectedVelocity(Player& player, Tile& tile, float deltaTime)
	{
		Math::Vector2 retVal(0.f, 0.f);
		Math::Vector2 vel = player.GetVelocity();

		// move right
		if (vel.x > 0.f)
		{
			float expectedXPos = tile.GetPosition().x - 20;
			retVal.x = (expectedXPos - player.GetPosition().x) / deltaTime;
		}
		// move left
		else if (vel.x < 0.f)
		{
			float expectedXPos = tile.GetPosition().x + tile.GetHalfWidth() * 2;
			retVal.x = (expectedXPos - player.GetPosition().x) / deltaTime;
		}
		// move down
		else if (vel.y > 0.f)
		{
			float expectedYPos = tile.GetPosition().y - 30;
			retVal.y = (expectedYPos - player.GetPosition().y) / deltaTime;
		}
		// move up
		else if (vel.y < 0.f)
		{
			float expectedYPos = tile.GetPosition().y + tile.GetHalfHeight() * 2 - 11;
			retVal.y = (expectedYPos - player.GetPosition().y) / deltaTime;
		}
		
		return retVal;
	}

	template <typename T>
	void ShuffleArray(T*& arr, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			int randomIndex = X::RandomInt(0, size);
			T temp = arr[i];
			arr[i] = arr[randomIndex];
			arr[randomIndex] = temp;
		}
	}

	int GetTileNumber(const Math::Vector2& pos, int numCols)
	{
		int tileX = pos.x / 32;
		int tileY = pos.y / 32;
		return tileY * numCols + tileX;
	}
}

Game::Game()
{
	wallTile = "BrickGrass.png";
	explodeTile = "QmarkGrass.png";
	floorTile = "grassBG.png";
	wall = -1;
	explodable = -1;
	floor = -1;

	players[0] = new Player(*this, X::Keys::W, X::Keys::S, X::Keys::A, X::Keys::D, X::Keys::SPACE);
	players[1] = new Player(*this, X::Keys::UP, X::Keys::DOWN, X::Keys::LEFT, X::Keys::RIGHT, X::Keys::NUMPAD0);

}
// ========================================================== 
//							INITIALIZE
// ========================================================== 
void Game::GameInitialize()
{

	//========= AUDIO ==========
	X::SetAudioPath("../Data/Sounds");
	X::SetAudioPath(audiopath);
	bgm_id = X::LoadAudio(bgm);
	quack_id = X::LoadAudio(quack);

	X::SetTexturePath("../Data/Images");
	SetWallTile(X::LoadTexture(wallTile));
	SetFloorTile(X::LoadTexture(floorTile));
	SetExplodableTile(X::LoadTexture(explodeTile));

	X::PlayAudio(bgm_id, true, 1.0f, 1.0f, 0.5f);

	
	int p1Down[4];
	int p1Up[4];
	int p1Left[4];
	int p1Right[4];

	int p2Down[4];
	int p2Up[4];
	int p2Left[4];
	int p2Right[4];

	for (int i = 0; i < 4; i++)
	{
		p1Down[i] = X::LoadTexture(p1DownSprite[i]);
		p2Down[i] = X::LoadTexture(p2DownSprite[i]);
		p1Up[i] = X::LoadTexture(p1UpSprite[i]);
		p2Up[i] = X::LoadTexture(p2UpSprite[i]);
		p1Left[i] = X::LoadTexture(p1LeftSprite[i]);
		p2Left[i] = X::LoadTexture(p2LeftSprite[i]);
		p1Right[i] = X::LoadTexture(p1RightSprite[i]);
		p2Right[i] = X::LoadTexture(p2RightSprite[i]);
	}
	
	players[0]->Initialize(p1Down, p1Left, p1Up, p1Right);
	players[1]->Initialize(p2Down, p2Left, p2Up, p2Right);
	

	fireUpPWR = X::LoadTexture(fireUpSprite);
	bombUpPWR = X::LoadTexture(bombUpSprite);
	kickPWR = X::LoadTexture(kickBombSprite);

	FireUp::spriteIndex = fireUpPWR;
	BombUp::spriteIndex = bombUpPWR;
	KickBomb::spriteIndex = kickPWR;

	Tile::floor = floor;


	pMemMan = new MemoryManager();
	pTile = static_cast<Tile*>(pMemMan->Allocate(225));
	
	for (int i = 0; i < 225; ++i)
	{
		int numCol = i % 15;
		int numRow = i / 15;
		if (numCol == 0 || numCol == 14 || numRow < 1 || numRow > 13 || (i % 2 == 0 && (numCol % 2 == 0)))
		{
			pTile[i].SetSprite(GetWallTile());
			pTile[i].SetType(Tile::Type::Indestructable);
		}
		else
		{
			pTile[i].SetSprite(GetFloorTile());
		}
		pTile[i].SetPosX(numCol*32.f);
		pTile[i].SetPosY(numRow*32.f);
	}

	players[0]->SetPosX(38.f);
	players[0]->SetPosY(32.f);
	players[1]->SetPosX(424.0f);
	players[1]->SetPosY(416.0f);

	midFire = X::LoadTexture(midFireSprite);

	for (int i = 0; i < 2; i++)
	{
		dirFire[0][i] = X::LoadTexture(upFireSprite[i]);
		dirFire[1][i] = X::LoadTexture(rightFireSprite[i]);
		dirFire[2][i] = X::LoadTexture(downFireSprite[i]);
		dirFire[3][i] = X::LoadTexture(leftFireSprite[i]);
	}


}
// ========================================================== 
//							FILL BOARD
// ========================================================== 
void Game::MakeMap(int maxExplodableTiles)
{
	const int numPassableTiles = 133;
	bool* arr = new bool [numPassableTiles];
	
	int notExplodables = numPassableTiles - maxExplodableTiles;
	XASSERT(notExplodables > 0, "More explodable tiles than passable tiles");

	memset(arr, false, notExplodables);
	ShuffleArray(arr, numPassableTiles);

	int explodableIndex = 0;

	for (int i = 1; i < 14; ++i)
	{
		for (int j = 1; j < 14; ++j)
		{
			if (explodableIndex >= numPassableTiles)
			{
				break;
			}

			Tile& tile = GetTile(i, j);
			if (tile.GetType() == Tile::Type::Passable)
			{
				if (arr[explodableIndex++])
				{
					tile.SetType(Tile::Type::Destructible);
					tile.SetSprite(explodable);
				}
			}
		}
	}

	//player's position and adjasent tiles to blank
	pTile[16].SetPassableType(floor);
	pTile[17].SetPassableType(floor);
	pTile[31].SetPassableType(floor);
	pTile[208].SetPassableType(floor);
	pTile[207].SetPassableType(floor);
	pTile[193].SetPassableType(floor);
	pTile[16].SetSprite(floor);
	pTile[17].SetSprite(floor);
	pTile[31].SetSprite(floor);
	pTile[208].SetSprite(floor);
	pTile[207].SetSprite(floor);
	pTile[193].SetSprite(floor);

}
// ========================================================== 
//							UPDATE
// ========================================================== 
void Game::Update(float deltaTime)
{
	for (int i = 0; i < numPlayers; i++)
	{
		players[i]->Update(deltaTime);
		if (!players[0]->IsActive())
		{
			X::DrawScreenText("Player 2 Wins!", 120.0f, 200.0f, 0.0f, Math::Vector4(X::RandomFloat(0.0f,1.0f), X::RandomFloat(0.0f, 1.0f), X::RandomFloat(0.0f, 1.0f),1.0f));
		}
		else if (!players[1]->IsActive())
		{
			X::DrawScreenText("Player 1 Wins!", 120.0f, 200.0f, 0.0f, Math::Vector4(X::RandomFloat(0.0f, 1.0f), X::RandomFloat(0.0f, 1.0f), X::RandomFloat(0.0f, 1.0f), 1.0f));
		}
	
	}

	for (int i = 0; i < kMaxExplosions; i++)
	{
		if (mExplosionArr[i].IsActive())
		{
			mExplosionArr[i].Update(deltaTime);
		}
	}

	Collision(deltaTime);

	for (int i = 0; i < numPlayers; i++)
	{
		players[i]->PostUpdate(deltaTime);
	}


}
// ========================================================== 
//							RENDER
// ========================================================== 
void Game::Render()
{
	for (int i = 0; i < kMaxPowerUps; i++)	
	{
		if (powerUp[i] != nullptr && powerUp[i]->IsActive())
		{
 			powerUp[i]->Render();
		}
	}

	for (int i = 0; i < numPlayers; i++)
	{
		players[i]->Render();
	}

	for (int i = 0; i < kMaxExplosions; i++)
	{
		if (mExplosionArr[i].IsActive())
		{
			mExplosionArr[i].Render();
		}
	}


}
// ========================================================== 
//							EXPLOSION
// ========================================================== 
void Game::RegisterExplosion(Math::Vector2 position, int power)
{
	int tileX = position.x / 32;
	int tileY = position.y / 32;
	int chance;

	Tile& tile = GetTile(tileX, tileY);	

	Explosion& explosion = GetNextExplosion();
	explosion.SetPosition(tile.GetPosition());
	explosion.SetSprite(midFire);

	ActiveNextExplosion();

	int i;
	bool exploded = false;

	// up right down left
	int xDiff[4] = { 0, 1, 0, -1 };
	int yDiff[4] = { -1, 0, 1, 0 };

	// up, right, down, left
	for (int dir = 0; dir < 4; ++dir)
	{
		exploded = false;
		for (i = 1; i <= power; ++i)
		{
			Tile& currTile = GetTile(tileX + xDiff[dir] * i, tileY + yDiff[dir] * i);
			Explosion& currExplosion = GetNextExplosion();
			currExplosion.SetPosition(currTile.GetPosition());
			currExplosion.SetSprite(dirFire[dir][0]);

			if (currTile.GetType() == Tile::Type::Passable)
			{				
				exploded = true;
				ActiveNextExplosion();
			}

			else if (currTile.GetType() == Tile::Type::Powerup)
			{
				exploded = true;
				int currPowerUpIndex = currTile.GetPowerUpIndex();
				currTile.SetPassableType(floor);
				delete powerUp[currPowerUpIndex];
				powerUp[currPowerUpIndex]= nullptr;
				ActiveNextExplosion();
			}

			else if (currTile.GetType() == Tile::Type::Destructible)
			{
				chance = X::RandomInt(1, 100);
				currTile.SetPassableType(floor);
				
				// =========================
				//		SPAWN FIRE UP
				// =========================
				if (chance <= 15) 
				{
					for (int i = 0; i < kMaxPowerUps; i++)
					{
						if (powerUp[i] == nullptr)
						{
							powerUp[i] = new FireUp(fireUpPWR, currTile.GetPosition());
							currTile.SetPowerType(fireUpPWR, i);
							break;
						}
					}
				}

				// =======================
				//		SPAWN BOMB UP
				// =======================
				if (chance > 15 && chance <= 30)
				{
					for (int i = 0; i < kMaxPowerUps; i++)
					{
						if (powerUp[i] == nullptr)
						{
							powerUp[i] = new BombUp(bombUpPWR, currTile.GetPosition());
							currTile.SetPowerType(bombUpPWR, i);
							break;
						}
					}
				}

				// =======================
				//		SPAWN KICK BOMB
				// =======================
				if (chance > 30 && chance <= 40)
				{
					for (int i = 0; i < kMaxPowerUps; i++)
					{
						if (powerUp[i] == nullptr)
						{
							powerUp[i] = new KickBomb(kickPWR, currTile.GetPosition());
							currTile.SetPowerType(kickPWR, i);
							break;
						}
					}
				}
				ActiveNextExplosion();
				break;
			}

			else if (currTile.GetType() == Tile::Type::Indestructable)
				break;

			else if (currTile.GetType() == Tile::Type::Bomb)
			{
				exploded = true;
				ActiveNextExplosion();
				currTile.GetBomb()->Explode();
			}
		}
		if (exploded)
		{
			mExplosionArr[mExplosionIndex].SetSprite(dirFire[dir][1]);
		}
	}
}
// ========================================================== 
//							COLLISION
// ========================================================== 
void Game::Collision(float deltaTime)
{
	// ==================================
	//          PLAYER COLLISIONS
	// ==================================
	for (int i = 0; i < numPlayers; i++)
	{
		Player& player = *players[i];

		for (int i = 0; i < kMaxExplosions; i++)
		{
			if(mExplosionArr[i].IsActive())
			{
				if (Math::Intersect(mExplosionArr[i].GetBoundingRect(), player.GetBoundingRect()))
				{
					player.Destroy();
				}
			}
		}

		Math::Vector2 vel = player.GetVelocity();
		Math::Vector2 direction = (vel.x == 0.f && vel.y == 0.f) ? Math::Vector2::Zero() : Math::Normalize(vel);
		Math::Vector2 futurePos = player.GetCenter() + Math::Vector2(player.GetHalfDim().x * direction.x, player.GetHalfDim().y * direction.y) + vel * deltaTime;
	
		int tileNumber = ::GetTileNumber(futurePos, numCols);
		Tile& currTile = pTile[tileNumber];
		int currPowerUpIndex;
	
		switch (currTile.GetType())
		{
			case Tile::Type::Bomb:
				if (!player.justPlacedBomb)
				{					
					player.SetVelocity(::GetExpectedVelocity(player, currTile, deltaTime));
					Bomb* bomb = currTile.GetBomb();
				
					if (player.CanKick() && !bomb->IsMoving())
					{
						bomb->SetMoving(true);
						currTile.SetPassableType(floor);
						bomb->SetDirection(direction);
					}
				}
				break;

			case Tile::Type::Indestructable:				
			case Tile::Type::Destructible:
				player.SetVelocity(::GetExpectedVelocity(player, currTile, deltaTime));
				break;

			case Tile::Type::Powerup:
				currPowerUpIndex = currTile.GetPowerUpIndex();
				currTile.SetPassableType(floor);
				powerUp[currPowerUpIndex]->Collect(player);
				delete powerUp[currPowerUpIndex];
				powerUp[currPowerUpIndex] = nullptr;

			case Tile::Type::Passable:
				player.justPlacedBomb = false;
				break;		
			default: XASSERT(true, "YOU MESSED UP");
		}
	}


	//=================================
	//		 MOVING BOMB COLLISION
	//=================================	
	for (int j = 0; j < numPlayers; j++)
	{

		Player& bombPlayer = *players[j];
		for (int k = 0; k < bombPlayer.kMaxBombs; k++)
		{
			Bomb& currBomb = bombPlayer.bombArr[k];
			if (currBomb.IsMoving())
			{

				Math::Vector2 bombPos = currBomb.GetPosition();
				Math::Vector2 vel = currBomb.GetVelocity();
				Math::Vector2 direction = (vel.x == 0.f && vel.y == 0.f) ? Math::Vector2::Zero() : Math::Normalize(vel);
				Math::Vector2 currPos = currBomb.GetCenter() + Math::Vector2(16 * direction.x, 16 * direction.y);
				Math::Vector2 futurePos = currPos + vel * deltaTime;

				int currTileNumber = ::GetTileNumber(currPos, numCols);
				int futureTileNumber = ::GetTileNumber(futurePos, numCols);

				if (currTileNumber == futureTileNumber)
				{
					continue;
				}

				Tile& currTile = pTile[currTileNumber];
				Tile& futureTile = pTile[futureTileNumber];				

				for (int i = 0; i < numPlayers; ++i)
				{
					Player& collidingPlayer = *players[i];
					Math::Vector2 futureColPlayerPos = collidingPlayer.GetPosition() + collidingPlayer.GetVelocity() * deltaTime;

					int playerTileNum = ::GetTileNumber(futureColPlayerPos, numCols);
					if (playerTileNum == futureTileNumber)
					{
						currBomb.SetMoving(false);
						currBomb.SetCenter(currTile.GetPosition());
						continue;
					}

					Tile& playerTile = pTile[playerTileNum];
				}
				int currPowerUpIndex;

				switch (futureTile.GetType())
				{
				case Tile::Type::Bomb:
				case Tile::Type::Indestructable:
				case Tile::Type::Destructible:
					currBomb.SetMoving(false);
					currBomb.SetPosition(currTile.GetPosition());
					break;

				case Tile::Type::Powerup:
					currPowerUpIndex = futureTile.GetPowerUpIndex();
					futureTile.SetPassableType(floor);
					delete powerUp[currPowerUpIndex];
					powerUp[currPowerUpIndex] = nullptr;

				case Tile::Type::Passable:
					if (currTile.GetPowerUpIndex() == -1)
					{
						currTile.SetPassableType(floor);
					}
					else
					{
						currTile.SetPowerType(powerUp[currTile.GetPowerUpIndex()]->spriteIndex, currTile.GetPowerUpIndex());
					}

					futureTile.SetBombType(&currBomb);
					currBomb.SetTile(&futureTile);
					break;
				default: XASSERT(true, "YOU MESSED UP");
				}
			}
		}
	}
}


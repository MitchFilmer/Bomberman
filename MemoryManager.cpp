#include "MemoryManager.h"
#include "Tile.h"

MemoryManager::MemoryManager()
{
	_location = static_cast<void*>(memory);
}

MemoryManager::~MemoryManager()
{

}

void *MemoryManager::Allocate(int numTiles)
{
	if (currentIndex + numTiles < kSize)
	{
		Tile* t = new(_location) Tile[numTiles];
		Tile* mem = (Tile*)_location;
		mem += numTiles;
		_location = mem;
		return t;
	}
	return nullptr;
}

void MemoryManager::Deallocate(int numTiles)
{
	if (currentIndex < numTiles)
	{
		return;
	}

	Tile* pTile = (Tile*)_location;

	for (int i = numTiles; i > 0; ++i)
	{
		pTile--;
		pTile->~Tile();
	}

	_location = static_cast<void*>(pTile);
	currentIndex -= numTiles;

}
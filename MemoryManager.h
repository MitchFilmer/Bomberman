#ifndef MEMORY_MANAGER_HEADER_H
#define MEMORY_MANAGER_HEADER_H
#include "Tile.h"

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();

	void* Allocate(int numTiles);
	void Deallocate(int numTiles);
	void* GetLocation() { return _location; }

private:
	void* _location = nullptr;
	static const int kSize = 226;
	char memory[kSize * sizeof(Tile)];
	int currentIndex = 0;
};

#endif // !MEMORY_MANAGER_HEADER_H
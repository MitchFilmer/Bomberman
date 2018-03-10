#include <XEngine.h>
#include "Tile.h"
#include "MemoryManager.h" 
#include "Game.h"

Game *game;

void Initialize();
void RenderTiles();
void Terminate();

bool GameLoop(float deltaTime)
{
	RenderTiles();
	game->Update(deltaTime);
	game->Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	X::Start("Notice me Craig-senpai", hInstance, 480, 480, 0);
	Initialize();
	X::Run(GameLoop);
	Terminate();
	X::Stop();
	return 0;
}

void Initialize()
{
	game = new Game();
	game->GameInitialize();
	game->MakeMap(100);
}

void RenderTiles()
{
	for (int i = 0; i < 225; i++)
	{
		X::DrawSprite(game->pTile[i].GetSprite(), game->pTile[i].GetPosition());
	}
}

void Terminate()
{
	game->pMemMan->Deallocate(25);
	delete game->pMemMan;
	delete game;

}
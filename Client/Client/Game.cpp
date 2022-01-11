#include "pch.h"
#include "Game.h"
#include "GameEngine.h"


void Game::Initialize(const WindowInfo& winfo)
{
	GEngine->Initialize(winfo);

}

void Game::Update()
{
	GEngine->Update();
}

void Game::Render()
{
	GEngine->Render();
}

void Game::CallScreenResize(const WindowInfo& wInfo)
{
	GEngine->CallScreenResize(wInfo);
}

#include "GameInstance.h"
#include "../gui/GPanel.h"
#include "../gui/GButton.h"
#include "../gui/GMenu.h"
#include "../item/Item.h"
#include "../ECS/Components/Items/Inventory.h"
GameInstance::GameInstance()
{
	
}


GameInstance::~GameInstance()
{
}

void GameInstance::loadSDL(int w, int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return;
	}
	window = new GameWindow();
	if (window == NULL)
	{
		return;
	}
	window->init(w, h);
	renderer = window->createRenderer();
	Texture::renderer = renderer;
	if (renderer == NULL)
	{
		return;

	}	
	else
	{
		
		//Initialize renderer color
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xFF);
		SDL_RenderClear(renderer);
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return;

		}

		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			return;
		}

		//set renderTarget
		windowTexture = new Texture();
		windowTexture->createBlank(30 * 32, 30 * 32, renderer);

		
		
	}
}

void GameInstance::initUI()
{
	ui = new GBase();
	//GPanel * menuPanel = new GPanel();
	//menuPanel->setX(0);
	//menuPanel->setY(0);
//	menuPanel->resize(150, 400);
//	menuPanel->Init();
	//GButton * ButtonTest = new GButton(5,0,140,75);
	//ButtonTest->setParent(menuPanel);
	//ButtonTest->setColor(25, 25, 25, 254);
	
	CurrentLevel->createGameUI(renderer, ui);
	
	
	

}

void GameInstance::InitMap()
{
	
	CurrentLevel = new Level(this->ui);
	CurrentLevel->Gen(this->renderer);
	initUI();
}

void GameInstance::ProcessInput(SDL_Event &e)
{
	while (SDL_PollEvent(&e) != 0)
	{
		window->handleEvent(e);
		if (CurrentLevel != nullptr)
		{
			CurrentLevel->ProcessInput(e);
		}
		ui->ProcessInput(e);

		
	}
}


void GameInstance::UpdateGame()
{

	if (CurrentLevel != nullptr)
	{
		CurrentLevel->UpdateGame();
	}
}

void GameInstance::DrawGame()
{
	if (!window->isMinimized())
	{
		
		windowTexture->setAsRenderTarget(renderer);
		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		CurrentLevel->DrawGame(renderer);
		ui->Draw(renderer);
		//g->Draw();


		SDL_SetRenderTarget(renderer, nullptr);


		windowTexture->stretchRender(0, 0, renderer, window->getWidth(), window->getHeight());
		//Update screen
		SDL_RenderPresent(renderer);
	}
}

void GameInstance::Shutdown()
{
	CurrentLevel->Shutdown();
}

void GameInstance::Debug()
{
	

}

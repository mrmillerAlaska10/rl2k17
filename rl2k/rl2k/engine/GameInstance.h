#pragma once
/* Responsible as a middle point for user input and the game map. Also holds the window and 
rendering data.
*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GameWindow.h"
#include "../map/Map.h"
#include "../map/Level.h"
#include "../gui/GBase.h"

#include "../font/GMessage.h"
class GameInstance
{
public:
	GameInstance();
	~GameInstance();

	void loadSDL(int windowWidth, int windowHeight);
	void initUI();
	void InitMap();


	//get user input
	void ProcessInput(SDL_Event &e);
	//if current users turn, process command. If ai turn run AI and process ai turn.
	//otherwise determine next turn.
	void UpdateGame();

	//Draw map, items, enemies, player, ui
	void DrawGame();
	//shutdown map, deinitialize SDL
	void Shutdown();

	void Debug();

private:
	SDL_Renderer * renderer;
	GameWindow * window;
	Texture * windowTexture;//for resizing
	Level * CurrentLevel;
	GBase *ui;


	GMessage * g;
};



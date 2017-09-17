#include "GameWindow.h"
#include <sstream>
using namespace std;

GameWindow::GameWindow()
{ 
	//Initialize non-existant window
	window = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
}

bool GameWindow::init(int w, int h)
{
	//Create window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window != NULL)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = w;
		mHeight = h;
	}

	return window != NULL;
}

SDL_Renderer * GameWindow::createRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return renderer;
}

void GameWindow::handleEvent(SDL_Event & e)
{ 
	//Window event occured
	if (e.type == SDL_WINDOWEVENT)
	{
		//Caption update flag
		bool updateCaption = false;
		switch (e.window.event)
		{
			//Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent(renderer);
			break;

			//Repaint on exposure
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer);
			break;
			//Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Window lost keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;
			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		}
		//Update window caption with new data
		if (updateCaption)
		{
			std::stringstream caption;
			caption << "SDL Tutorial - MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(window, caption.str().c_str());
		} //Enter exit full screen on return key
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
		{
			if (mFullScreen)
			{
				SDL_SetWindowFullscreen(window, SDL_FALSE);
				mFullScreen = false;
			}
			else
			{
				SDL_SetWindowFullscreen(window, SDL_TRUE);
				mFullScreen = true;
				mMinimized = false;
			}
		}
	}
}

void GameWindow::free()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}
int GameWindow::getWidth()
{
	return mWidth;
}

int GameWindow::getHeight()
{
	return mHeight;
}

bool GameWindow::hasMouseFocus()
{
	return mMouseFocus;
}

bool GameWindow::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool GameWindow::isMinimized()
{
	return mMinimized;
}


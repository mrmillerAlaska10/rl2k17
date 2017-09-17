#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;
class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	bool loadFromFile(std::string path, SDL_Renderer * renderer);

	bool loadFromRenderedText(std::string textureText, TTF_Font * gFont, SDL_Color textColor, SDL_Renderer * gRenderer);

	static SDL_Renderer * renderer;
	



	//Creates blank texture
	bool createBlank(int width, int height, SDL_Renderer * gRenderer);
	bool createTransparentTexture(int width, int height, SDL_Renderer * gRenderer);
	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	
	
	
	//Renders texture at given point
	void render(int x, int y, SDL_Renderer * gRenderer, SDL_Rect * clip = NULL, SDL_Rect * quad = NULL, double angle = 0, SDL_Point * center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void stretchRender(int x, int y, SDL_Renderer * gRenderer, int width, int height);
	//Set self as render target
	void setAsRenderTarget(SDL_Renderer * renderer);


	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	void copyPixels(void* pixels);
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	void* mPixels;
	int mPitch;

	//Image dimensions
	int mWidth;
	int mHeight;
};

#include "Texture.h"

//reference renderer
SDL_Renderer * Texture::renderer = 0;


Texture::Texture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPixels = NULL;
	mPitch = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer * gRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			printf("Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch);

				//Copy loaded/formatted surface pixels
				memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)mPixels;
				int pixelCount = (mPitch / 4) * mHeight;

				//Map colors				
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF);
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				mPixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, TTF_Font *gFont ,SDL_Color textColor, SDL_Renderer * gRenderer)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}

bool Texture::createBlank(int width, int height, SDL_Renderer * gRenderer)
{
	//Create uninitialized texture
	mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(mTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	
	SDL_SetRenderTarget(renderer, mTexture);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
	if (mTexture == NULL)
	{
		printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		mWidth = width;
		mHeight = height;
	}

	return mTexture != NULL;
}

bool Texture::createTransparentTexture(int width, int height, SDL_Renderer * gRenderer)
{
	//Create uninitialized texture
	mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(mTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, mTexture);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
	if (mTexture == NULL)
	{
		printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		mWidth = width;
		mHeight = height;
	}

	return mTexture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mPixels = NULL;
		mPitch = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, SDL_Renderer * gRenderer, SDL_Rect * clip, SDL_Rect * quad, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_Rect * srcRect = NULL;
	if (clip != NULL)
	{
		srcRect = new SDL_Rect{ clip->x, clip->y, clip->w, clip->h };
	}
	
	if (quad != NULL)
	{
		srcRect->w = quad->w;
		srcRect->h = quad->h;
	}

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, srcRect, &renderQuad, angle, center, flip);
	delete srcRect;
}

void Texture::stretchRender(int x, int y, SDL_Renderer * gRenderer, int width, int height)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, nullptr, &renderQuad, 0, nullptr, SDL_FLIP_NONE);
}

void Texture::setAsRenderTarget(SDL_Renderer * gRenderer)
{
	//Make self render target
	SDL_SetRenderTarget(gRenderer, mTexture);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}

bool Texture::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if (mPixels != NULL)
	{
		printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

bool Texture::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if (mPixels == NULL)
	{
		printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(mTexture);
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* Texture::getPixels()
{
	return mPixels;
}

void Texture::copyPixels(void* pixels)
{
	//Texture is locked
	if (mPixels != NULL)
	{
		//Copy to locked pixels
		memcpy(mPixels, pixels, mPitch * mHeight);
	}
}

int Texture::getPitch()
{
	return mPitch;
}

Uint32 Texture::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)mPixels;

	//Get the pixel requested
	return pixels[(y * (mPitch / 4)) + x];
}

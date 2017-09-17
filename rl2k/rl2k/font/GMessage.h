#pragma once
#include <string>
#include "../engine/graphics/Texture.h"
#include "GFont.h"
using namespace std;
//a string, and tools to render it with a GFont. If the message changes, 
class GMessage
{
public:
	
	GMessage(SDL_Renderer * renderer);
	~GMessage();

	void Write(string Message);
	void Draw(int x = 0, int y = 0);

	int lineWidth = 0;	
	int maxLines = 0;
	int maxHeight = 0;
	int maxWidth = 0;
private:
	//if the message changes, the font changes, or any text properties change, then the texture is dirty.
	//if the texture is dirty, it must be recreated with the new properties before being drawn.
	bool dirty = true;	
	void Reload();

	string Message;
	string PreviousMessage;
	Texture * drawTexture;
	SDL_Renderer * renderer;
	GFont * font;
};


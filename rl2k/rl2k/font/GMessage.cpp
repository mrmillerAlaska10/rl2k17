#include "GMessage.h"
#include "../util/ExpressionParser.h"


GMessage::GMessage(SDL_Renderer * renderer)
{
	font = new GFont();
	this->renderer = renderer;
}


GMessage::~GMessage()
{
}

void GMessage::Write(string Message)
{
	drawTexture = new Texture();
	this->Message = Message;
	dirty = true;
}

void GMessage::Draw(int x, int y)
{
	if (dirty)
	{
		Reload();
	}
	drawTexture->render(x,y, renderer);

}

void GMessage::Reload()
{
	vector<string> split = ExpressionParser::split(Message, lineWidth, '\n');
	
	
	
	

	
	//get first line
	

	//height = number of lines * line height
	int megatexheight = 0;// lineTex->getHeight() * split.size();
	int megatexwidth = 0;
	
	
	vector<Texture*> lines;
	for (int i = 0; i < split.size(); i++)
	{
		Texture * lineTex = new Texture();
		lineTex->loadFromRenderedText(split[i], font->getFont(), SDL_Color{ 0,0,255 }, renderer);
		if (lineTex->getWidth() > megatexwidth)
		{
			megatexwidth = lineTex->getWidth();
		}		
		lines.push_back(lineTex);
	}
	megatexheight = lines[0]->getHeight() * lines.size();
	if (megatexheight > maxHeight && maxHeight != 0)
	{
		megatexheight = maxHeight;
	}

	if (split.size() > maxLines && maxLines != 0)
	{
		megatexheight = maxLines * lines[0]->getHeight();
	}

	if (megatexwidth > maxWidth && maxWidth != 0)
	{
		megatexwidth = maxWidth;
	}
	//draw lines onto texture

	drawTexture = new Texture();
	drawTexture->createTransparentTexture(megatexwidth, megatexheight, renderer);
	

	SDL_Texture * t = SDL_GetRenderTarget(renderer);	//previous render target
	drawTexture->setAsRenderTarget(renderer);
	for (int i = 0; i < split.size(); i++)
	{
		lines[i]->render(0, i*lines[0]->getHeight(), renderer);
	}

	
	SDL_SetRenderTarget(renderer, t);


	

	
	dirty = false;
}

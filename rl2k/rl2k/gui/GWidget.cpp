#include "GWidget.h"
#include <iostream>
class Actor;
using namespace std;
GWidget::GWidget()
{
}
GWidget::~GWidget()
{
}
void GWidget::ProcessInput(SDL_Event & e)
{
	Input(e);
	//for (int i = 0; i < children.size(); i++)
	//{
		//children[i]->ProcessInput(e);
	//}
}

void GWidget::Draw(SDL_Renderer * renderer)
{
	if (this->hidden == true)
		return;
	this->Render(renderer);
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Draw(renderer);
	}
}

void GWidget::Refresh()
{
	if (onRefresh != 0)
	{
		onRefresh();

	}
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Refresh();
	}
}

void GWidget::resize(int w, int h)
{
	this->width = w;
	this->height = h;
}

void GWidget::setX(int x)
{
	//How many units the widget is moving
	int deltaX = x - this->x;


	this->x = x;
	//all children need to be moved delta units
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->addX(deltaX);
	}
}

void GWidget::setY(int y)
{
	//How many units the widget is moving
	int deltaY = y - this->y;


	this->y = y;
	//all children need to be moved delta units
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->addX(deltaY);
	}
}

void GWidget::addX(int add)
{
	this->x += add;
	//all children need adjusted
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->addX(add);
	}
}

void GWidget::addY(int add)
{
	this->y += add;
	//all children need adjusted
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->addY(add);
	}
}

void GWidget::setParent(GWidget * widget)
{
	this->parent = widget;
	parent->children.push_back(this);
	//try to keep position relative to parent
	this->addX(parent->x);
	this->addY(parent->y);
}

void GWidget::setColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A)
{
	Background->setColor(R, G, B);
	Background->setAlpha(A);
}

int GWidget::getX()
{
	return x;
}

int GWidget::getY()
{
	return y;
}

int GWidget::getWidth()
{
	return width;
}

int GWidget::getHeight()
{
	return height;
}

void GWidget::CreateWidget(GBase * container)
{
	this->container = container;
	parent = 0;
	x = y = width = height = 0;
}

void GWidget::WidgetInit()
{
	Background = new Texture();
	Background->createBlank(this->width, this->height, Texture::renderer);

	setColor(50, 50, 50, 200);
}

void GWidget::Input(SDL_Event & e)
{
	DetectEvents( e);
}

void GWidget::DetectEvents(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		/* If the left button was pressed. */
		if (e.button.button == SDL_BUTTON_LEFT)
			/* Quit the application */
			WasClicked();
	}
}

void GWidget::setVisibility(bool visible)
{
	this->hidden = visible;
}

void GWidget::toggleVisibility()
{
	hidden = !hidden;
}

bool GWidget::WasClicked()
{
	bool stop = false;
	for (int i = 0; i < children.size(); i++ )
	{
		//if another child was already activated, don't double trigger
		if (stop == false)
		{
			//when a child is activated, stop = true
			if (children[i]->WasClicked() == true)
			{
				stop = true;
			}
		}
	}
	//if a child is activated, return true
	if (stop == true)
	{
		return true;
	}
	else
	{



		//else check if clicked
		int mX, mY;
		SDL_GetMouseState(&mX, &mY);
		if (mX > x && mX <= x + width && mY > y && mY < y + height)
		{
			Click();
			return true;
		}
		//if not click, return false
		else
		{
			return false;
		}
	}
}

bool GWidget::Click()
{
	cout << "click";
	return false;
}

#include "Camera.h"



Camera::Camera() :position(SDL_Rect{ 0,0,0,0 }), boundaryX(80), boundaryY(0)
{
}

Camera::Camera(int x, int y, int width, int height, int bX, int bY) : position(SDL_Rect{ 0,0,0,0 }), boundaryX(bX), boundaryY(bY)
{
	position = SDL_Rect{ x,y,width, height };

}
Camera::~Camera()
{
}

void Camera::HandleInput(SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_UP:
		if(position.y > 0)
		position.y--;
		
		break;
	case SDLK_DOWN:
		if(position.y < boundaryY-position.h)
		position.y++;
		break;
	case SDLK_LEFT:
		if (position.x > 0)
		{
			position.x--;
		}
		break;
	case SDLK_RIGHT:
		if (position.x <  boundaryX - this->position.w)
		{
			position.x++;
		}
		break;
	default:		
		break;
	}
	CameraCheckBounds();
}

void Camera::CameraCheckBounds()
{
	if (position.x < 0)
	{
		position.x = 0;
	}
	if (position.y < 0)
	{
		position.y = 0;
	}
	if (position.x + position.w > boundaryX)
	{
		position.x = boundaryX - position.w;
	}
	if (position.y + position.h > boundaryY)
	{
		position.y = boundaryY - position.h;
	}
}


void Camera::set(int px, int py, bool center)
{
	
		position.x = px -15;
		position.y = py - 15;
	
	CameraCheckBounds(); 
		int z = 2;

	
	

}

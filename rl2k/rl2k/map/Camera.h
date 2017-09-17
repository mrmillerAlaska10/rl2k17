#pragma once
#include <SDL.h>
class Camera
{
public:
	Camera();

	Camera(int x, int y, int width, int height, int boundaryX = 100, int boundaryY = 100);

	~Camera();

	void HandleInput(SDL_Event &e);

	void CameraCheckBounds();
	

	void set(int x, int y, bool center = true);
	int boundaryX, boundaryY;
	SDL_Rect position;
	bool freelook = true;
};


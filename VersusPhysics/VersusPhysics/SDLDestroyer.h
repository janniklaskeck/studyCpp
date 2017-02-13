#pragma once
#include <SDL.h>

struct SDLWindowDestroyer
{
	void operator()(SDL_Window* window) const
	{
		SDL_DestroyWindow(window);
	}
};

struct SDLRendererDestroyer
{
	void operator()(SDL_Renderer* Renderer) const
	{
		SDL_DestroyRenderer(Renderer);
	}
};

struct SDLSurfaceDestroyer
{
	void operator()(SDL_Surface* Surface) const
	{
		SDL_FreeSurface(Surface);
	}
};

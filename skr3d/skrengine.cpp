#include "skrengine.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
namespace skrengine
{
	int init()
	{
		// INIT SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// Set GL to double buffering mode
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}
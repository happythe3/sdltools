#include "sdltWindowDetails.h"

using namespace sdlt;

WindowDetails::WindowDetails(SDL_Window * window, SDL_Renderer * renderer)
	:windowPtr{ window }, rendererPtr{ renderer }
{
}

WindowDetails::~WindowDetails()
{
	SDL_DestroyRenderer(rendererPtr);
	SDL_DestroyWindow(windowPtr);
}
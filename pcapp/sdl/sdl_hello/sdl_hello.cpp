#include <unistd.h>
#include <SDL/SDL.h>
int main(void)
{
	SDL_Surface* hello = NULL;
	SDL_Surface* screen = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	sleep(10);
	SDL_Quit();

	return 0;
}

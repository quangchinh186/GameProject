#include "game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    const int fps = 60;
    const int delay = 1000/fps;

    Uint32 frameStart;
    int frametime;
	game = new Game();
	game->init("GameWindow", 1200, 800, false);

	while (game->running())
	{
	    frameStart = SDL_GetTicks();
		game->handleEvents();
        game->update();

		game->render();

		frametime = SDL_GetTicks() - frameStart;
        if(delay > frametime){
            SDL_Delay(delay - frametime);
        }
	}

	game->clean();
    std::cout << "Game Over !" << std::endl;

	return 0;
}


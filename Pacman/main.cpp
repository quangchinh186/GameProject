#include "game.h"
#include <fstream>

Game *game = nullptr;

int main(int argc, char *argv[])
{
    const int fps = 60;
    const int delay = 1000/fps;
    Uint32 frameStart;
    int frametime;
	game = new Game();
	game->init("Pacman", 1400, 800, false);

	std::fstream score;
	score.open("highscore.txt", std::ios_base::in);
	if(score.is_open()){
        score >> game->high_score;
        score.close();
	}

	while (game->running())
	{
	    frameStart = SDL_GetTicks();
	    game->handleEvents();
	    game->render();
	    game->render_all();
	    game->play_sound();

	    if(game->is_pause){
            game->handleEvents();
            continue;
	    }
	    else{
            game->update();
	    }

        if(game->score > game->high_score){
            game->high_score = game->score;
        }

		frametime = SDL_GetTicks() - frameStart;
        if(delay > frametime){
            SDL_Delay(delay - frametime);
        }
	}


    score.open("highscore.txt", std::ios_base::out);
	if(score.is_open()){
        score << game->high_score;
        score.close();
	}

	game->clean();

	return 0;
}


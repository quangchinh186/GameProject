#ifndef GAME_h
#define GAME_h

#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <cmath>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	bool is_pause = false;
	bool is_muted = false;
	void render();
	void render_all();
	void play_sound();
	void clean();

	static SDL_Renderer *renderer;
	int cherri;
	int score = 0, lives = 3;
	int high_score;

private:
	bool isRunning = false;
	SDL_Window *window;
	SDL_Texture* player_lives;
	SDL_Texture* win_screen;
	SDL_Texture* pause_screen;
	SDL_Texture* retry_screen;
	SDL_Texture* lost_screen;
	SDL_Rect render_rect;
    Mix_Music* waka;
    Mix_Music* power;
    Mix_Chunk* die;

};


#endif // GAME_h


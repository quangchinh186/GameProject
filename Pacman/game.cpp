#include "game.h"
#include "load_image.h"
#include "player.h"
#include "map.h"
#include "ghost.h"


player* pacman;
SDL_Renderer* Game::renderer = nullptr;
map* gamemap;
const int fps = 60;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
		pacman = new player("image/pacman.png", 560, 480, 3);
		gamemap = new map;
		gamemap->create_map();
	}
}

int d = 0;

void Game::handleEvents()
{
	SDL_Event e;
	if(SDL_PollEvent(&e) == 0){}
    else if(e.type == SDL_QUIT){
            isRunning = false;
    }
    else if(e.type == SDL_KEYDOWN){
        std::cout << SDL_GetKeyName(e.key.keysym.sym) << std::endl;
        switch(e.key.keysym.sym){
            case SDLK_d:
            d = 0;
            break;

            case SDLK_s:
            d = 1;
            break;

            case SDLK_a:
            d = 2;
            break;

            case SDLK_w:
            d = 3;
            break;

            default:
            break;
            }
    }

}
int change_frame = 0, speed = 6;

void Game::update()
{
    change_frame++;
    if(fps / change_frame == speed){
        change_frame = 0;
        pacman->sprite(d);
    }
    pacman->action(d);
    gamemap->update_map(pacman->xpos, pacman->ypos);

}

void Game::render()
{

	SDL_RenderClear(renderer);
	gamemap->loadmap();
	pacman->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

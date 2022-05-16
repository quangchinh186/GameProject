#include "game.h"
#include "load_image.h"
#include "player.h"
#include "map.h"
#include "ghost.h"
#include <cstdlib>
#include <ctime>


player* pacman;
ghost* red;
ghost* pink;
ghost* blue;
ghost* orange;

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
		red = new ghost(40, 40, 0);
		pink = new ghost(1120, 40, 1);
		blue = new ghost(120, 640, 2);
		orange = new ghost(1040, 640, 3);
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
    if(gamemap->win()){
        isRunning = false;
        std::cout << "You Won !!!" << std::endl;
    }

    if(pacman->dead){
        isRunning = false;
        std::cout << "Game Over !" << std::endl;
    }
    change_frame++;
    if(fps / change_frame == speed){
        change_frame = 0;
        pacman->sprite(d);
    }
    int x = pacman->xpos, y = pacman->ypos;
    int x_rand = rand() % 1200 + 1, y_rand = rand() % 800 + 1;

    pacman->action(d);
    red->chase(x, y, red->facing);
    pink->chase(x_rand, y_rand, pink->facing);
    blue->chase(x_rand , x_rand, blue->facing);
    orange->chase(y_rand , y_rand, orange->facing);
    gamemap->update_map(x, y);
    cherri = gamemap->cherri_left;
    if(red->meet(x, y) || pink->meet(x, y) || blue->meet(x, y) || orange->meet(x, y)){
        pacman->dead = true;

    }else{

    }
    std::cout << "here" << std::endl;
    //std::cout << red->xcoor << " " << red->ycoor << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	gamemap->loadmap();
	pacman->render();
	red->render(cherri);
	pink->render(cherri);
	blue->render(cherri);
	orange->render(cherri);
	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

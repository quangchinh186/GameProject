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
int safe_house_x, safe_house_y;

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

	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO ) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		TTF_Init();
		waka = Mix_LoadWAV("wakawaka.wav");
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
	isRunning = true;
    pacman = new player("image/pacman.png", 560, 480, 3);
    red = new ghost(40, 40, 0);
    pink = new ghost(1120, 40, 1);
    blue = new ghost(120, 640, 2);
    orange = new ghost(1040, 640, 3);
    gamemap = new map;
    gamemap->create_map();
    cherri = gamemap->cherri_left;
    gamemap->get_safehouse(safe_house_x, safe_house_y);
    is_pause = true;
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
            case SDLK_r:
            if(pacman->dead){
                is_pause = true;
                pacman->retry();
                red->retry(red->spaw_x, red->spaw_y);
                pink->retry(pink->spaw_x, pink->spaw_y);
                blue->retry(blue->spaw_x, blue->spaw_y);
                orange->retry(orange->spaw_x, orange->spaw_y);
                lives--;
            }
            break;

            case SDLK_d:
            is_pause = false;
            d = 0;
            break;

            case SDLK_s:
            is_pause = false;
            d = 1;
            break;

            case SDLK_a:
            is_pause = false;
            d = 2;
            break;

            case SDLK_w:
            is_pause = false;
            d = 3;
            break;

            case SDLK_p:
            if(!is_pause){
                is_pause = true;
            }else{
                is_pause = false;
            }
            break;

            default:
            if(is_pause){
                is_pause = false;
            }
            break;
            }
    }

}
int change_frame = 0, speed = 5;

void Game::update()
{
    if(gamemap->win()){
        isRunning = false;
        std::cout << "You Won !!!" << std::endl;
    }
    if(lives == 0){
        isRunning = false;
    }
    change_frame++;
    if((fps / change_frame) == speed and !pacman->dead){
        change_frame = 0;
        pacman->sprite(d);
    }
    else if((fps / change_frame) == speed and pacman->dead){
        change_frame = 0;
        pacman->dying_animation();
    }
    int x = pacman->xpos, y = pacman->ypos;
    int x_rand = rand() % 1200 + 1, y_rand = rand() % 800 + 1;



    if(!pacman->dead){
        pacman->action(d);
        if(red->eaten){
            red->chase(safe_house_x, safe_house_y, red->facing, red->eaten);
            if(red->got_to_safehouse(safe_house_x, safe_house_y)){
                red->eaten = false;
                red->scare = false;
                red->revive(safe_house_x, safe_house_y);
            }
        }else{
            red->chase(x, y, red->facing, red->eaten);
        }

        if(pink->eaten){
            pink->chase(safe_house_x, safe_house_y, pink->facing, pink->eaten);
            if(pink->got_to_safehouse(safe_house_x, safe_house_y)){
                pink->eaten = false;
                pink->scare = false;
                pink->revive(safe_house_x, safe_house_y);
            }
        }else{
            pink->chase(red->xcoor, red->ycoor, pink->facing, pink->eaten);
        }

        if(blue->eaten){
            blue->chase(safe_house_x , safe_house_y, blue->facing, blue->eaten);
            if(blue->got_to_safehouse(safe_house_x, safe_house_y)){
                blue->eaten = false;
                blue->scare = false;
                blue->revive(safe_house_x, safe_house_y);
            }
        }else{
            blue->chase(x_rand , x_rand, blue->facing, blue->eaten);
        }

        if(orange->eaten){
            orange->chase(safe_house_x, safe_house_y, orange->facing, orange->eaten);
            if(orange->got_to_safehouse(safe_house_x, safe_house_y)){
                orange->eaten = false;
                orange->scare = false;
                orange->revive(safe_house_x, safe_house_y);
            }
        }else{
            orange->chase(x_rand , y_rand, orange->facing, orange->eaten);
        }
    }

    gamemap->update_map(x, y, score);
    if(red->meet(x, y, red->scare, red->eaten, score) || pink->meet(x, y, pink->scare, pink->eaten, score) || blue->meet(x, y, blue->scare, blue->eaten, score) || orange->meet(x, y, orange->scare, orange->eaten, score)){
        pacman->dead = true;
    }

}

int scare_timer = 0;

void Game::render()
{
	SDL_RenderClear(renderer);
	gamemap->loadmap();
    write("score: " + std::to_string(score) + "/" + std::to_string(high_score) , 1200, 650, {255, 255, 255, 255}, 30);
    //write("P to pause" , 0, 0, {255, 255, 255, 255}, 30);

	if(cherri != gamemap->cherri_left){
        scare_timer++;
        red->scare = true;
        pink->scare = true;
        blue->scare = true;
        orange->scare = true;
        if(scare_timer == 500){
            cherri = gamemap->cherri_left;
            scare_timer = 0;
            red->scare = false;
            pink->scare = false;
            blue->scare = false;
            orange->scare = false;
        }
	}
	red->render(cherri, red->scare, red->eaten);
	pink->render(cherri, pink->scare, pink->eaten);
	blue->render(cherri, blue->scare, blue->eaten);
	orange->render(cherri, orange->scare, orange->eaten);
	pacman->render();
	SDL_RenderPresent(renderer);

}

void Game::render_all(){


}

void Game::write(const std::string &msg, int x, int y, SDL_Color color, int size)
{
    TTF_Font *font = TTF_OpenFont("font.ttf", size);
    SDL_Surface *surf;
    SDL_Texture *tex;
    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, msg.c_str(), color);
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    SDL_FreeSurface(surf);
    SDL_RenderCopy(renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
    TTF_CloseFont(font);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

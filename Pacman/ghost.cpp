#include "ghost.h"

map* ghost_map;


ghost::ghost(int x, int y, int color){
    ghost_tex = Texture::NewTexture("image/ghost.png");
    ghost_scare = Texture::NewTexture("image/scare.png");
    ghost_eaten = Texture::NewTexture("image/eaten.png");
    srcR.x = 50*color;
    srcR.y = 0;
    srcR.h = 50;
    srcR.w = 50;

    desR.x = x;
    desR.y = y;
    desR.h = 40;
    desR.w = 40;

    ghost_map = new map;
    ghost_map->create_map();
}

ghost::~ghost(){}

void ghost::render(){
    if()
    SDL_RenderCopy(Game::renderer, ghost_tex, &srcR, &desR);
}

void ghost::chase(int x, int y, int direct){


}

void ghost::sprint(int direct){


}

bool ghost::meet(int x, int y){



}

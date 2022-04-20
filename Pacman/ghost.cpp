#include "ghost.h"
#include "map.h"
#include <cmath>
#include <algorithm>

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
    eaten = false;
    scare = false;
}

ghost::~ghost(){}

void ghost::render(int cherri){
    if(eaten){
        srcR.x = 0;
        SDL_RenderCopy(Game::renderer, ghost_eaten, &srcR, &desR);
    }
    else if(cherri != 4){
        scare = true;
        srcR.x = 0;
        SDL_RenderCopy(Game::renderer, ghost_scare, &srcR, &desR);
    }
    else{
        SDL_RenderCopy(Game::renderer, ghost_tex, &srcR, &desR);
    }
}

void ghost::chase(int x, int y, int direct, bool& d){
    int step;
    if(x == desR.x and y == desR.y and !scare){
        d = true;
    }

    if(x == desR.x and y == desR.y and scare){
        eaten = true;
    }

    int way1 = sqrt(pow(x - desR.x - 1, 2) + pow(y - desR.y, 2));
    int way2 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y - 1, 2));
    if(way1 < way2){
        step = (x - desR.x) / std::max(abs(x - desR.x), 1);

        desR.x += step*2;
    }else{
        step = (y - desR.y) / std::max(abs(y - desR.y), 1);
        desR.y += step*2;
    }

}



void ghost::sprite(int direct){


}



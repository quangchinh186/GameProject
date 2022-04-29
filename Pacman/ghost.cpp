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

int x_s[4] = {1, 0, -1, 0};
int y_s[4] = {0, 1, 0, -1};
int face = 0;
int ghost_v;

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

void ghost::chase(int x, int y, bool& player_dead){
    if(scare){
        ghost_v = -2;
    }else{
        ghost_v = 2;
    }
    if(abs(x - desR.x) < 20 and abs(y - desR.y) < 20 and !scare){
        player_dead = true;
    }
    if(abs(x - desR.x) < 20 and abs(y - desR.y) < 20 and scare){
        eaten = true;
    }

    xcoor = desR.x;
    ycoor = desR.y;

    double way_1, way_2;
    int sub_face;

    switch(face){
    case 0:
        way_1 = sqrt(pow(x - desR.x - ghost_v, 2) + pow(y - desR.y, 2));
        if(desR.y <= y){
            way_2 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y - ghost_v, 2));
            sub_face = 1;
        }else{
            way_2 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y + ghost_v, 2));
            sub_face = 3;
        }

        if(way_1 < way_2){
            face = 0;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }else{
            face = sub_face;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }
        break;

    case 1:
        way_1 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y - ghost_v, 2));
        if(desR.x <= x){
            way_2 = sqrt(pow(x - desR.x - ghost_v, 2) + pow(y - desR.y, 2));
            sub_face = 0;
        }else{
            way_2 = sqrt(pow(x - desR.x + ghost_v, 2) + pow(y - desR.y, 2));
            sub_face = 2;
        }

        if(way_1 < way_2){
            face = 1;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }else{
            face = sub_face;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }
        break;

    case 2:
        way_1 = sqrt(pow(x - desR.x + ghost_v, 2) + pow(y - desR.y, 2));
        if(desR.y <= y){
            way_2 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y - ghost_v, 2));
            sub_face = 1;
        }else{
            way_2 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y + ghost_v, 2));
            sub_face = 3;
        }

        if(way_1 < way_2){
            face = 2;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }else{
            face = sub_face;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }
        break;

    case 3:
        way_1 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y + ghost_v, 2));
        if(desR.x <= x){
            way_2 = sqrt(pow(x - desR.x - ghost_v, 2) + pow(y - desR.y, 2));
            sub_face = 0;
        }else{
            way_2 = sqrt(pow(x - desR.x + ghost_v, 2) + pow(y - desR.y, 2));
            sub_face = 2;
        }

        if(way_1 < way_2){
            face = 1;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }else{
            face = sub_face;
            if(ghost_map->moveable(desR.x + (x_s[face]*ghost_v), desR.y + (y_s[face]*ghost_v), ghost_v)){
                desR.x += (x_s[face]*ghost_v);
                desR.y += (y_s[face]*ghost_v);
            }
        }
        break;


    default:
        break;

    }


}



void ghost::sprite(int direct){


}



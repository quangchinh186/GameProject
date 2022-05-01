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
        ghost_v = -1;
    }else{
        ghost_v = 1;
    }
    if(abs(x - desR.x) < 20 and abs(y - desR.y) < 20 and !scare){
        player_dead = true;
    }
    if(abs(x - desR.x) < 20 and abs(y - desR.y) < 20 and scare){
        eaten = true;
    }
    xcoor = desR.x;
    ycoor = desR.y;
    double way_1, way_2, way_3;
    int temp;

    switch(face){
    case 0:
        if(ghost_map->moveable(desR.x+(x_s[0]*ghost_v), desR.y+(y_s[0]*ghost_v), ghost_v))
        {
            way_1 = sqrt(pow(x - desR.x - ghost_v, 2) + pow(y - desR.y, 2));
        }else{way_1 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[1]*ghost_v), desR.y+(y_s[1]*ghost_v), ghost_v))
        {
            way_2 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y - ghost_v, 2));
        }else{way_2 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[3]*ghost_v), desR.y+(y_s[3]*ghost_v), ghost_v))
        {
            way_3 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y + ghost_v, 2));
        }else{way_3 = 100000;}

        if(way_1 < way_2 && way_1 < way_3){
            face = 0;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_2 < way_1 && way_2 < way_3){
            face = 3;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_3 < way_1 && way_3 < way_2){
            face = 1;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }

        if(desR.x == xcoor){
            temp = desR.x % desR.w;
            temp >= (desR.w - temp) ? desR.x += (desR.w - temp) : desR.x -= temp;
        }
        if(desR.y == ycoor){
            temp = desR.y % desR.h;
            temp >= (desR.h - temp) ? desR.y += (desR.h - temp) : desR.y -= temp;
        }
        break;

    case 1:
        if(ghost_map->moveable(desR.x+(x_s[1]*ghost_v), desR.y+(y_s[1]*ghost_v), ghost_v))
        {
            way_1 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y - ghost_v, 2));
        }else{way_1 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[0]*ghost_v), desR.y+(y_s[0]*ghost_v), ghost_v))
        {
            way_2 = sqrt(pow(x - desR.x - ghost_v, 2) + pow(y - desR.y, 2));
        }else{way_2 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[2]*ghost_v), desR.y+(y_s[2]*ghost_v), ghost_v))
        {
            way_3 = sqrt(pow(x - desR.x + ghost_v, 2) + pow(y - desR.y, 2));
        }else{way_3 = 100000;}

        if(way_1 < way_2 && way_1 < way_3){
            face = 1;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_2 < way_1 && way_2 < way_3){
            face = 0;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_3 < way_1 && way_3 < way_2){
            face = 2;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        if(desR.x == xcoor){
            temp = desR.x % desR.w;
            temp >= (desR.w - temp) ? desR.x += (desR.w - temp) : desR.x -= temp;
        }
        if(desR.y == ycoor){
            temp = desR.y % desR.h;
            temp >= (desR.h - temp) ? desR.y += (desR.h - temp) : desR.y -= temp;
        }
        break;

    case 2:
    if(ghost_map->moveable(desR.x+(x_s[2]*ghost_v), desR.y+(y_s[2]*ghost_v), ghost_v))
        {
            way_1 = sqrt(pow(x - desR.x + ghost_v, 2) + pow(y - desR.y, 2));
        }else{way_1 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[1]*ghost_v), desR.y+(y_s[1]*ghost_v), ghost_v))
        {
            way_2 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y - ghost_v, 2));
        }else{way_2 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[3]*ghost_v), desR.y+(y_s[3]*ghost_v), ghost_v))
        {
            way_3 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y + ghost_v, 2));
        }else{way_3 = 100000;}

        if(way_1 <= way_2 && way_1 <= way_3){
            face = 2;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_2 <= way_1 && way_2 <= way_3){
            face = 3;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_3 < way_1 && way_3 < way_2){
            face = 1;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        if(desR.x == xcoor){
            temp = desR.x % desR.w;
            temp >= (desR.w - temp) ? desR.x += (desR.w - temp) : desR.x -= temp;
        }
        if(desR.y == ycoor){
            temp = desR.y % desR.h;
            temp >= (desR.h - temp) ? desR.y += (desR.h - temp) : desR.y -= temp;
        }
        break;

    case 3:
    if(ghost_map->moveable(desR.x+(x_s[3]*ghost_v), desR.y+(y_s[3]*ghost_v), ghost_v))
        {
            way_1 = sqrt(pow(x - desR.x, 2) + pow(y - desR.y + ghost_v, 2));
        }else{way_1 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[0]*ghost_v), desR.y+(y_s[0]*ghost_v), ghost_v))
        {
            way_2 = sqrt(pow(x - desR.x - ghost_v, 2) + pow(y - desR.y, 2));
        }else{way_2 = 100000;}
        if(ghost_map->moveable(desR.x+(x_s[2]*ghost_v), desR.y+(y_s[2]*ghost_v), ghost_v))
        {
            way_3 = sqrt(pow(x - desR.x + ghost_v, 2) + pow(y - desR.y, 2));
        }else{way_3 = 100000;}

        if(way_1 <= way_2 && way_1 <= way_3){
            face = 3;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_2 < way_1 && way_2 < way_3){
            face = 0;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        else if(way_3 < way_1 && way_3 < way_2){
            face = 2;
            desR.x += (x_s[face]*ghost_v);
            desR.y += (y_s[face]*ghost_v);
        }
        if(desR.x == xcoor){
            temp = desR.x % desR.w;
            temp >= (desR.w - temp) ? desR.x += (desR.w - temp) : desR.x -= temp;
        }
        if(desR.y == ycoor){
            temp = desR.y % desR.h;
            temp >= (desR.h - temp) ? desR.y += (desR.h - temp) : desR.y -= temp;
        }
        break;

    default:
        break;

    }
}



void ghost::sprite(int direct){


}



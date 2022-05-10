#include "ghost.h"
#include "map.h"
#include <cmath>
#include <algorithm>

map* ghost_map;


ghost::ghost(int x, int y, int _color){
    ghost_tex = Texture::NewTexture("image/ghost.png");
    ghost_scare = Texture::NewTexture("image/scare.png");
    ghost_eaten = Texture::NewTexture("image/eaten.png");
    srcR.x = 50*_color;
    srcR.y = 0;
    srcR.h = 50;
    srcR.w = 50;

    source = srcR.x;

    desR.x = x;
    desR.y = y;
    desR.h = 40;
    desR.w = 40;

    ghost_map = new map;
    ghost_map->create_map();
    eaten = false;
    scare = false;
    //color = _color;
}

ghost::~ghost(){}

int x_s[4] = {1, 0, -1, 0};
int y_s[4] = {0, 1, 0, -1};
int face[4] = {0, 1, 2, 3};
int t = 0, cherri_on_map = 4, time = 0;
int ghost_v = 4;
double max_distance = 10000;


void ghost::render(int cherri){
    if(eaten){
        srcR.x = 0;
        SDL_RenderCopy(Game::renderer, ghost_eaten, &srcR, &desR);
    }
    else if(cherri != cherri_on_map ){
        time++;
        scare = true;
        srcR.x = 0;
        SDL_RenderCopy(Game::renderer, ghost_scare, &srcR, &desR);
        if(time == 1500){
            cherri_on_map = cherri;
            scare = false;
            time = 0;
        }
    }
    else{
        srcR.x = source;
        SDL_RenderCopy(Game::renderer, ghost_tex, &srcR, &desR);
    }


}

void ghost::chase(int x, int y, int color){
    if(scare){
        ghost_v = 2;
    }else{
        ghost_v = 4;
    }
    xcoor = desR.x;
    ycoor = desR.y;
    double way_1, way_2, way_3;
    int temp, curr_face = face[color];
    double x_1 = static_cast<float>(xcoor), x_2 = static_cast<float>(x);
    double y_1 = static_cast<float>(ycoor), y_2 = static_cast<float>(y);

if(ghost_map->turnable(xcoor, ycoor)){
    switch(face[color]){
    case 0:
        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face[color] = 1;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face[color] = 3;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 1  : temp = 3, way_2 = way_3;
        way_1 < way_2 ? face[color] = 0 : face[color] = temp;

        break;

    case 1:
        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face[color] = 2;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face[color] = 0;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 2  : temp = 0, way_2 = way_3;
        way_1 < way_2 ? face[color] = 1 : face[color] = temp;

        break;

    case 2:
        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face[color] = 3;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face[color] = 1;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 3  : temp = 1, way_2 = way_3;
        way_1 < way_2 ? face[color] = 2 : face[color] = temp;

        break;

    case 3:
        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face[color] = 0;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face[color] = 2;
        if(ghost_map->moveable(xcoor + (x_s[face[color]]*desR.w), ycoor + (y_s[face[color]]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face[color]]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face[color]]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 0  : temp = 2, way_2 = way_3;
        way_1 < way_2 ? face[color] = 3 : face[color] = temp;

        break;
    }
    t = face[color];
}
else{
    face[color] = t;
}
    desR.x += x_s[face[color]]*ghost_v;
    desR.y += y_s[face[color]]*ghost_v;

    //std::cout << face[0] << face[1] << face[2] << face[3] << std::endl;
    std::cout << color << std::endl;
}

bool ghost::kill(int x, int y){
    if(abs(desR.x - x) <= desR.w/2 && abs(desR.y - y) <= desR.h/2){
        return true;
    }
    return false;
}


void ghost::sprite(int direct){


}



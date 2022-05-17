#include "ghost.h"
#include "map.h"
#include <cmath>
#include <algorithm>

map* ghost_map;

int safe_house_x, safe_house_y;

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

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 30; j ++){
            if(ghost_map->m[i][j] == 4){
                safe_house_x = desR.w * (j+1);
                safe_house_y = desR.h * (i+1);
            }
        }
    }

}

ghost::~ghost(){}

int x_s[4] = {1, 0, -1, 0};
int y_s[4] = {0, 1, 0, -1};
int cherri_on_map = 4, time = 0;

double max_distance = 10000;


void ghost::render(int cherri, bool& sc, bool& ate){
    if(ate){
        srcR.x = 0;
        SDL_RenderCopy(Game::renderer, ghost_eaten, &srcR, &desR);
    }
    else if(cherri != cherri_on_map ){
        time++;
        sc = true;
        //ghost_v = -2;
        srcR.x = 0;
        SDL_RenderCopy(Game::renderer, ghost_scare, &srcR, &desR);
        if(time == 1000){
            cherri_on_map = cherri;
            sc = false;
            //ghost_v = 2;
            time = 0;
        }
    }
    else{

        srcR.x = source;
        SDL_RenderCopy(Game::renderer, ghost_tex, &srcR, &desR);
    }


}

void ghost::chase(int x, int y, int& face, bool ate){
    xcoor = desR.x;
    ycoor = desR.y;
    if(ate){
        x = safe_house_x;
        y = safe_house_y;
        if(desR.x == x && desR.y == y){
            ate = false;
        }
    }else{

    }


    double way_1, way_2, way_3;
    int temp;

    double x_1 = static_cast<float>(xcoor), x_2 = static_cast<float>(x);
    double y_1 = static_cast<float>(ycoor), y_2 = static_cast<float>(y);

if(ghost_map->turnable(xcoor, ycoor) ){
    switch(face){
    case 0:

        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face = 1;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face = 3;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 1  : temp = 3, way_2 = way_3;
        way_1 < way_2 ? face = 0 : face = temp;

        break;

    case 1:

        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face = 2;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face = 0;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 2  : temp = 0, way_2 = way_3;
        way_1 < way_2 ? face = 1 : face = temp;

        break;

    case 2:

        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face = 3;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face = 1;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 3  : temp = 1, way_2 = way_3;
        way_1 < way_2 ? face = 2 : face = temp;

        break;

    case 3:

        //di thang
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_1 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_1 = sqrt(way_1);
        }else{way_1 = max_distance;}
        //re phai
        face = 0;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_2 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_2 = sqrt(way_2);
        }else{way_2 = max_distance;}
        //re trai
        face = 2;
        if(ghost_map->moveable(xcoor + (x_s[face]*desR.w), ycoor + (y_s[face]*desR.h))){
            way_3 = pow(x_1 - x_2 + (x_s[face]*desR.w), 2) + pow(y_1 - y_2 + (y_s[face]*desR.h), 2);
            way_3 = sqrt(way_3);
        }else{way_3 = max_distance;}

        way_2 < way_3 ? temp = 0  : temp = 2, way_2 = way_3;
        way_1 < way_2 ? face = 3 : face = temp;

        break;
    }
    temp_face = face;
}
else{
    face = temp_face;
}

    desR.x += x_s[face]*ghost_v;
    desR.y += y_s[face]*ghost_v;


}

void ghost::go_to_safehouse(){

}

bool ghost::meet(int x, int y, bool& sc, bool& ate){
    if(ate){
        x = safe_house_x;
        y = safe_house_y;
    }

    if(abs(desR.x - x) <= desR.w/2 && abs(desR.y - y) <= desR.h/2 && !sc){
        return true;
    }else if(abs(desR.x - x) <= desR.w/2 && abs(desR.y - y) <= desR.h/2 && sc){
        ate = true;
        return false;
    }
    else if(abs(desR.x - x) <= desR.w/2 && abs(desR.y - y) <= desR.h/2 && ate){
        ate = false;
        return false;
    }

    return false;
}






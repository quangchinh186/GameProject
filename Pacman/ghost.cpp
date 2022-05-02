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
int ghost_v = 3;

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
        x = 0;
        y = 0;
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
        face = 0;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_1 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            go_straight = true;
        }else{go_straight = false;}

        face = 1;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_2 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_right = true;
        }else{t_right = false;}

        face = 3;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_3 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_left = true;
        }else{t_left = false;}

        if(desR.x % desR.w != 0 || desR.y % desR.h != 0){
            t_left = false;
            t_right = false;
        }

        if(go_straight == false){
            if(t_left and t_right){
                way_2 < way_3 ? face = 1 : face = 3;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                face = 1;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else{
                face = 3;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }

        }else if(go_straight){
            if(t_left and t_right){
                way_2 < way_3 ? temp = 1 : temp = 3;
                way_1 < std::min(way_2, way_3) ? face = 0 : face = temp;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                way_1 < way_2 ? face = 0 : face = 1;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_right == false){
                way_1 < way_3 ? face = 0 : face = 3;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else{
                face = 0;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
        }


        break;

    case 1:
        face = 1;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_1 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            go_straight = true;
        }else{go_straight = false;}

        face = 2;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_2 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_right = true;
        }else{t_right = false;}

        face = 0;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_3 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_left = true;
        }else{t_left = false;}

        if(desR.x % desR.w != 0 || desR.y % desR.h != 0){
            t_left = false;
            t_right = false;
        }

        if(go_straight == false){
            if(t_left and t_right){
                way_2 < way_3 ? face = 2 : face = 0;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                face = 2;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else{
                face = 0;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }

        }else if(go_straight){
            if(t_left and t_right){
                way_2 < way_3 ? temp = 2 : temp = 0;
                way_1 < std::min(way_2, way_3) ? face = 1 : face = temp;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                way_1 < way_2 ? face = 1 : face = 2;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_right == false){
                way_1 < way_3 ? face = 1 : face = 0;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }

            else{
                face = 1;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
        }



        break;

    case 2:
        face = 2;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_1 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            go_straight = true;
        }else{go_straight = false;}

        face = 3;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_2 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_right = true;
        }else{t_right = false;}

        face = 1;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_3 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_left = true;
        }else{t_left = false;}

        if(desR.x % desR.w != 0 || desR.y % desR.h != 0){
            t_left = false;
            t_right = false;
        }

        if(go_straight == false){
            if(t_left and t_right){
                way_2 < way_3 ? face = 3 : face = 1;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                face = 3;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else{
                face = 1;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }

        }else if(go_straight){
            if(t_left and t_right){
                way_2 < way_3 ? temp = 3 : temp = 1;
                way_1 < std::min(way_2, way_3) ? face = 2 : face = temp;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                way_1 < way_2 ? face = 2 : face = 3;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_right == false){
                way_1 < way_3 ? face = 2 : face = 1;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else{
                face = 0;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
        }



        break;

    case 3:
        face = 3;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_1 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            go_straight = true;
        }else{go_straight = false;}

        face = 0;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_2 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_right = true;
        }else{t_right = false;}

        face = 1;
        if(ghost_map->moveable(desR.x+(x_s[face]*ghost_v), desR.y+(y_s[face]*ghost_v), ghost_v)){
            way_3 = sqrt(pow(x-(desR.x+(x_s[face]*ghost_v)), 2) + pow(y - (desR.y+(y_s[face]*ghost_v)), 2));
            t_left = true;
        }else{t_left = false;}

        if(desR.x % desR.w != 0 || desR.y % desR.h != 0){
            t_left = false;
            t_right = false;
        }

        if(go_straight == false){
            if(t_left and t_right){
                way_2 < way_3 ? face = 0 : face = 2;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                face = 0;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else{
                face = 2;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }

        }else if(go_straight){
            if(t_left and t_right){
                way_2 < way_3 ? temp = 0 : temp = 2;
                way_1 < std::min(way_2, way_3) ? face = 3 : face = temp;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_left == false){
                way_1 < way_2 ? face = 3 : face = 0;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
            else if(t_right == false){
                way_1 < way_3 ? face = 3 : face = 2;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }

            else{
                face = 3;
                desR.x += x_s[face]*ghost_v;
                desR.y += y_s[face]*ghost_v;
            }
        }


        break;

    }
}



void ghost::sprite(int direct){


}



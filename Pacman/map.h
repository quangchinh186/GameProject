#ifndef map_h
#define map_h
#include "game.h"
#include "load_image.h"
#include <fstream>

class map{
public:
    map();
    ~map();
    int m[20][30];
    void loadmap();
    void create_map();
    void update_map(int x, int y);
    bool moveable(int x, int y);
    bool turnable(int x, int y);
    int cherri_left = 4;
private:

    SDL_Texture* wall;
    SDL_Texture* blank;
    SDL_Texture* item;
    SDL_Texture* cherri;
    SDL_Texture* gate;
    SDL_Rect destR, sorcR;
};


#endif // map_h

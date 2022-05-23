#ifndef player_h
#define player_h

#include "game.h"

class player{
public:
    player(const char* filename, int x, int y, int f);
    ~player();
    void action(int direct);
    void render();
    void retry();
    void sprite(int direct);
    void dying_animation();
    int xpos, ypos, frame;
    int spawn_x, spawn_y;
    bool dead = false;
    bool is_power_up = false;

private:
    SDL_Texture* dyingPlayer;
    SDL_Texture* playerTex;
    SDL_Rect sR, dR;

};


#endif // player_h

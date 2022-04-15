#ifndef player_h
#define player_h

#include "game.h"

class player{
public:
    player(const char* filename, int x, int y, int f);
    ~player();
    void action(int direct);
    void render();
    void sprite(int direct);
    int xpos, ypos, frame;
private:

    SDL_Texture* playerTex;
    SDL_Rect sR, dR;

};


#endif // player_h

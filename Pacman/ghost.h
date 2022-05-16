#ifndef ghost_h
#define ghost_h

#include "game.h"
#include "load_image.h"

class ghost{
public:
    ghost(int x, int y, int _color);
    ~ghost();
    void render(int cherri);
    void chase(int x, int y, int& face);

    int xcoor, ycoor, source, facing = 0;
    int temp_face = 0;
    int ghost_v = 4;
    bool meet(int x, int y);
    bool get_eaten(int x, int y);


private:
    SDL_Texture* ghost_tex;
    SDL_Texture* ghost_scare;
    SDL_Texture* ghost_eaten;
    SDL_Rect desR, srcR;
    bool eaten;
    bool scare;
};


#endif // ghost_h

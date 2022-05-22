#ifndef ghost_h
#define ghost_h

#include "game.h"
#include "load_image.h"

class ghost{
public:
    ghost(int x, int y, int _color);
    ~ghost();
    void render(int cherri, bool& sc, bool& ate);
    void chase(int x, int y, int& face, bool eat);
    void revive(int x, int y);
    void retry(int x, int y);

    int spaw_x, spaw_y;
    int xcoor, ycoor, source, facing = 0;
    int temp_face = 0;
    int ghost_v = 4;
    bool meet(int x, int y, bool& sc, bool& ate, int& score);
    bool got_to_safehouse(int x, int y);
    bool eaten;
    bool scare;

private:
    SDL_Texture* ghost_tex;
    SDL_Texture* ghost_scare;
    SDL_Texture* ghost_eaten;
    SDL_Rect desR, srcR;

};


#endif // ghost_h

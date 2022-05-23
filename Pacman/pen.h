#ifndef pen_h
#define pen_h
#include "game.h"

class pen{

public:
    pen(int size);
    ~pen();
    void write(const std::string &msg, int x, int y, SDL_Color color);

private:
    TTF_Font *font;

};

#endif // pen_h


#ifndef pen_h
#define pen_h
#include "game.h"

class pen{

public:
    pen();
    ~pen();
    void write(const std::string &msg, int x, int y, SDL_Color color, int size);

private:
    TTF_Font *font;

};

#endif // pen_h


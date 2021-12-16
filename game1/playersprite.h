#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H
#include "../age/prefab.h"
#include <tuple>
#include <vector>
#include <ncurses.h>


class PlayerSprite : public Prefab{
    public:
        PlayerSprite(){
            colors = {std::make_pair<int, int>(COLOR_GREEN, COLOR_BLACK)};
            bitmap = {std::make_tuple(0,0, 'x', 0)};
        }
};

#endif
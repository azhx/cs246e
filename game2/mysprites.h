#ifndef MYSPRITES_H
#define MYSPRITES_H

#include "../age/prefab.h"
#include <tuple>
#include <vector>
#include <ncurses.h>


class BatSprite : public Prefab{
    public:
        BatSprite(){
            colors = {std::make_pair<int, int>(COLOR_MAGENTA, COLOR_BLACK), 
                      std::make_pair<int, int>(COLOR_RED, COLOR_BLACK)};
            bitmap = {std::make_tuple(0, 0, 'o', 0),
                    std::make_tuple(-1, 0, '-', 1),
                    std::make_tuple(-2, 0, '_', 0),
                    std::make_tuple(-3, 0, '\\', 0),
                    std::make_tuple(-4, 0, '/', 0),
                    std::make_tuple(1, 0, '-', 1),
                    std::make_tuple(2, 0, '_', 0),
                    std::make_tuple(3, 0, '/', 0),
                    std::make_tuple(4, 0, '\\', 0),};
        }
};

class GoblinSprite : public Prefab{
    std::vector<std::vector<std::tuple<int, int, char, int>>> forms {{std::make_tuple(0,0, 'O', 0), 
                      std::make_tuple(0,-1, 'o', 0), 
                      std::make_tuple(-1,0, '"', 0), 
                     },{std::make_tuple(0,0, 'O', 0), 
                      std::make_tuple(0,-1, 'o', 0), 
                      std::make_tuple(1,0, '"', 0), 
                     }};
    public:
        GoblinSprite(bool facing_left){
            colors = {std::make_pair<int, int>(COLOR_GREEN, COLOR_BLACK)};
            bitmap = forms[!facing_left];
        }
};

class BulletSprite : public Prefab{
    public:
        BulletSprite(){
            colors = {std::make_pair<int, int>(COLOR_YELLOW, COLOR_BLACK)};
            bitmap = {std::make_tuple(0, 0, '-', 0), std::make_tuple(-1, 0, '-', 0), std::make_tuple(1, 0, '-', 0)};
        }
};

#endif
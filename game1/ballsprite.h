#ifndef BALLSPRITE_H
#define BALLSPRITE_H
#include "../age/prefab.h"
#include <tuple>
#include <vector>
#include <ncurses.h>


class BallSprite : public Prefab{
    std::vector<std::pair<int, int>> ballcolors {
        std::make_pair<int, int>(COLOR_BLACK, COLOR_RED),
        std::make_pair<int, int>(COLOR_BLACK, COLOR_BLUE), 
        std::make_pair<int, int>(COLOR_BLACK, COLOR_CYAN),
        std::make_pair<int, int>(COLOR_BLACK, COLOR_MAGENTA)};
    public:
        BallSprite(int radius, int height){
            colors = {ballcolors[height]};
            bitmap = {};
            for (int i = -radius; i < radius; ++i){
                for (int j = -radius; j < radius; ++j){
                    bitmap.push_back(std::make_tuple(i, j, ' ', 0));
                }
            }
        }
};

#endif
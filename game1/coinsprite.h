#ifndef COINSPRITE_H
#define COINSPRITE_H
#include <ncurses.h>

#include <tuple>
#include <vector>

#include "../age/prefab.h"

class CoinSprite : public Prefab {
 public:
  CoinSprite() {
    colors = {std::make_pair<int, int>(COLOR_YELLOW, COLOR_BLACK)};
    bitmap = {std::make_tuple(0, 0, 'c', 0)};
  }
};

#endif
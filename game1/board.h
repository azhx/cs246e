#ifndef BOARD_H
#define BOARD_H
#include "../age/environment.h"
#include <vector>

class Board : public Environment {
 public:
  template<typename...Args>
  Board(Args&&...args): Environment{std::forward<Args>(args)...} {}
  void update(const std::vector<int>& input) override {}
};

#endif
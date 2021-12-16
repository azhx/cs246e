#ifndef PLAYER_H
#define PLAYER_H
#include <ncurses.h>

#include <algorithm>
#include <memory>
#include "../age/termview.h"
#include "../age/state.h"

#include "../age/gameobject.h"

class Ball;
class PlayerCollider;
class Coin;
class Player : public GameObject<Coin, Ball> {
  // pos is x, y
 public:
  Player(State& state, int id, int height, std::pair<int, int> pos,
         std::shared_ptr<Prefab> prefab);
  void onCollision(Ball& other) override;
  void onCollision(Coin& other) override;

  void Collide(Ball& other) override;
  void Collide(Coin& other) override;
  void update(const std::vector<int>& input) override {
    if (input.size() == 0) return;
    int sprint = 0;
    for (size_t i = 0; i < input.size(); ++i) {
      if (input[i] == 'x' && this->state.globals["xcooldown"] == 0) {
        sprint = std::max(sprint, 6);
      } else if (input[i] == 'z' && this->state.globals["zcooldown"] == 0) {
        sprint = std::max(sprint, 12);
      }
    }
    bool moved = false;
    for (int i = input.size() - 1; i >= 0; --i) {
      if (input[i] == 'w' || input[i] == KEY_UP) {
        pos.second = std::max(pos.second - 1 - sprint, 1);
        moved = true;
        break;
      } else if (input[i] == 'a' || input[i] == KEY_LEFT) {
        pos.first = std::max(pos.first - 1 - sprint, 1);
        moved = true;
        break;
      } else if (input[i] == 's' || input[i] == KEY_DOWN) {
        pos.second = std::min(pos.second + 1 + sprint, GAMEHEIGHT - 2);
        moved = true;
        break;
      } else if (input[i] == 'd' || input[i] == KEY_RIGHT) {
        pos.first = std::min(pos.first + 1 + sprint, GAMEWIDTH - 2);
        moved = true;
        break;
      }
    }
    if (moved) {
      if (sprint == 12)
        this->state.globals["zcooldown"] = 10;
      else if (sprint == 6)
        this->state.globals["xcooldown"] = 5;
    }
  }
};

#endif
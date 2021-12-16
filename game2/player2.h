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
class Enemy;
class Player : public GameObject<Enemy> {
  // pos is x, y
  void spawnBullet();
 public:
  std::pair<int, int> prevpos {0,0};
 // vel and acc are both x, y
  std::pair<int, int> vel {1, 0};
  const std::pair<int, int> acc {0, 1};
  int jumps = 0;

  Player(State& state);

  void Collide(Enemy& other);

  void onCollision(Enemy& other) override;


  void update(const std::vector<int>& input) override {
    vel.second += acc.second;
    if (pos.second == GAMEHEIGHT-2){
      vel.second = 0;
      jumps = 0;
    }
    bool makeBullet = false;
    // change the velocity
    for (int i = input.size() - 1; i >= 0; --i) {
      if (jumps < 2 && (input[i] == 'w' || input[i] == KEY_UP)) {
        vel.second = -4; //neg is positive on the screen
        ++jumps;
        break;
      } else if (input[i] == 'a' || input[i] == KEY_LEFT) {
        vel.first = -std::abs(vel.first);
        break;
      } else if (input[i] == 'd' || input[i] == KEY_RIGHT) {
        vel.first = std::abs(vel.first);
        break;
      }
      if (input[i] == ' '){
        makeBullet = true;
      }
      /*else if (input[i] == 's' || input[i] == KEY_DOWN) {
        vel.first = std::abs(vel.first);
        break;
      } */
    }
    if (makeBullet) spawnBullet();
    // 1 velocity equals to 1 block/tick
    prevpos.first = pos.first;
    prevpos.second = pos.second;
    pos.first = std::min(std::max(pos.first + vel.first, 1), GAMEWIDTH-2);
    pos.second = std::min(std::max(pos.second + vel.second, 1), GAMEHEIGHT-2);
  }
};

#endif
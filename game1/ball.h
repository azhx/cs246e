#ifndef BALL_H
#define BALL_H
#include <utility>
#include <memory>
#include "../age/gameobject.h"

#include "mycolliders.h"

class Border;
class Coin;
class Ball;
class Ball : public GameObject<Coin, Border, Ball> {
 public:
  int radius;
  // x, y velocity
  std::pair<int, int> vel;
  /*template<typename...Args>
  Ball(int radius, std::pair<int, int> vel, std::forward<Args>(args)...)
  : GameObject<Border, Ball>(std::forward<Args>(args)...), radius{radius},
  vel{vel} {}
*/
  Ball(State& state, int id, int height, std::pair<int, int> pos,
       std::shared_ptr<Prefab> prefab, int radius, std::pair<int, int> vel)
      : GameObject<Coin, Border, Ball>(state, id, height, pos, prefab,
                                 std::make_shared<BallCollider>(*this)),
        radius{radius},
        vel{vel} {}

  void update(const std::vector<int>& input) override {
    pos = std::make_pair(pos.first + vel.first, pos.second + vel.second);
  }
  
  void Collide(Border& other) override;
  
  void Collide(Ball& ball) override;

  void Collide(Coin& coin) override {};

  void onCollision(Border& border) override;

  void onCollision(Ball& ball) override {
    // do nothing;
  }

  void onCollision(Coin& coin) override {};
};

#endif

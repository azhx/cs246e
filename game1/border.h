#ifndef BORDER_H
#define BORDER_H

#include "../age/gameobject.h"
#include "../age/termview.h"
#include "mycolliders.h"

class State;
class Ball;

class Border : public GameObject<Ball> {
  // This class only exists to store the BorderCollider
 public:
  int minx = 1;
  int miny = 1;
  int maxx = GAMEWIDTH - 1;
  int maxy = GAMEHEIGHT - 1;

  Border(State& state, int id, int height, std::pair<int, int> pos,
         std::shared_ptr<Prefab> prefab)
      : GameObject<Ball>(state, id, height, pos, prefab,
                         std::make_shared<BorderCollider>(*this)) {}

  void Collide(Ball& other) override;

  void onCollision(Ball& other) override {}
  void update(const std::vector<int>& input) override {}
};

#endif
#ifndef BULLET_H
#define BULLET_H
#include <utility>
#include <memory>
#include "../age/gameobject.h"

#include "mycolliders2.h"
#include "mysprites.h"
#include "../age/termview.h"

class Enemy;
class Bullet: public GameObject<Enemy, Bullet> {
 public:
  int xvel = 3;
  Bullet(State& state, int id, int height, std::pair<int, int> pos, bool facing_left)
      : GameObject<Enemy, Bullet>(state, id, height, pos, std::make_shared<BulletSprite>(),
                                 std::make_shared<BulletCollider>(*this)) {
                                   if (facing_left) xvel = -xvel;
                                 }
  void update(const std::vector<int>& input) override {
    if (pos.first > GAMEWIDTH+20 || pos.first < -20){
      state.destroyObjects(std::vector<int> {id});
      return;
    }
    pos.first += xvel;
  }

  void Collide(Enemy& other) override;
  void onCollision(Enemy& other) override;
  void Collide(Bullet& other) override {};
  void onCollision(Bullet& other) override{};
};

#endif

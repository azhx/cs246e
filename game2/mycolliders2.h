#ifndef MYCOLLIDERS_H
#define MYCOLLIDERS_H

#include <utility>

#include "../age/collider.h"
class Player;
class Enemy;
class Bullet;
class EnemyCollider;
class BulletCollider : public Collider<EnemyCollider, BulletCollider>{
  public:
    Bullet& bullet;
    BulletCollider(Bullet& bullet): bullet{bullet}{}
    bool checkCollision(EnemyCollider& otherCollider) const override;
    bool checkCollision(BulletCollider& otherCollider) const override {return false;};
};

class EnemyCollider : public Collider<EnemyCollider, BulletCollider>{
  public:
    Enemy& enemy;
    EnemyCollider(Enemy& enemy): enemy{enemy}{}
    bool checkCollision(EnemyCollider& otherCollider) const override {return false;};
    bool checkCollision(BulletCollider& otherCollider) const override;
};

// Player Collides with Ball (one way)
class PlayerCollider : public Collider<EnemyCollider> {
 public:
  Player& player;
  PlayerCollider(Player& player): player{player}{}
  // this checkCollision should check pixel intersection for arbitrary enemies.
  bool checkCollision(EnemyCollider& otherCollider) const override;
};

#endif
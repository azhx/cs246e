#ifndef MYCOLLIDERS_H
#define MYCOLLIDERS_H

#include <utility>

#include "../age/collider.h"
class Ball;
class Player;
class State;
class BorderCollider;
class Border;
class Coin;
class CoinCollider;

class BallCollider : public Collider<BorderCollider, BallCollider> {
 public:
  Ball& ball;
  BallCollider(Ball& ball):ball{ball}{}

  bool checkCollision(BorderCollider& border)const override;

  bool checkCollision(BallCollider& otherball) const override{
    // NO BALL COLLISIONS!
    return false;
  }
};
// Player Collides with Ball (one way)
class PlayerCollider : public Collider<BallCollider, CoinCollider> {
 public:
  Player& player;
  PlayerCollider(Player& player): player{player}{}
  bool checkCollision(BallCollider& otherCollider) const override;
  bool checkCollision(CoinCollider& otherCollider) const override;
};

class CoinCollider : public Collider<PlayerCollider>{
  public:
    Coin& coin;
    CoinCollider(Coin& coin): coin{coin}{}
    bool checkCollision(PlayerCollider& otherCollider) const override;
};

class BorderCollider : public Collider<BallCollider> {
 public:
  Border& border;
  BorderCollider(Border& border);
  bool checkCollision(BallCollider& otherCollider) const override;
};


#endif
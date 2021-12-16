#include "player.h"
#include "ball.h"
#include "coin.h"
#include "mycolliders.h"
void Player::Collide(Ball& other){
    if (std::dynamic_pointer_cast<PlayerCollider>(this->collider)->checkCollision(
        dynamic_cast<BallCollider&>(*other.collider))) {
      onCollision(other);
    }
}

void Player::Collide(Coin& other){
    if (std::dynamic_pointer_cast<PlayerCollider>(this->collider)->checkCollision(
        dynamic_cast<CoinCollider&>(*other.collider))) {
      onCollision(other);
    }
}

void Player::onCollision(Ball& other) {
    this->state.stop();
}

void Player::onCollision(Coin& other) {
    state.globals["score"] += other.health;
    other.health = 100;
    other.pos.first = (rand() % (GAMEWIDTH-2))+1;
    other.pos.second = (rand() % (GAMEHEIGHT-2))+1;
    other.prefab->colors[0] = other.coincolors[0];
}

Player::Player(State& state, int id, int height, std::pair<int, int> pos,
         std::shared_ptr<Prefab> prefab)
      : GameObject<Coin, Ball>(state, id, height, pos, prefab,
                         std::make_shared<PlayerCollider>(*this)) {}
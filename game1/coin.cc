#include "ball.h"
#include "player.h"
#include "coin.h"

void Coin::Collide(Player& other) {
    if (std::dynamic_pointer_cast<CoinCollider>(this->collider)->checkCollision(
        dynamic_cast<PlayerCollider&>(*other.collider))) {
      onCollision(other);
      other.onCollision(*this);
    }
}

void Coin::Collide(Ball& other) {}

void Coin::onCollision(Player& other){
    state.globals["score"] += health;
    health = 100;
    pos.first = (rand() % (GAMEWIDTH-2))+1;
    pos.second = (rand() % (GAMEHEIGHT-2))+1;
    prefab->colors[0] = coincolors[0];
}
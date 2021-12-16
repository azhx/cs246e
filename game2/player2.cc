#include "player2.h"

#include "mycolliders2.h"
#include "playersprite2.h"
#include "enemies.h"
#include "bullet.h"
#include "game2.h"

void Player::spawnBullet(){
    std::vector<std::shared_ptr<GameObject<>>> spawns = {};
    if (vel.first > 0){
        // spawn bullet going right
        spawns.push_back(std::make_shared<Bullet>(state, state.getFreeId(), 0, std::make_pair<int, int>(pos.first + 2, pos.second + 0), false));
    } else {
        // spawn bullet facing right
        spawns.push_back(std::make_shared<Bullet>(state, state.getFreeId(), 0, std::make_pair<int, int>(pos.first - 2, pos.second + 0), true));
    }
    state.spawnObjects(spawns);
}

void Player::Collide(Enemy& other) {
    if (std::dynamic_pointer_cast<PlayerCollider>(this->collider)->checkCollision(
        dynamic_cast<EnemyCollider&>(*other.collider))) {
      onCollision(other);
    }
};

void Player::onCollision(Enemy& other) {
    state.stop();
};

Player::Player(State& state)
    : GameObject<Enemy>(state, 0, 0, std::make_pair<int, int>(40, 22),
                   std::make_shared<PlayerSprite>(),
                   std::make_shared<PlayerCollider>(*this)) {}
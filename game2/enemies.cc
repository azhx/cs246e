#include "enemies.h"
#include "bullet.h"
void Enemy::Collide(Bullet& other) {
    if (std::dynamic_pointer_cast<EnemyCollider>(this->collider)->checkCollision(
        dynamic_cast<BulletCollider&>(*other.collider))) {
      onCollision(other);
      other.onCollision(*this);
    }
}
void Enemy::onCollision(Bullet& other) {
    std::vector<int> destroy = {id, other.id};
    state.destroyObjects(destroy);
}
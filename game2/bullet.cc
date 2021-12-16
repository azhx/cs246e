#include "bullet.h"
#include "enemies.h"

void Bullet::Collide(Enemy& other) {
    if (std::dynamic_pointer_cast<BulletCollider>(this->collider)->checkCollision(
        dynamic_cast<EnemyCollider&>(*other.collider))) {
      onCollision(other);
      other.onCollision(*this);
    }
}

void Bullet::onCollision(Enemy& other) {
    std::vector<int> destroy = {id, other.id};
    state.destroyObjects(destroy);
}

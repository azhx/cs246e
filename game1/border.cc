#include "border.h"
#include "ball.h"

void Border::Collide(Ball& other) {
  if (std::dynamic_pointer_cast<BorderCollider>(this->collider)
          ->checkCollision(dynamic_cast<BallCollider&>(*other.collider))) {
    onCollision(other);
    other.onCollision(*this);
  }
}
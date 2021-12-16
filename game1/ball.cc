#include "ball.h"
#include "border.h"

void Ball::Collide(Border& other) {
    if (std::dynamic_pointer_cast<BallCollider>(this->collider)->checkCollision(
        dynamic_cast<BorderCollider&>(*other.collider))) {
      onCollision(other);
      other.onCollision(*this);
    }
}

void Ball::Collide(Ball& other) {}

void Ball::onCollision(Border& border){
    int trueminx = border.minx + radius;
    int trueminy = border.miny + radius;
    int truemaxx = border.maxx - radius;
    int truemaxy = border.maxy - radius;
    if (pos.first < trueminx) {
      pos.first = trueminx + trueminx - pos.first;
      vel.first = -vel.first;
    }
    if (pos.first > truemaxx) {
      pos.first = truemaxx - (pos.first - truemaxx);
      vel.first = -vel.first;
    }
    if (pos.second < trueminy) {
      pos.second = trueminy + trueminy - pos.second;
      vel.second = -vel.second;
    }
    if (pos.second > truemaxy) {
      pos.second = truemaxy - (pos.second - truemaxy);
      vel.second = -vel.second;
    }

}
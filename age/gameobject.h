#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <utility>
#include <vector>
#include "prefab.h"
#include "collider.h"
#include "state.h"

template <typename...> 
class GameObject {
 protected:
  State& state;

 public:
  const int id;
  int height;
  std::pair<int, int> pos;
  std::shared_ptr<Prefab> prefab;
  std::shared_ptr<Collider<>> collider;
  
  GameObject(State& state, int id, int height,
             std::pair<int, int> pos,
             std::shared_ptr<Prefab> prefab, 
             std::shared_ptr<Collider<>> collider)
      : state{state},
        id{id},
        height{height},
        pos{pos},
        prefab{prefab},
        collider{collider} {}

  virtual void update(const std::vector<int>& input) = 0;

  void Collide(GameObject<>& other){}
  void onCollision();
  virtual ~GameObject() {}
};

template <typename Obj, typename... Objs>
class GameObject<Obj, Objs...> : public GameObject<Objs...> {
 public:
  using GameObject<Objs...>::onCollision;
  using GameObject<Objs...>::Collide;
  
  GameObject<Obj, Objs...>(State& state, int id, int height,
          std::pair<int, int> pos,
          std::shared_ptr<Prefab> prefab, 
          std::shared_ptr<Collider<>> collider)
    : GameObject<Objs...>::GameObject(state, id, height, pos, prefab, collider) {}

  virtual void onCollision(Obj& other) = 0;

  virtual void Collide(Obj& other) = 0;
  /*void Collide(Obj& other) {
    if (this->collider->checkCollision(*other.collider)) {
      onCollision(other);
      other.onCollision(*this);
    }
  }*/
};

#endif
#ifndef ENEMIES_H
#define ENEMIES_H
#include <utility>
#include <memory>
#include "../age/gameobject.h"

#include "mycolliders2.h"
#include "mysprites.h"
#include "../age/termview.h"
#include "algorithm"

class Enemy : public GameObject<Enemy, Bullet> {
 public:
  std::pair<int, int> vel;
  Enemy(State& state, int id, int height, std::pair<int, int> pos,
       std::shared_ptr<Prefab> prefab, std::shared_ptr<EnemyCollider> collider, std::pair<int, int> vel)
      : GameObject<Enemy, Bullet>(state, id, height, pos, prefab,
                                 collider),
        vel{vel} {}
  
  void Collide(Enemy& other) {};

  void onCollision(Enemy& other) override {};
    void Collide(Bullet& other) override;
    void onCollision(Bullet& other) override;

};

class Bat: public Enemy{

    public:
        Bat(State& state, int id, int height, std::pair<int, int> pos, std::pair<int, int> vel):
            Enemy(state, id, height, pos, std::make_shared<BatSprite>(), std::make_shared<EnemyCollider>(*this), vel){}
    
    void update(const std::vector<int>& input) override {
        if (pos.first > GAMEWIDTH+20 || pos.first < -20){
            state.destroyObjects(std::vector<int> {id});
            return;
        }

        pos.first += vel.first;
        if (rand() % 20 == 0) {
            pos.second = std::max(std::min(pos.second + (rand() % 3)-2, GAMEHEIGHT-5), 1);
        }
    }
};

class Goblin: public Enemy{
    int acc = 1;
    public:
        Goblin(State& state, int id, int height, std::pair<int, int> pos, std::pair<int, int> vel, bool facing_left):
            Enemy(state, id, height, pos, std::make_shared<GoblinSprite>(facing_left), std::make_shared<EnemyCollider>(*this), vel){}

    void update(const std::vector<int>& input) override {
        if (pos.first > GAMEWIDTH+20 || pos.first < -20){
            state.destroyObjects(std::vector<int> {id});
            return;
        }
        vel.second += acc;
        if (pos.second == GAMEHEIGHT-2){
            vel.second = 0;
        }
        pos.first += vel.first;
        pos.second += vel.second;
        if (pos.second == GAMEHEIGHT-2 && rand() % 20 == 0) {
            vel.second = -3;
        }
        pos.second = std::max(std::min(pos.second + vel.second, GAMEHEIGHT-2), 1);
    }

};

#endif

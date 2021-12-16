#ifndef COIN_H
#define COIN_H
#include <utility>
#include <memory>
#include "../age/gameobject.h"

#include "mycolliders.h"
#include "coinsprite.h"
#include "../age/termview.h"

class Coin : public GameObject<Player, Ball> {

 public:
    std::vector<std::pair<int, int>> coincolors{
      std::make_pair<int, int>(COLOR_YELLOW, COLOR_BLACK),
      std::make_pair<int, int>(COLOR_RED, COLOR_BLACK),
      std::make_pair<int, int>(COLOR_CYAN, COLOR_BLACK)};
    int health = 100;

  Coin(State& state, int id, int height, std::pair<int, int> pos)
      : GameObject<Player, Ball>(state, id, height, pos, std::make_shared<CoinSprite>(),
                                 std::make_shared<CoinCollider>(*this)) {}

  void update(const std::vector<int>& input){
      if (health == 0){
          // reposition and reset health
          health = 100;
          pos.first = (rand() % (GAMEWIDTH-2))+1;
          pos.second = (rand() % (GAMEHEIGHT-2))+1;
          prefab->colors[0] = coincolors[0];
      }
      if (health == 50){
          prefab->colors[0] = coincolors[1];
      } 
      if (health == 20){
          prefab->colors[0] = coincolors[2];
      }
      --health;
  };
  
  void Collide(Player& other) override;
  
  void Collide(Ball& ball) override;

  void onCollision(Player& other) override;

  void onCollision(Ball& ball) override {
    // do nothing;
  }
};

#endif

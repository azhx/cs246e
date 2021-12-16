#include "game2.h"
#include "enemies.h"
#include "player2.h"
#include "bullet.h"
#include "../age/termview.h"


void Game::spawnEnemy(){
    std::vector<std::shared_ptr<GameObject<>>> spawns = {};
    if (rand()%3 == 0){
        //spawn goblin
        if (rand()%2 == 0){
            // left side of screen
            spawns.push_back(std::make_shared<Goblin>(
                *this, getFreeId(), 0, std::make_pair<int, int>(-5, GAMEHEIGHT-2), 
                std::make_pair<int, int>(1, 0), false));
        } else {
            // right side of screen
            spawns.push_back(std::make_shared<Goblin>(
                *this, getFreeId(), 0, std::make_pair<int, int>(GAMEWIDTH+5, GAMEHEIGHT-2), 
                std::make_pair<int, int>(-1, 0), true));
        }
        spawnObjects(spawns);
        return;
    } else {
        //spawn bat
        if (rand()%2 == 0){
            // left side of screen
            spawns.push_back(std::make_shared<Bat>(
                *this, getFreeId(), 0, std::make_pair<int, int>(-5, randy(5)), 
                std::make_pair<int, int>(2, 0)));
        } else {
            // right side of screen
            spawns.push_back(std::make_shared<Bat>(
                *this, getFreeId(), 0, std::make_pair<int, int>(GAMEWIDTH+5, randy(5)), 
                std::make_pair<int, int>(-2, 0)));
        }
        spawnObjects(spawns);
        return;
    }
}
// collision workhorse that needs to know all possible object types
void Game::doCollisions() {
  for (size_t i = 0; i < ents.size(); ++i) {
    if (auto enemy = std::dynamic_pointer_cast<Enemy>(ents[i])) {
      std::dynamic_pointer_cast<Player>(player)->Collide(*enemy);
    }
  }
  if (stopped) return;
  for (size_t i = 0; i < ents.size(); ++i) {
    for (size_t j = i + 1; j < ents.size(); ++j) {
      if (auto enemy = std::dynamic_pointer_cast<Enemy>(ents[j])) {
        if (auto caller = std::dynamic_pointer_cast<Bullet>(ents[i]))
          caller->Collide(*enemy);
      } else if (auto bullet = std::dynamic_pointer_cast<Bullet>(ents[j])) {
        if (auto caller = std::dynamic_pointer_cast<Enemy>(ents[i]))
          caller->Collide(*bullet);
      }
    }
  }
};

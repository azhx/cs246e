#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

#include <algorithm>
#include <string>
#include <utility>
#include <memory>
#include <vector>

#include "../age/state.h"
#include "ball.h"
#include "border.h"
#include "player.h"
#include "coin.h"
#include "playersprite.h"

class Game : public State {
  std::vector<int> curinput = {};

  int randx(int offset) {return rand() % (GAMEWIDTH-2-offset)+1;}
  int randy(int offset) {return rand() % (GAMEHEIGHT-2-offset)+1;}

 public:
  Game(std::vector<std::shared_ptr<GameObject<>>> ents,
       std::unordered_map<std::string, int> globals)
      : State{std::make_shared<Board>(*this, std::make_shared<Prefab>(),
                                      std::make_pair(22, 80),
                                      std::make_pair(0, 0)),
              ents, globals,
              std::make_shared<Player>(*this, 0, 0,
                                       std::make_pair<int, int>(1, 1),
                                       std::make_shared<PlayerSprite>())} {
    this->globals["score"] = 0;
    this->globals["time"] = 0;
    this->globals["zcooldown"] = 0;
    this->globals["xcooldown"] = 0;
  }

  void init() {
    std::vector<std::shared_ptr<GameObject<>>> spawns = {};
    spawns.push_back(std::make_shared<Coin>(
        *this, 9, 0, std::make_pair<int, int>(randx(0), randy(0))));
    spawns.push_back(std::make_shared<Ball>(
        *this, 7, 4, std::make_pair<int, int>(randx(3), randy(3)),
        std::make_shared<BallSprite>(3, 3), 3, std::make_pair<int, int>(-2, 2)));
    spawns.push_back(std::make_shared<Ball>(
        *this, 8, 4, std::make_pair<int, int>(randx(3), randy(3)),
        std::make_shared<BallSprite>(2, 3), 2, std::make_pair<int, int>(1, 2)));
    spawns.push_back(std::make_shared<Ball>(
        *this, 1, 1, std::make_pair<int, int>(randx(3), randy(3)),
        std::make_shared<BallSprite>(2, 0), 2, std::make_pair<int, int>(1, 2)));
    spawns.push_back(std::make_shared<Ball>(
        *this, 2, 1, std::make_pair<int, int>(randx(3), randy(3)),
        std::make_shared<BallSprite>(1, 0), 1, std::make_pair<int, int>(-1, 1)));
    spawns.push_back(std::make_shared<Ball>(
        *this, 3, 2, std::make_pair<int, int>(randx(3), randy(3)),
        std::make_shared<BallSprite>(1, 1), 1, std::make_pair<int, int>(-2, 1)));
    spawns.push_back(std::make_shared<Ball>(
        *this, 4, 2, std::make_pair<int, int>(randx(3), randy(3)),
        std::make_shared<BallSprite>(3, 1), 3, std::make_pair<int, int>(2, 2)));
    spawns.push_back(std::make_shared<Ball>(
        *this, 6, 3, std::make_pair<int, int>(randx(3), randy(3)),
        std::make_shared<BallSprite>(2, 2), 2, std::make_pair<int, int>(1, -1)));
    spawns.push_back(std::make_shared<Border>(*this, 5, 0, std::make_pair<int, int>(0, 0),
                        std::make_shared<Prefab>()));
    spawnObjects(spawns);
  }

  // collision workhorse that needs to know all possible object types 
  void doCollisions() override {
    for (size_t i = 0; i < ents.size(); ++i) {
      if (auto ball = std::dynamic_pointer_cast<Ball>(ents[i])){
          std::dynamic_pointer_cast<Player>(player)->Collide(*ball);
      } else if (auto coin = std::dynamic_pointer_cast<Coin>(ents[i])){
        std::dynamic_pointer_cast<Player>(player)->Collide(*coin);
      }
    }
    if (stopped) return;
    for (size_t i = 0; i < ents.size(); ++i) {
      for (size_t j = i + 1; j < ents.size(); ++j) {
        if (auto ball = std::dynamic_pointer_cast<Ball>(ents[j])){
            if (auto caller = std::dynamic_pointer_cast<Ball>(ents[i])) caller->Collide(*ball);
            else if (auto caller = std::dynamic_pointer_cast<Border>(ents[i])) caller->Collide(*ball);
        } else if (auto border = std::dynamic_pointer_cast<Border>(ents[j])){
            if (auto caller = std::dynamic_pointer_cast<Ball>(ents[i])) caller->Collide(*border);
        } 
      }
    }
  };
  
  void update(const std::vector<int>& input) override {
    if (stopped) return;
    curinput = input;
    player->update(input);
    for (size_t i = 0; i < ents.size(); ++i) {
      ents[i]->update(input);
    }
    ++globals["time"];
    globals["zcooldown"] = std::max(globals["zcooldown"] - 1, 0);
    globals["xcooldown"] = std::max(globals["xcooldown"] - 1, 0);
  };
  void renderStatus(WINDOW* status) const override {
    // init_pair(1, fg, bg);
    // attron(COLOR_PAIR(1));
    std::string tmpbuf = "";
    for (size_t i = 0; i < curinput.size(); ++i) {
      tmpbuf += ",";
      tmpbuf += std::to_string(curinput[i]);
    }
    //mvwprintw(status, 0, 0, "%s", tmpbuf.c_str());
    mvwprintw(status, 1, 1, "Score: %d", this->globals.at("score"));
    mvwprintw(status, 1, 40, "Time: %d", this->globals.at("time"));
    if (!this->globals.at("xcooldown"))
      mvwprintw(status, 2, 1, "X-Cooldown: Ready");
    else
      mvwprintw(status, 2, 1, "X-Cooldown: %d", this->globals.at("xcooldown"));
    if (!this->globals.at("zcooldown"))
      mvwprintw(status, 2, 40, "Z-Cooldown: Ready");
    else
      mvwprintw(status, 2, 40, "Z-Cooldown: %d", this->globals.at("zcooldown"));
    // attroff(COLOR_PAIR(1));
  };
};

#endif
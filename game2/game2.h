#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

#include <algorithm>
#include <string>
#include <utility>
#include <memory>
#include <vector>

#include "../age/state.h"
#include "player2.h"
#include "board2.h"
#include "playersprite2.h"

class Game : public State {
  std::vector<int> curinput = {};

  int randx(int offset) {return rand() % (GAMEWIDTH-2-offset)+1;}
  int randy(int offset) {return rand() % (GAMEHEIGHT-2-offset)+1;}
  void spawnEnemy();

 public:
  Game(std::vector<std::shared_ptr<GameObject<>>> ents,
       std::unordered_map<std::string, int> globals)
      : State{std::make_shared<Board>(*this, std::make_shared<Prefab>(),
                                      std::make_pair(22, 80),
                                      std::make_pair(0, 0)),
              ents, globals,
              std::make_shared<Player>(*this)} {
    this->globals["time"] = 0;
  }

  // collision workhorse that needs to know all possible object types 
  void doCollisions() override;
  
  void update(const std::vector<int>& input) override {
    if (stopped) return;
    curinput = input;
    if (rand()% 20 == 0){
      spawnEnemy();
    }
    player->update(input);
    for (size_t i = 0; i < ents.size(); ++i) {
      ents[i]->update(input);
    }
    ++globals["time"];
    //globals["zcooldown"] = std::max(globals["zcooldown"] - 1, 0);
    //globals["xcooldown"] = std::max(globals["xcooldown"] - 1, 0);
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
    //mvwprintw(status, 1, 1, "Score: %d", this->globals.at("score"));
    mvwprintw(status, 1, 1, "Time: %d", this->globals.at("time"));
    mvwprintw(status, 2, 1, "Entities: %d", this->ents.size());
    // attroff(COLOR_PAIR(1));
  };
};

#endif
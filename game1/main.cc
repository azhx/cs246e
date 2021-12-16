#include <memory>
#include <vector>

#include "../age/age.h"
#include "ball.h"
#include "ballsprite.h"
#include "board.h"
#include "game.h"
#include "mycolliders.h"
#include "player.h"
#include "border.h"
#include "playersprite.h"

int main(int argc, char *argv[]) {
  srand(time(0));
  int tickrate = 100;
  bool colors = false;
  for (int i = 0; i < argc; ++i){
    if ((std::string) argv[i] == "-ts"){
      if (i+1 < argc) tickrate = atoi(argv[i+1]);
    }
    if ((std::string) argv[i] == "-withcolor"){
      colors = true;
    }
  }
  std::shared_ptr<Game> gameState = std::make_shared<Game>(
      std::vector<std::shared_ptr<GameObject<>>>(),
      std::unordered_map<std::string, int>());
  gameState->init();
  Model runtime(std::make_unique<TermView>(colors),
                std::make_unique<KBController>(tickrate), gameState);
  runtime.go();
}

// TODO:
// Collision with Player
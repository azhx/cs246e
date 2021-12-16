#include <memory>
#include <vector>

#include "../age/age.h"
#include "game2.h"
#include "mycolliders2.h"
#include "player2.h"
#include "playersprite2.h"

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
  Model runtime(std::make_unique<TermView>(colors),
                std::make_unique<KBController>(tickrate), gameState);
  runtime.go();
}

#include "Game.h"

void Game::start() {
  this->drawScreen();

  while(state == 0) {
    if(getMove()) {
      std::cout << "Redrawing the screen";
      this->drawScreen();
    }
  }
  std::cout << "Game Over\n";
}
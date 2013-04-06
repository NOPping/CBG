#include "Game.h"

void Game::start() {
  this->drawScreen();
  while(this->state==0) {
    if(getMove()) {
      this->drawScreen();
    } else {
      std::cout << "Invalid Move, try again.\n";
    }
  }

  std::cout << "Game ended with state: " << this->state << "\n";
}

void Game::clearScreen() {
  std::cout << "\033[2J\033[;H";
}
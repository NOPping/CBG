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

std::ostream& operator<<(std::ostream& out, const Square& square) {
  for(int i=0; i<square.amountOfPlayers; i++) {
    if(square.pieces[i] != 0) {
      out << (square.start + square.pieces[i]->putPiece() + square.end);
      return out;
    }
  }
  out << (square.start + " " + square.end);
  return out;
}
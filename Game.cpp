#include "Game.h"

using std::cout;
using std::ostream;

Game::Game() {}

Game::~Game() {}

void Game::start() {
  drawScreen();
  while(state==0) {
    if(getMove()) {
      drawScreen();
    } else {
      cout << "Invalid Move, try again.\n";
    }
  }

  cout << "Game ended with state: " << state << "\n";
}

void Game::clearScreen() {
  cout << "\033[2J\033[;H";
}

ostream& operator<<(ostream& out, const Square& square) {
  for(int i=0; i<square.amountOfPlayers; i++) {
    if(square.pieces[i] != 0) {
      out << *square.pieces[i];
      return out;
    }
  }
  out << " ";
  return out;
}

ostream& operator<<(ostream& out, const Piece& piece) {
  out << piece.owner->getCharacter(piece.type);
  return out;
}
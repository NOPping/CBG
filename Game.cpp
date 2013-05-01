/// Base foundation for all of the games.
/// @author Ian Duffy
/// @author Darren Brogan

#include "Game.h"

using std::cout;
using std::ostream;

Game::Game(const int amountOfPlayers, const int columns, const int rows)
: amountOfPlayers(amountOfPlayers), columns(columns), rows(rows) {
  this->currentPlayer = 0;
  this->players = new Player*[this->amountOfPlayers];
  this->grid = new Square*[rows];
  for(int i=0; i<rows; i++) {
    this->grid[i] = new Square[columns];
  }
}

Game::~Game() {
  for(int i=0; i<rows; i++) {
    delete [] grid[i];
  }
  delete [] grid;
  for(int i=0; i<amountOfPlayers; i++) {
    delete players[i];
  }
  delete [] players;
}

/// Controls the flow of the game, Continues to call getMove() until
/// isOver() returns something other than 0.
void Game::start() {
  drawScreen();
  while(isOver()=0) {

    if(getMove()) {
      drawScreen();
    } else {
      cout << "Invalid Move, try again.\n";
    }
  }

  if(isOver()=1) {
    int winner =  currentPlayer-1 == -1  ? amountOfPlayers : currentPlayer;
    cout << "Player " << winner << " has won the game\n";
  } 
  // A draw is the only other opeion so no need to test agagin
  else {
    cout << "Game ended in a draw\n";
  }
}


/// Clears the terminal window.
void Game::clearScreen() const {
  cout << CLEAR;
}

/// Overrides the insert operator for a square.
ostream& operator << (ostream& os, const Square& square) {
  for(int i=0; i<square.amountOfPlayers; i++) {
    if(square.pieces[i] != 0) {
      square.pieces[i]->print(os);
      return os;
    }
  }
  os << " ";
  return os;
}

/// Overrides the insert operator for a piece.
ostream& operator << (ostream& os, const Piece& piece) {
  piece.print(os);
  return os;
}

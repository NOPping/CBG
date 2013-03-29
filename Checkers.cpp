#include "Checkers.h"

Checkers::Checkers() {
  this->rows = 8;
  this->columns = 8;
  this->amountOfPlayers = 2;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];
  this->grid = new Square*[rows];
  for(int i=0;i<rows;i++) {
    this->grid[i] = new Square[columns];
  }
  
  int amountOfTypes=2;
  std::string types[] = {"○","◎"};
  this->players[0] = Player(&amountOfTypes,types,12);
  this->players[1] = Player(&amountOfTypes,types,12);
  
  std::string squareRepresentations[] = {"\033[0;37;47m   \033[0m","\033[0;37;40m   \033[0m"};
  int squareIdentifier = 1;
  
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      this->grid[i][j] = Square(squareIdentifier,
                                squareRepresentations[squareIdentifier]);
      squareIdentifier = (squareIdentifier + 1)%2;
    }
    squareIdentifier = (squareIdentifier + 1)%2;
  }
}

void Game::drawScreen() {
  std::cout << "\033[2J\033[;H";
  std::cout << "Player " << (this->currentPlayer+1) << " it is your go\n";
  //std::cout << this->grid[0][0].representation;
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      std::cout << grid[i][j].putSquare();
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
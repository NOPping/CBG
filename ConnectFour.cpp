#include "ConnectFour.h"

ConnectFour::ConnectFour() {
  this->rows = 7;
  this->columns = 6;
  this->amountOfPlayers = 2;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];
  this->grid = new Square*[rows];
  this->columnSpace = new int[columns];
  for(int currentRow=0;currentRow<rows;currentRow++) {
    this->grid[currentRow] = new Square[columns];
  }
  
  int amountOfTypes=2;
  std::string types[] = {"○","◎"};
  this->players[0] = Player(&amountOfTypes,types,21);
  this->players[1] = Player(&amountOfTypes,types,21);
  
  std::string squareRepresentation = "| ";
  int squareIdentifier = 1;
  
  for(int currentRow=0;currentRow<rows;currentRow++) {
    for(int currentColumn=0;currentColumn<columns;currentColumn++) {
      this->grid[currentRow][currentColumn] = Square(squareIdentifier,
                                squareRepresentation, Coordinate(currentRow, currentColumn));
      squareIdentifier = (squareIdentifier + 1)%2;
    }
    squareIdentifier = (squareIdentifier + 1)%2;
  }
}

void Game::drawScreen() {
  std::cout << "\033[2J\033[;H";
  std::cout << "Player " << (this->currentPlayer+1) << " it is your go\n";
  //std::cout << this->grid[0][0].representation;
  for(int currentRow=0;currentRow<rows;currentRow++) {
    for(int currentColumn=0;currentColumn<columns;currentColumn++) {
      std::cout << grid[currentRow][currentColumn].putSquare();
    }
    std::cout << "|\n";
  }
  std::cout << "\n";
}

bool ConnectFour::isGameOver() {
  return (fourInRow() || topRowFull());
}

bool ConnectFour::fourInRow() {
  for(int currentColumn = 0; currentColumn < columns; currentColumn++) {
    for(int currentRow = 0; currentRow < rows; currentRow++) {
    Square current = grid[currentColumn][currentRow];
      if(current.hasPieces()) {
        if(checkNextSquare(current, 1, 0) == 4)     // Check east
        if(checkNextSquare(current, 1, 1) == 4);    // Check north east
        if(checkNextSquare(current, -1, 1) == 4);   // Check north west
        if(checkNextSquare(current, 0, 1) == 4);    // Check north
      }
    }
  }
  return false;
}

int ConnectFour::checkNextSquare(Square current, int nextColumnOffset, int nextRowOffset) {
  Coordinate currentPosition = current.getPosition();
  Square next = grid[currentPosition.x + nextColumnOffset][currentPosition.y + nextRowOffset];
  //need to implement a check here to see if owners are the same, not implemented yet
  if(next.getPieces() == current.getPieces()) {
    return checkNextSquare(next, nextColumnOffset + nextColumnOffset, nextRowOffset + nextRowOffset) + 1;
  }
  else return 1;
}

bool ConnectFour::topRowFull() {
  for(int currentColumn = 0; currentColumn < columns; currentColumn++) {
    if(columnSpace[currentColumn] != rows) {
      return false;
    }
  }
  return true;
}
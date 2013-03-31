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
/**
 * Function to draw the screen used to play connect four.
 */
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

/**
 * Function to reurn weather or not the game is over.
 */
bool ConnectFour::isGameOver() {
  return (fourInRow() || topRowFull());
}
/**
 * Function to return true if four or more player pieces are in a row
 */
bool ConnectFour::fourInRow() {
  for(int currentColumn = 0; currentColumn < columns; currentColumn++) {
    for(int currentRow = 0; currentRow < rows; currentRow++) {
      Square current = grid[currentRow][currentColumn];
      Coordinate currentPosition = current.getPosition();
      if(current.hasPieces()) {
        if(checkNextSquare(current, grid[currentPosition.y + 0][currentPosition.x + 1], 0, 1) == 4)  return true;       // Check east
        else if(checkNextSquare(current, grid[currentPosition.y + 1][currentPosition.x + 1], 1, 1) == 4) return true;  // Check north east
        else if(checkNextSquare(current, grid[currentPosition.y + 1][currentPosition.x - 1], 1, -1) == 4) return true;  // Check north west
        else if(checkNextSquare(current, grid[currentPosition.y + 1][currentPosition.x + 0], 1, 0) == 4)  return true; // Check north
      }
    }
  }
  return false;
}
/**
 * Recursive function to return the number of player pieces in a row
 */
int ConnectFour::checkNextSquare(Square current, Square next, int nextRowOffset, int nextColumnOffset) {
  Coordinate nextPosition = next.getPosition();
  Piece* piecesOnNextSquare = next.getPieces();
  Piece* piecesOnCurrentSquare = current.getPieces();
  if(piecesOnCurrentSquare[currentPlayer].getOwner() == piecesOnNextSquare[currentPlayer].getOwner()) {
    return checkNextSquare(next, grid[nextPosition.y + nextRowOffset][nextPosition.x + nextColumnOffset], nextRowOffset, nextColumnOffset) + 1;
  }
  else return 1;
}
/**
 * Function to test if top row is full
 */
bool ConnectFour::topRowFull() {
  for(int currentColumn = 0; currentColumn < columns; currentColumn++) {
    if(columnSpace[currentColumn] != rows) {
      return false;
    }
  }
  return true;
}
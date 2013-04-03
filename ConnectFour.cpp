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
  for(int currentRow=0; currentRow<rows; currentRow++) {
    this->grid[currentRow] = new Square[columns];
  }

  int amountOfTypes=2;
  std::string types[] = {"○","◎"};
  this->players[0] = Player(&amountOfTypes,types,21);
  this->players[1] = Player(&amountOfTypes,types,21);

  std::string squareRepresentation = "| ";
  int squareIdentifier = 1;

  for(int currentRow=0; currentRow<rows; currentRow++) {
    for(int currentColumn=0; currentColumn<columns; currentColumn++) {
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
  for(int currentRow=0; currentRow<rows; currentRow++) {
    for(int currentColumn=0; currentColumn<columns; currentColumn++) {
      std::cout << grid[currentRow][currentColumn].putSquare();
    }
    std::cout << "|\n";
  }
  std::cout << "\n";
}

/**
 * Function to reurn weather or not the game is over.
 */
bool ConnectFour::isGameOver(Square current) {
  return (fourInRow(Square current) || topRowFull());
}
/**
 * Function to return true if four or more player pieces are in a row
 */
bool ConnectFour::fourInRow(Square current) {
  Coordinate currentPosition = current.getPosition();
  for(int currentRowOffset = -1; currentRowOffset <= 0; currentRowOffset++) {
    for(int currentColumnOffset = -1;currentColumnOffset <= 0; currentColumnOffset++) {
      if(currentRowOffset != 0 || currentColumnOffset != 0) {
        int amountOfPlayerPliecesFirstSide = checkNextSquare(grid[currentPosition.y + currentColumnOfset][currentPosition.x + currentRowOffset], currentColumnOfset, currentRowOffset);
        int amountOfPlayerPliecesSecondSide = checkNextSquare(4grid[currentPosition.y + currentColumnOfset*-1a][currentPosition.x + currentRowOffset*-1], currentColumnOfset*-1, currentRowOffset*-1);
        if((1 + amountOfPlayerPliecesFirstSide + amountOfPlayerPliecesSecondSide) > 3)
           return true;
      }
    }
  }
  return false;
}
/**
 * Recursive function to return the number of player pieces in a row
 */
int ConnectFour::checkNextSquare(Square next, int nextRowOffset, int nextColumnOffset) {
  Coordinate nextPosition = next.getPosition();
  if(next.hasPieceOwnedBy(curentPlayer)) {
    return checkNextSquare(grid[nextPosition.y + nextRowOffset][nextPosition.x + nextColumnOffset], nextRowOffset, nextColumnOffset) + 1;
  }
  else return 0;
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
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
  for(int rowOffset = -1; rowOffset <= 0; rowOffset++)  {
    for(int columnOffset = -1; columnOffset <= 0; columnOffset++) {
      if(currentRowOffset != 0 || currentColumnOffset != 0) {
        int numPlayerPiecesFirstSide  = checkNextSquare(grid[currentPosition.y + columnOffset][currentPosition.x + rowOffset], columnOfset, rowOffset);
        int numPlayerPiecesSecondSide = checkNextSquare(grid[currentPosition.y + columnOffset*-1][currentPosition.x + rowOffset*-1], columnOffset*-1, rowOffset*-1);
        if((1 + numPlayerPiecesFirstSide + numPlayerPiecesSecondSide) > 3) return true;
      }
    }
  }
  return false;
}
/**
 * Recursive function to return the number of player pieces in a row
 */
int ConnectFour::checkNextSquare(Square next, int rowOffset, int columnOffset) {
  if(next.hasPieceOwnedBy(curentPlayer)) {
    Coordinate nextPosition = next.getPosition();
    return 1 + checkNextSquare(grid[nextPosition.y + rowOffset][nextPosition.x + columnOffset], rowOffset, columnOffset);
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
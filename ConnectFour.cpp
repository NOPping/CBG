#include "ConnectFour.h"

using namespace std;

ConnectFour::ConnectFour() {
  this->rows = 7;
  this->columns = 6;
  this->amountOfPlayers = 2;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];
  this->grid = new Square*[rows];
  this->columnSpace = new int[columns];
  for(int i=0; i<rows; i++) {
    this->columnSpace[i] = 0;
  }
  for(int currentRow=0; currentRow<rows; currentRow++) {
    this->grid[currentRow] = new Square[columns];
  }

  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 12;
  std::string types[] = {"O","◎"};
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = types[0];
  player2PieceTypes[0] = types[1];

  this->players[0] = Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = Player(amountOfPieceTypes,
                            player2PieceTypes,maxAmountOfPlayerPieces);

  std::string start = "| ";
  std::string end = " ";

  for(int currentRow=0; currentRow<rows; currentRow++) {
    for(int currentColumn=0; currentColumn<columns; currentColumn++) {
      this->grid[currentRow][currentColumn] = Square(1, start, end,amountOfPlayers, Coordinate(currentRow, currentColumn));
    }
  }
}
/**
 * Function to draw the screen used to play connect four.
 */
void ConnectFour::drawScreen() {
  this->clearScreen();
  std::cout << "Player " << (this->currentPlayer+1) << " it is your go\n";
  //std::cout << this->grid[0][0].representation;
  std::cout << "_________________________\n";
  for(int currentRow=0; currentRow<rows; currentRow++) {
    for(int currentColumn=0; currentColumn<columns; currentColumn++) {
      std::cout << grid[currentRow][currentColumn].getStart();
      std::cout << grid[currentRow][currentColumn];
      std::cout << grid[currentRow][currentColumn].getEnd();
    }
    std::cout << "|\n";
  }
  std::cout << "_________________________\n";
  std::cout << "\n";
}

/**
 * Function to reurn weather or not the game is over.
 */
bool ConnectFour::isGameOver(Square current) {
  return (this->fourInRow(current) || this->topRowFull());
}
/**
 * Function to return true if four or more player pieces are in a row
 */
bool ConnectFour::fourInRow(Square current) {
  Coordinate currentPosition = current.getPosition();
  for(int rowOffset = -1; rowOffset <= 0; rowOffset++)  {
    for(int columnOffset = -1; columnOffset <= 0; columnOffset++) {
      if(rowOffset != 0 || columnOffset != 0) { //Make sure we avoid infinate recursion by not checking current square
        int numPlayerPiecesFirstSide  = checkNextSquare(grid[currentPosition.y + columnOffset][currentPosition.x + rowOffset], columnOffset, rowOffset);
        int numPlayerPiecesSecondSide = checkNextSquare(grid[currentPosition.y - columnOffset][currentPosition.x - rowOffset], columnOffset*-1, rowOffset*-1);
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
  if(next.hasPieceOwnedBy(currentPlayer)) {
    Coordinate nextPosition = next.getPosition();
    return 1 + checkNextSquare(grid[nextPosition.y + rowOffset][nextPosition.x + columnOffset], rowOffset, columnOffset);
  } else return 0;
}

bool ConnectFour::getMove() {
  int x,y;
  bool validInput = false;
  do {
    cout << "Type in the X coordinate of the column you would like to "
    << "add your piece to:\n";
    cin >> x;
    validInput = isValidMove(x);
  } while(!validInput);
  this->executeMove(x);
  return true;
}

bool ConnectFour::isValidMove(int destinationX) {
  if(columnSpace[destinationX] < columns) return true;
  else {
    cout << "Destination column is full\n";
    return false;
  }
}

bool ConnectFour::executeMove(int destinationX) {
  int destinationY = columnSpace[destinationX];
  this->columnSpace[destinationX]++;
  Square destinationSquare = grid[destinationX][destinationY];
  cout << "Updating the destination square";
  destinationSquare.addPiece(currentPlayer,this->players[currentPlayer].addPiece());
  if(isGameOver(destinationSquare)) {
    return false;
  }
  return true;
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
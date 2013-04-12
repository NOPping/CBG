#include "ConnectFour.h"

using namespace std;

ConnectFour::ConnectFour():Game(2,6,7) {
  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 12;
  this->columnSpace.resize(columns);
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = "O";
  player2PieceTypes[0] = "◎";

  this->players[0] = Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = Player(amountOfPieceTypes,
                            player2PieceTypes,maxAmountOfPlayerPieces);


  std::string start = "| ";
  std::string end = " ";

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      this->grid[i][j] = Square(1, start, end,amountOfPlayers, Coordinate(i, j));
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
  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      std::cout << grid[i][j].getStart();
      std::cout << grid[i][j];
      std::cout << grid[i][j].getEnd();
    }
    std::cout << "|\n";
  }
  std::cout << "_________________________\n";
  std::cout << "\n";
}

/**
 * Function to reurn weather or not the game is over.
 */
int ConnectFour::isOver() {
  for(int j = 0; j < columns; j++) {
    int i = rows - 1 - columnSpace[j];
    if(grid[i][j].hasPiece()) {
      if(grid[i][j].hasPieceOwnedBy(currentPlayer)) {
        if(this->fourInRow(&grid[i][j])) return 1;
      }
    }
  }
  if (this->topRowFull()) return 2;
  return 0;
}
/**
 * Function to return true if four or more player pieces are in a row
 */
bool ConnectFour::fourInRow(Square* current) {
  Coordinate currentPosition = current->getPosition();

  for(int rowOffset = -1; rowOffset <= 0; rowOffset++)  {
    for(int columnOffset = -1; columnOffset <= 0; columnOffset++) {
      if(rowOffset != 0 || columnOffset != 0) { //Make sure we avoid infinate recursion by not checking current square
        Square* next = &grid[currentPosition.y + rowOffset][currentPosition.x + columnOffset];
        int numPlayerPiecesFirstSide  = checkNextSquare(next, rowOffset, columnOffset);
        next = &grid[currentPosition.y - rowOffset][currentPosition.x - columnOffset];
        int numPlayerPiecesSecondSide = checkNextSquare(next, rowOffset*-1,columnOffset*-1);
        if((1 + numPlayerPiecesFirstSide + numPlayerPiecesSecondSide) > 3) return true;
      }
    }
  }
  return false;
}
/**
 * Recursive function to return the number of player pieces in a row
 */
int ConnectFour::checkNextSquare(Square* next, int rowOffset, int columnOffset) {
  if(next->hasPieceOwnedBy(currentPlayer)) {
    Coordinate nextPosition = next->getPosition();
    return 1 + checkNextSquare(&grid[nextPosition.y + rowOffset][nextPosition.x + columnOffset], rowOffset, columnOffset);
  } else return 0;
}

bool ConnectFour::getMove() {
  int x;
  bool validInput = false;
  do {
    cout << "Type in the X coordinate of the column you would like to "
    << "add your piece to:\n";
    cin >> x;
	
    validInput = isValidMove(x - 1);
  } while(!validInput);
  this->executeMove(x - 1);
  currentPlayer = (currentPlayer + 1) % 2;
  return true;
}

bool ConnectFour::executeMove(int destinationX) {
  this->columnSpace[destinationX]++;
  int destinationY = rows - columnSpace[destinationX];
  grid[destinationY][destinationX].addPiece(currentPlayer,this->players[currentPlayer].addPiece());
  return true;
}

bool ConnectFour::isValidMove(int destinationX) {
  if(destinationX > columns || destinationX < 0) {
    cout << "Your input fell out of the bounds of the board\n";
    return false;
  }
  else if(columnSpace[destinationX] > rows) {
	cout << "Destination column is full\n";
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

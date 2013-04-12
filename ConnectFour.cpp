#include "ConnectFour.h"

using namespace std;

ConnectFour::ConnectFour():Game(2,7,6) {

  state = 0;
  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 12;
  this->columnSpace.resize(columns);
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = "○";
  player2PieceTypes[0] = "◎";

  this->players[0] = new Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = new Player(amountOfPieceTypes,
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
  std::cout << "\n";
  for(int i=1; i<=columns; i++) cout << "  " << i << " ";
  std::cout << "\n";
  std::cout << "+---+---+---+---+---+---+---+\n";
  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      std::cout << grid[i][j].getStart();
      std::cout << grid[i][j];
      std::cout << grid[i][j].getEnd();
    }
    std::cout << "|\n";
    std::cout << "+---+---+---+---+---+---+---+\n";
  }
  std::cout << "\n";
}

/**
 * Function to reurn weather or not the game is over.
 */
int ConnectFour::isOver() {
  return state;
}
int ConnectFour::isOver(Square* current) {
  if(this->fourInRow(current)) return 1;
  else if (this->topRowFull()) return 2;
  else return 0;
}
/**
 * Function to return true if four or more player pieces are in a row
 */
bool ConnectFour::fourInRow(Square* current) {
  Coordinate currentPosition = current->getPosition();
  for(int rowOffset = 0; rowOffset <= 1; rowOffset++)  {
    for(int colOffset = 0; colOffset <= 1; colOffset++) {
      int numPlayerPiecesFirstSide  = checkNext(current, rowOffset, colOffset);
      int numPlayerPiecesSecondSide = checkNext(current, 0-rowOffset, 0-colOffset);
      if((1+ numPlayerPiecesFirstSide + numPlayerPiecesSecondSide) >3) return true;
    }
  }
  return false;
}
/**
 * Recursive function to return the number of player pieces in a row
 */
int ConnectFour::checkNext(Square* current,int rowOffset,int colOffset) {
  if(current->hasPieceOwnedBy(currentPlayer)) {
    Coordinate currentPos = current->getPosition();
    if(isLegal(currentPos, rowOffset, colOffset)) {
      Square* next = &grid[currentPos.y + rowOffset][currentPos.x + colOffset];
      return 1 + checkNext(next, rowOffset, colOffset);
    }
  }
  return 0;
}

bool ConnectFour::isLegal(Coordinate currentPos,int rowOffset,int colOffset) {
  return((currentPos.x + colOffset < columns)&&(currentPos.x + colOffset >= 0))
        &&(currentPos.y + rowOffset < columns)&&(currentPos.y + rowOffset >= 0)
        &&(rowOffset != 0 || colOffset != 0);
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
  grid[destinationY][destinationX].addPiece(currentPlayer,this->players[currentPlayer]->addPiece());
  state = isOver(&grid[destinationY][destinationX]);
  return true;
}

bool ConnectFour::isValidMove(int destinationX) {
  if(destinationX > columns || destinationX < 0) {
    cout << "Your input fell out of the bounds of the board\n";
    return false;
  }
  else if(columnSpace[destinationX] >= rows) {
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
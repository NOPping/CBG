#include "ConnectFour.h"

using namespace std;

ConnectFour::ConnectFour():Game(2,7,6) {

  state = 0;
  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 12;
  this->columnSpace.resize(columns);
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = "\033[33m○\033[0m";
  player2PieceTypes[0] = "\033[38m○\033[0m";

  this->players[0] = new Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = new Player(amountOfPieceTypes,
                            player2PieceTypes,maxAmountOfPlayerPieces);


  std::string start = "\033[36m| \033[0m";
  std::string end = " ";

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      this->grid[i][j] = Square(1, start, end,amountOfPlayers, Coordinate(j, i));
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
  std::cout << "\033[36m+---+---+---+---+---+---+---+\033[0m\n";
  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      std::cout << grid[i][j].getStart();
      std::cout << grid[i][j];
      std::cout << grid[i][j].getEnd();
    }
    std::cout << "\033[36m|\033[0m\n";
    std::cout << "\033[36m+---+---+---+---+---+---+---+\033[0m\n";
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
      int numPlayerPiecesFirstSide  = checkNext(current,   rowOffset,   colOffset);
      int numPlayerPiecesSecondSide = checkNext(current, 0-rowOffset, 0-colOffset);
      if((numPlayerPiecesFirstSide + numPlayerPiecesSecondSide) > 3) return true;
    }
  }
  return false;
}
/**
 * Recursive function to return the number of player pieces in a row
 */
int ConnectFour::checkNext(Square* current,int rowOffset,int colOffset) {
  if(current->hasPieceOwnedBy(currentPlayer)) {
    if(isLegal(current, rowOffset, colOffset)) {
      Coordinate currentPos = current->getPosition();
      Square* next = &grid[currentPos.y + rowOffset][currentPos.x + colOffset];
      return 1 + checkNext(next, rowOffset, colOffset);
    }
    return 1;
  }
  return 0;
}

bool ConnectFour::isLegal(Square* current,int rowOffset,int colOffset) {
  Coordinate currentPos = current->getPosition();
  return((currentPos.x + colOffset < columns)&&(currentPos.x + colOffset >= 0))
        &&(currentPos.y + rowOffset < rows)&&(currentPos.y + rowOffset >= 0)
        &&(rowOffset != 0 || colOffset != 0);
}

bool ConnectFour::getMove() {
  int x;
  bool validInput = false;
  do {
    cout << "Type in the X coordinate of the column you would like to "
         << "add your piece to:\n";
    cin >> x;
    // Derement x
    x--;
    // Check that input is a numeric value
    if(cin.fail()) {
      cout << "\nYou entered a non numeric value, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }
    if(x >= columns || x < 0) {
      cout << "Your input fell out of the bounds of the board\n";
    }
    else if(columnSpace[x] >= rows) {
      cout << "Destination column is full\n";
    }
    else validInput = true;

  } while(!validInput);
  this->executeMove(x);
  currentPlayer = (currentPlayer + 1) % 2;
  return true;
}

bool ConnectFour::executeMove(int x) {
  this->columnSpace[x]++;
  int y = rows - columnSpace[x];
  grid[y][x].addPiece(currentPlayer,this->players[currentPlayer]->addPiece());
  state = isOver(&grid[y][x]);
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

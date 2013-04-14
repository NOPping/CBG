#include "ConnectFour.h"

using namespace std;

ConnectFour::ConnectFour():Game(2,7,6) {

  state = 0;
  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 21;
  this->columnSpace.resize(columns);
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = FYELLOW "○";
  player2PieceTypes[0] = FRED "○";

  this->players[0] = new Player(amountOfPieceTypes,
                                player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = new Player(amountOfPieceTypes,
                                player2PieceTypes,maxAmountOfPlayerPieces);


  std::string start = FBLUE "| ";
  std::string end = " " RESET;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      this->grid[i][j] = Square(1, start, end,amountOfPlayers,
                                Coordinate(j, i));
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
  for(int iOffset = 0; iOffset <= 1; iOffset++)  {
    for(int jOffset = 0; jOffset <= 1; jOffset++) {
      int numPlayerPiecesFirstSide  = checkNext(current,  iOffset,  jOffset);
      int numPlayerPiecesSecondSide = checkNext(current,0-iOffset,0-jOffset);
      if((numPlayerPiecesFirstSide +numPlayerPiecesSecondSide -1) > 3)
        return true;
    }
  }
  return false;
}
/**
 * Recursive function to return the number of player pieces in a row
 */
int ConnectFour::checkNext(Square* current,int iOffset,int jOffset) {
  if(current->hasPieceOwnedBy(currentPlayer)) {
    if(isLegal(current, iOffset, jOffset)) {
      Coordinate currentPos = current->getPosition();
      Square* next = &grid[currentPos.y + iOffset][currentPos.x + jOffset];
      return 1 + checkNext(next, iOffset, jOffset);
    }
    return 1;
  }
  return 0;
}

bool ConnectFour::isLegal(Square* current,int iOffset,int jOffset) {
  Coordinate currentPos = current->getPosition();
  return((currentPos.x + jOffset < columns)&&(currentPos.x + jOffset >= 0))
        &&(currentPos.y + iOffset < rows)&&(currentPos.y + iOffset >= 0)
        &&(iOffset != 0 || jOffset != 0);
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
  grid[y][x].addPiece(currentPlayer,
                      this->players[currentPlayer]->addPiece());
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

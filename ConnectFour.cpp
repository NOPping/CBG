/// ConnectFour Game.
/// @author Darren Brogan

#include "ConnectFour.h"

using namespace std;

ConnectFour::ConnectFour():Game(2,7,6) {
  state = 0;
  
  ///Setup the players.
  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 21;
  columnSpace.resize(columns);
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = FYELLOW "○";
  player2PieceTypes[0] = FWHITE "○";

  players[0] = new Player(amountOfPieceTypes,
                                player1PieceTypes,maxAmountOfPlayerPieces);

  players[1] = new Player(amountOfPieceTypes,
                                player2PieceTypes,maxAmountOfPlayerPieces);


  ///Setup the start and end of each square
  string start = FBLUE "| ";
  string end = " " RESET;

  ///Setup the squares in the grid.
  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      grid[i][j] = Square(1, start, end,amountOfPlayers,
                                Coordinate(j, i));
    }
  }
}

void ConnectFour::drawScreen() {
  clearScreen();
  cout << "Player " << (currentPlayer+1) << " it is your go\n";
  cout << "\n";
  for(int i=1; i<=columns; i++) cout << "  " << i << " ";
  cout << "\n";
  cout << FBLUE " +---+---+---+---+---+---+---+" RESET << "\n";
  for(int i=0; i<rows; i++) {
    cout << " ";
    for(int j=0; j<columns; j++) {
      cout << grid[i][j].getStart();
      cout << grid[i][j];
      cout << grid[i][j].getEnd();
    }
    cout << FBLUE "|" RESET << "\n";
    cout << FBLUE " +---+---+---+---+---+---+---+" RESET << "\n";
  }
  cout << "\n";
}

int ConnectFour::isOver() {
  return state;
}

int ConnectFour::isOver(Square* current) {
  if(fourInRow(current)) return 1;
  else if (topRowFull()) return 2;
  else return 0;
}

bool ConnectFour::fourInRow(Square* current) {
  Coordinate currentPosition = current->getPosition();
  for(int iOffset = -1; iOffset <= 1; iOffset++)  {
    for(int jOffset = -1; jOffset <= 1; jOffset++) {
      int numPlayerPiecesFirstSide  = checkNext(current,  iOffset,  jOffset);
      int numPlayerPiecesSecondSide = checkNext(current,0-iOffset,0-jOffset);
      if((numPlayerPiecesFirstSide + numPlayerPiecesSecondSide) > 4)
        return true;
    }
  }
  return false;
}

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
    cout << "\nType in the X coordinate of the column you would like to "
    << "add your piece to:\n";
    cin >> x;
    // Decrement x
    x--;
    // Check that input is a numeric value
    if(cin.fail()) {
      cout << "\nYou entered a non numeric value, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }
    if(x >= columns || x < 0) {
      cout << "\nYour input fell out of the bounds of the board\n";
    } else if(columnSpace[x] >= rows) {
      cout << "\nDestination column is full\n";
    } else validInput = true;

  } while(!validInput);
  executeMove(x);
  currentPlayer = (currentPlayer + 1) % 2;
  return true;
}

bool ConnectFour::executeMove(int x) {
  columnSpace[x]++;
  int y = rows - columnSpace[x];
  grid[y][x].addPiece(currentPlayer,players[currentPlayer]->addPiece());
  state = isOver(&grid[y][x]);
  return true;
}

bool ConnectFour::topRowFull() {
  for(int currentColumn = 0; currentColumn < columns; currentColumn++) {
    if(columnSpace[currentColumn] != rows) {
      return false;
    }
  }
  return true;
}

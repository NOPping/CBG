/// ConnectFour Game.
/// @author Darren Brogan

#include "ConnectFour.h"

using namespace std;

ConnectFour::ConnectFour():Game(2,7,6) {
  state = 0;
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


  string start = FBLUE "| ";
  string end = " " RESET;

  for(int y=0; y<rows; y++) {
    for(int x=0; x<columns; x++) {
      grid[y][x] = Square(1, start, end,amountOfPlayers,
                          Coordinate(x, y));
    }
  }
}

/// Deconstructor for Connect Four
ConnectFour::~ConnectFour() {

}

void ConnectFour::drawScreen() const {
  clearScreen();
  cout << "Player " << (currentPlayer+1) << " it is your go\n";
  cout << "\n";
  for(int i=1; i<=columns; i++) cout << "  " << i << " ";
  cout << "\n";
  cout << FBLUE " +---+---+---+---+---+---+---+" RESET << "\n";
  //Print out each square of the board
  for(int y=0; y<rows; y++) {
    std::cout << " ";
    for(int x=0; x<columns; x++) {
      //Print out what's inside each square
      cout << grid[y][x].getStart();
      cout << grid[y][x];
      cout << grid[y][x].getEnd();
    }
    cout << FBLUE "|" RESET << "\n";
    cout << FBLUE " +---+---+---+---+---+---+---+" RESET << "\n";
  }
  cout << "\n";
}

int ConnectFour::isOver() const {
  return state;
}

int ConnectFour::isOver(const Square& current) const {
  if(fourInRow(current)) return 1;
  else if (topRowFull()) return 2;
  else return 0;
}

bool ConnectFour::fourInRow(const Square& current) const {
  Coordinate& currentPosition = current.getPosition();
  //Test each side of the current square.
  for(int yOffset = -1; yOffset <= 1; yOffset++)  {
    for(int xOffset = -1; xOffset <= 1; xOffset++) {
      //Get the number of pieces the first side of current square.
      int numPlayerPiecesFirstSide  = checkNext(current,  yOffset,  xOffset);
      //Get the number of pieces the second side of current square.
      int numPlayerPiecesSecondSide = checkNext(current,0-yOffset,0-xOffset);
      //Add the number of pieces each side up and test if they exceed three
      //current square is counted twice so we take one away before testing
      if((numPlayerPiecesFirstSide + numPlayerPiecesSecondSide -1) > 3)
        return true;
    }
  }
  return false;
}

int ConnectFour::checkNext(const Square& current,int yOffset,int xOffset) const {
  if(current.hasPieceOwnedBy(currentPlayer)) {
    if(isLegal(current, yOffset, xOffset)) {
      Coordinate currentPos = current.getPosition();
      //Get the next square in the row by adding the offsets to there
      //cooresponding x/y values in the Coordinate class.
      Square& next = grid[currentPos.y + yOffset][currentPos.x + xOffset];
      //Return 1 for the current piece plus check the next square and add it on.
      return 1 + checkNext(next, yOffset, xOffset);
    }
    //If the next square isn't legal just return one for the current square
    return 1;
  }
  return 0;
}


bool ConnectFour::isLegal(const Square& current,int yOffset,int xOffset) const {
  Coordinate& currentPos = current.getPosition();
  //Ensure that the next square lies inside the bounds of the board
  return((currentPos.x + xOffset < columns)&&(currentPos.x + xOffset >= 0))
         &&(currentPos.y + yOffset < rows)&&(currentPos.y + yOffset >= 0)
         &&(yOffset != 0 || xOffset != 0);
}

bool ConnectFour::getMove() {
  int x;
  bool validInput = false;
  do {
    cout << "\nType in the X coordinate of the column you would like to "
    << "add your piece to:\n";
    cin >> x;
    //Decrement x so the inputed value corresponds to how the board is
    //laid out.
    x = x - 1;
    //Check that input is a numeric value.
    if(cin.fail()) {
      cout << "\nYou entered a non numeric value, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }
    //Ensure that the number inputted lies inside the bounds of the board.
    if(x >= columns || x < 0) {
      cout << "\nYour input fell out of the bounds of the board\n";
    } else if(columnSpace[x] >= rows) {
      cout << "\nDestination column is full\n";
    } else validInput = true;
    //Loop until correct number in inputed.
  } while(!validInput);
  //pass inputed value to executeMove() function.
  executeMove(x);
  //Change currentPlayer to the next player.
  currentPlayer = (currentPlayer + 1) % 2;
  return true;
}

bool ConnectFour::executeMove(int x) {
  //Add one to the number of items in desired column.
  columnSpace[x]++;
  //Get the y destination of the piece to be added bytaking the
  //amount of pieces in the column from the total
  int y = rows - columnSpace[x];
  grid[y][x].addPiece(currentPlayer, players[currentPlayer]->addPiece());
  //Update the state variable
  state = isOver(grid[y][x]);
  return true;
}

bool ConnectFour::topRowFull() const {
  for(int currentColumn = 0; currentColumn < columns; currentColumn++) {
    //If this coloumn isn't full return false because top row isn't full
    if(columnSpace[currentColumn] != rows) {
      return false;
    }
  }
  return true;
}

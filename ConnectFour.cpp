/// ConnectFour Game.
/// @author Darren Brogan

#include "ConnectFour.h"

using std::vector;
using std::max;
using std::cout;
using std::cin;

ConnectFour::ConnectFour():Game(2,7,6) {
  state = 0;
  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 21;
  columnHeight.resize(columns);
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

/// Prints out the board and all the players pieces.
void ConnectFour::drawScreen() const {
  clearScreen();
  cout << "Player " << (currentPlayer+1) << " it is your go\n";
  cout << "\n ";
  for(int i=1; i<=columns; i++) cout << "  " << i << " ";
  cout << "\n";
  cout << FBLUE " +---+---+---+---+---+---+---+" RESET << "\n";
  // Print out each square of the board.
  for(int y=0; y<rows; y++) {
    std::cout << " ";
    for(int x=0; x<columns; x++) {
      // Print out what's inside each square.
      cout << grid[y][x].getStart();
      cout << grid[y][x];
      cout << grid[y][x].getEnd();
    }
    cout << FBLUE "|" RESET << "\n";
    cout << FBLUE " +---+---+---+---+---+---+---+" RESET << "\n";
  }
  cout << "\n";
}

/// Overloaded function to to return weather or not the game is over.
int ConnectFour::isOver() {
  return state;
}

int ConnectFour::isOver(const Square& current) const {
  if(fourInRow(current)) return 1;
  else if (isDraw()) return 2;
  else return 0;
}

/// Function to get the max amount of pieces in a line around the piece added
/// returns weather or not the number is greater than 3, signifying a win.
bool ConnectFour::fourInRow(const Square& current) const {
  int numPiecesInRow = max(
    max(
      // Vertical.
      (checkNext(current,0,1) + checkNext(current,0,-1)),
      // Diagonal down right / up left.
      (checkNext(current,1,1) + checkNext(current,-1,-1))
    ),
    max(
      // Horizontal.
      (checkNext(current,1,0) + checkNext(current,-1,0)),
      // Diagonal up right / down left.
      (checkNext(current,1,-1) + checkNext(current,-1,1))
    )
  );
  // Greater than 4 becuase current square was added in twice on each.
  return(numPiecesInRow > 4);
}

/// Recursive function to check the next square to see if it has a piece
/// to see if it's owned by current player.
int ConnectFour::checkNext(const Square& current,int yOffset,int xOffset) const {
  if(current.hasPieceOwnedBy(currentPlayer)) {
    if(isLegal(current, yOffset, xOffset)) {

      Coordinate currentPos = current.getPosition();

      // Get the next square in the row.
      Square& next = grid[currentPos.y + yOffset][currentPos.x + xOffset];

      // Return 1 for the current piece plus check the next square for piece.
      return 1 + checkNext(next, yOffset, xOffset);
    }
    // If the next square isn't legal just return one for the current square.
    return 1;
  }
  return 0;
}

/// Function to test if the next square is legal.
bool ConnectFour::isLegal(const Square& current,int yOffset,int xOffset) const {
  Coordinate currentPos = current.getPosition();

  // Ensure that the next square lies inside the bounds of the board.
  return(
    (currentPos.x + xOffset < columns)&&
    (currentPos.y + yOffset < rows)&&
    (currentPos.x + xOffset >= 0)&&
    (currentPos.y + yOffset >= 0)&&
    (yOffset != 0 || xOffset != 0)
  );
}

/// Function to request a move from the user and read it in
/// Pass move to executeMove().
bool ConnectFour::getMove() {
  int x = getPoint("\nType in the X coordinate of the column you would like to "
                   "add your piece to:\n", columns);
  // Decrememnt x so it matches how the columns are numbered in code.
  x--;
  executeMove(x);

  currentPlayer = getOpposition();
  return true;
}

/// Prompts with message to get a point between 0 and range.
int ConnectFour::getPoint(const string message, const int range) const {
  int point=0;
  while(true) {
    cout << message;
    cin >> point;

    // Check that input is a numeric value.
    if(cin.fail()) {
      drawScreen();
      cout << "\nYou entered a non numeric value, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    // Check that input is within our grid range.
    if(point < 0 || point > range) {
      drawScreen();
      cout << "\nPoint out of range, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    // Check that there's room in column.
    if(columnHeight[point-1] == rows) {
      drawScreen();
      cout << "\nColumn you selected is full\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    return point;
  }
}

/// Function to take an int representing a column and move a piece to the
/// next available slot in that column.
bool ConnectFour::executeMove(int x) {
  // Add one to the number of items in desired column.
  columnHeight[x]++;

  // Get the y destination of the piece to be added by taking the
  // amount of pieces in the column from the total amount of rows.
  int y = rows - columnHeight[x];

  if(players[currentPlayer]->hasRoomForPiece()) {
    grid[y][x].addPiece(currentPlayer, players[currentPlayer]->addPiece());
  }

  // Update the state variable.
  state = isOver(grid[y][x]);
  return true;
}

/// Functions to test if the game has ended in a draw
bool ConnectFour::isDraw() const {
  return(players[0]->getAmountOfPieces()+players[1]->getAmountOfPieces() == 42);
}

/// Returns the opposition.
int ConnectFour::getOpposition() const {
  return (currentPlayer+1)%amountOfPlayers;
}

/// Deconstructor for Connect Four.
ConnectFour::~ConnectFour() {
  columnHeight.clear();
}

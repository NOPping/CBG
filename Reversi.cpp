/// Reversi Game.
/// @author Peter Morgan

#include "Reversi.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

Reversi::Reversi():Game(2, 8, 8)  {
  // Setup the players.
  const int amountOfPieceTypes= 1;
  const int maxPlayerPieces = 64;

  vector<string> player1PieceTypes(amountOfPieceTypes);
  vector<string> player2PieceTypes(amountOfPieceTypes);

  player1PieceTypes[0] = FWHITE "◎";
  player2PieceTypes[0] = FBLACK "◎";

  players[0] =new Player(amountOfPieceTypes,player1PieceTypes,maxPlayerPieces);
  players[1] =new Player(amountOfPieceTypes,player2PieceTypes,maxPlayerPieces);

  // Setup the colors for the squares.
  string start[] = {BLIME" ",BGREEN" "};
  string end = " "RESET;

  int identifier = 0;

  for(int y=0; y<rows; y++) {
    for(int x=0; x<columns; x++) {
      // Setup the square
      grid[y][x] = Square(identifier,start[identifier],end,amountOfPlayers,
                          Coordinate(x,y));
      // Switch identifier
      identifier = (identifier+1)%2;
    }
    // Switch identifier
    identifier = (identifier+1)%2;
  }
  //add the starting pieces to the board
  grid[3][3].addPiece(0, players[0]->addPiece());
  grid[4][4].addPiece(0, players[0]->addPiece());
  grid[3][4].addPiece(1, players[1]->addPiece());
  grid[4][3].addPiece(1, players[1]->addPiece());
}

/// Prints out the board and all the players pieces.
void Reversi::drawScreen() const {
  clearScreen();
  cout << "Player " << (currentPlayer+1) << " it is your go\n\n  ";
  for(int x=0; x<columns; x++) cout << " " << x << " ";
  cout << "\n";
  for(int y=0; y<rows; y++) {
    cout << y << " ";
    for(int x=0; x<columns; x++) {
      cout << grid[y][x].getStart();
      cout << grid[y][x];
      cout << grid[y][x].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

/// Prompts with message to get a point between 0 and range.
int Reversi::getPoint(const string message, const int range) const {
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
    if(point < 0 || point >= range) {
      drawScreen();
      cout << "\nPoint out of range, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    return point;
  }
}

//prompts a player to enter an x and y coordinate using get point
//passes the coordinate on to execute move
bool Reversi::getMove() {
  Coordinate destinationCoordinate;
  Square  *destSquare;
  int x,y;
  bool validInput=false;

  while(!validInput) {
    x = getPoint("Type the X point of the piece you would like to move:\n",
                 rows);
    y = getPoint("Type the Y point of the piece you would like to move:\n",
                 columns);

    destinationCoordinate = Coordinate(x,y);

    if(grid[y][x].hasPiece()) {
      cout << "\nThe selected square is occupied, try again\n";
      continue;
    } else {
      destSquare = &grid[y][x];
      validInput=executeMove(*destSquare);
    }
    if(validInput)currentPlayer = getOpposition();

  }
  return true;
}

// call the flanks method to ensure the destination coordinate  flanks an opponents piece
//if ti does it adds the piece to the destination square
bool Reversi::executeMove(Square& destSquare)const {
  if(flanks(destSquare,true)) {
    destSquare.addPiece(currentPlayer,players[currentPlayer]->addPiece());
    return true;
  } else{
    cout<<"\nDoes not flank opponent piece\n";
    return false;
  }
}

//checks if a coordinate flanks an opponents piece
//calls check next to see if the piece is inline with an existing piece owned
//by the same player
bool Reversi::flanks(const Square current,bool flip) const {
  bool count=false;

  for(int yOffset = -1; yOffset <= 1; yOffset++)  {
    for(int xOffset = -1; xOffset <= 1; xOffset++) {
      if(isLegal(current.getPosition(),yOffset,xOffset)) {
        Coordinate currentPos = current.getPosition();
        Square& orbit = grid[currentPos.y + yOffset][currentPos.x + xOffset];
        if(checkNext(orbit,yOffset,xOffset,flip))
          count =true;
      }
    }
  }
  return count;
}

//checks a line of pieces to see if it ends with a piece that belong to the
//current player if it does, it flips the line of pieces to the current players colour
bool Reversi::checkNext(Square &current,int yOffset,int xOffset,bool flip) const {
  if(current.hasPieceOwnedBy(getOpposition()) &&
  isLegal(current.getPosition(),
  yOffset, xOffset)) {
    Coordinate currentPos = current.getPosition();
    Square& next = grid[currentPos.y + yOffset][currentPos.x + xOffset];
    if(next.hasPieceOwnedBy(currentPlayer)||checkNext(next,yOffset,xOffset,true)) {
      if(flip) {
        players[getOpposition()]->removePiece(&(current.getPiece(getOpposition())));
        current.removePiece(getOpposition());
        if(players[currentPlayer]->hasRoomForPiece()) {
          current.addPiece(((currentPlayer)),players[currentPlayer]->addPiece());
        }
      }
      return true;
    }
  }
  return false;
}

//checks if a move is  within the bounds of the board
bool Reversi::isLegal(const Coordinate current,int iOffset,int jOffset) const {
  //Ensure that the next square lies inside the bounds of the board
  return((current.x + jOffset < columns)&&(current.x + jOffset >= 0))
  &&(current.y + iOffset < rows)&&(current.y + iOffset >= 0)
  &&(iOffset != 0 || jOffset != 0);
}

//determines the winner  of the game
int Reversi::isOver() const {
  int check;
  int check2=1;
  for(int x = 0; x<rows; x++) {
    for(int y=0; y<columns; y++) {
      if(!grid[y][x].hasPiece()) {
        if(flanks(grid[y][x],false))check=0;
        check2=players[currentPlayer]->getAmountOfPieces()
        +players[getOpposition()]->getAmountOfPieces() == 64 ? 1 : 0;

      }
    }
  }
  return check+check2;
}

/// Returns the opposition.
int Reversi::getOpposition() const {
  return (currentPlayer+1)%amountOfPlayers;
}

/// Reversi Game.
/// @author Peter Morgan

#include "Reversi.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

Reversi::Reversi():Base()  {
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
  //Sets up the grid.
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

///Prompts a player to enter an x and y coordinate using get point.
///Passes the coordinate on to execute move.
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
    //Checks if the sqaure is empty.
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

// Call the flanks method to ensure the destination coordinate flanks an opponents piece.
//If it does it adds the piece to the destination square.
bool Reversi::executeMove(Square& destSquare) const {
  if(flanks(destSquare,true)) {
    destSquare.addPiece(currentPlayer,players[currentPlayer]->addPiece());
    return true;
  } else{
    cout<<"\nDoes not flank opponent piece\n";
    return false;
  }
}

//Checks if a coordinate flanks an opponents piece
//Calls check next to see if the piece is inline with an existing piece owned
//By the same player
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

//Checks a line of pieces to see if it ends with a piece that belong to the
//Current player if it does, it flips the line of pieces to the current players colour
bool Reversi::checkNext(Square &current,int yOffset,int xOffset,bool flip) const {
  if(current.hasPieceOwnedBy(getOpposition()) &&
     isLegal(current.getPosition(),yOffset, xOffset)) {
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

//Checks if a move is  within the bounds of the board
bool Reversi::isLegal(const Coordinate current,int iOffset,int jOffset) const {
  //Ensure that the next square lies inside the bounds of the board
  return((current.x + jOffset < columns)&&(current.x + jOffset >= 0))
  &&(current.y + iOffset < rows)&&(current.y + iOffset >= 0)
  &&(iOffset != 0 || jOffset != 0);
}

//Determines the winner  of the game
int Reversi::isOver() const {
  int check;
  int check2=1;
  for(int x = 0; x<rows; x++) {
    for(int y=0; y<columns; y++) {
      if(!grid[y][x].hasPiece()) {
        if(flanks(grid[y][x],false))check=0;
        //Checks if the board is full and determines the winner based on the number
        //of pieces on the board.
        check2=players[currentPlayer]->getAmountOfPieces()
        +players[getOpposition()]->getAmountOfPieces() == 64 ? 1 : 0;

      }
    }
  }
  return check+check2;
}

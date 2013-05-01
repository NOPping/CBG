/// Reversi Game.
/// @author Peter Morgan

#include "Reversi.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

Reversi::Reversi():GameWithXYSelector(2,8,8)  {
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
  // Add the starting pieces to the board
  grid[3][3].addPiece(0, players[0]->addPiece());
  grid[4][4].addPiece(0, players[0]->addPiece());
  grid[3][4].addPiece(1, players[1]->addPiece());
  grid[4][3].addPiece(1, players[1]->addPiece());
}

/// Calls getPoint to get the destination square validates the move and
/// passes the destination square onto executeMove().
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
    }

    else {
      destSquare = &grid[y][x];
      validInput=executeMove(*destSquare);
    }
  }

  currentPlayer = getOpposition();
  return true;
}

/// Call the flanks method to ensure the destination coordinate flanks an opponents piece.
/// If it does it adds the piece to the destination square.
bool Reversi::executeMove(Square& destSquare) const {

  if(flanks(destSquare,true)) {
    destSquare.addPiece(currentPlayer,players[currentPlayer]->addPiece());
    return true;
  }

  else{
    cout<<"\nDoes not flank opponent piece\n";
    return false;
  }
}

/// Checks if the current square flanks an opponents piece
/// Boolean flip is passed in to tel the function if we want to flip the pieces or we're
/// just testing if there is a place where a move could be made.
bool Reversi::flanks(const Square current,bool flip) const {
  bool madeFlank=false;

  for(int yOffset = -1; yOffset <= 1; yOffset++)  {
    for(int xOffset = -1; xOffset <= 1; xOffset++) {

      // Check the next position that orbit will take is  inside board bounds
      if(isLegal(current.getPosition(),yOffset,xOffset)) {
        Coordinate currentPos = current.getPosition();

        // Get the next square by adding the offsets of x and y to the position
        Square& orbit = grid[currentPos.y + yOffset][currentPos.x + xOffset];
        if(checkNext(orbit,yOffset,xOffset,flip))
          madeFlank = true;
      }
    }
  }
  return madeFlank;
}

/// Checks a line of pieces to see if it ends with a piece that belong to the
/// Current player, if it does it removes the line of pieces and exchanges them
/// with pieces owned by the current player.
bool Reversi::checkNext(Square &current,int yOffset,int xOffset,bool flip) const {
  // Make sure the current piece is owned by currentPlayer
  Coordinate currentPos = current.getPosition();

  if(current.hasPieceOwnedBy(getOpposition()) &&
  isLegal(currentPos,yOffset, xOffset)) {
    Square& next = grid[currentPos.y + yOffset][currentPos.x + xOffset];

    // If the next square in line is owned by the current player or the piece
    // at the end of a line of opponent pieces is owned by current player
    // flip pieces.
    if(next.hasPieceOwnedBy(currentPlayer) ||
    checkNext(next,yOffset,xOffset,flip)
      ) {
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

// Checks if the next square is inside the bounds of the board.
bool Reversi::isLegal(const Coordinate current,int yOffset,int xOffset) const {
  return(
    (current.x + xOffset < columns)&&
    (yOffset != 0 || xOffset != 0)&&
    (current.y + yOffset < rows)&&
    (current.x + xOffset >= 0) &&
    (current.y + yOffset >= 0)
  );
}

// Determines if the game has been won or not.
int Reversi::isOver() {
  char c;
  int check=1;
  int check2;
  int pCurPieces=players[currentPlayer]->getAmountOfPieces();
  int pOppPieces=players[getOpposition()]->getAmountOfPieces();
  //Checks of the board is full.
  if(pCurPieces+pOppPieces == 64) {
    //if the board is full sets player with least pieces to current player.
    if(pCurPieces>pOppPieces)
      currentPlayer=getOpposition();
    return 1;
  }
  for(int x = 0; x<rows; x++) {
    for(int y=0; y<columns; y++) {
      if(!grid[y][x].hasPiece()) {
        if(flanks(grid[y][x],false))
          check=0;
      }
    }
  }
  //If the current player cannot make a move switches to other player.
  if(check=0) currentPlayer=getOpposition();
}

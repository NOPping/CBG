/// Checkers Game.
/// @author Ian Duffy

#include "Checkers.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

Checkers::Checkers():Game(2, 8, 8) {
  // Setup the players.
  const int amountOfPieceTypes = 2;
  const int maxAmountOfPlayerPieces = 12;

  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);

  player1PieceTypes[0] = FRED "○";
  player1PieceTypes[1] = FRED "◎";
  player2PieceTypes[0] = FWHITE "○";
  player2PieceTypes[1] = FWHITE "◎";

  players[0] = new Player(amountOfPieceTypes,player1PieceTypes,
                          maxAmountOfPlayerPieces);

  players[1] = new Player(amountOfPieceTypes,player2PieceTypes,
                          maxAmountOfPlayerPieces);

  // Setup the colors for the squares.
  string start[] = {BWHITE " ",BBLACK " "};
  string end = " " RESET;

  int identifier = 0;

  for(int y=0; y<rows; y++) {
    for(int x=0; x<columns; x++) {
      // Setup the square
      grid[y][x] = Square(identifier,start[identifier],end,amountOfPlayers,
                          Coordinate(x,y));

      // Check if its a black square
      if(identifier == 1) {
        // Add a black piece if its a black square and on the first 3 rows
        if(y<3 && players[0]->hasRoomForPiece()) {
          grid[y][x].addPiece(0, players[0]->addPiece());
        }
        // Add a white piece if its a black square and on the last 3 rows
        else if(y>4 && players[1]->hasRoomForPiece()) {
          grid[y][x].addPiece(1, players[1]->addPiece());
        }
      }

      // Switch identifier
      identifier = (identifier+1)%2;
    }
    // Switch identifier
    identifier = (identifier+1)%2;
  }
}

/// Prints out the board and all the players pieces.
void Checkers::drawScreen() const {
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
int Checkers::getPoint(const string message, const int range) const {
  int point=0;
  while(true) {
    cout << message;
    cin >> point;

    cin.clear();
    cin.ignore(1000,'\n');

    // Check that input is a numeric value.
    if(cin.fail()) {
      drawScreen();
      cout << "\nYou entered a non numeric value, try again\n";
      continue;
    }

    // Check that input is within our grid range.
    if(point < 0 || point >= range) {
      drawScreen();
      cout << "\nPoint out of range, try again\n";
      continue;
    }

    return point;
  }
}

/// Calls getPoint twice to get a source square and destination square
/// Validates the move and passes the source square and destination square
/// onto executeMove().
bool Checkers::getMove() {
  Coordinate srcCoordinate, destCoordinate, jumpCoordinate;
  Square *srcSquare, *destSquare;
  int x,y;

  // Get input for the source square.
  while(true) {
    x = getPoint("Type the X point of the piece you would like to move:\n",
                 rows);
    y = getPoint("Type the Y point of the piece you would like to move:\n",
                 columns);

    // Setup a coordinate for the given X and Y.
    srcCoordinate = Coordinate(x,y);

    // Setup a pointer to the square at the given coordinate.
    srcSquare = &grid[srcCoordinate.y][srcCoordinate.x];

    // Check that the square has a piece.
    if(!srcSquare->hasPiece()) {
      drawScreen();
      cout << "\nThe selected square doesn't contain a piece, try again\n";
      continue;
    }

    // Check that the piece in the square is currentPlayers.
    if(!srcSquare->hasPieceOwnedBy(currentPlayer)) {
      drawScreen();
      cout << "\nThe selected square doesn't contain a piece owned by you,"
      << "try again\n";
      continue;
    }

    break;
  }

  // Get input for the destination square.
  while(true) {
    x = getPoint("Type the X point of the square you would like to move too:\n",
                 rows);
    y = getPoint("Type the Y point of the square you would like to move too:\n",
                 columns);

    // Setup a coordinate for the given X and Y.
    destCoordinate = Coordinate(x,y);

    // Setup a pointer to the square at the given coordinate.
    destSquare = &grid[destCoordinate.y][destCoordinate.x];

    // Check that the destination square is not white.
    if(destSquare->getIdentifier() == 0) {
      drawScreen();
      cout << "\nThe selected square is invalid, try again\n";
      continue;
    }

    // Check that the destination square is not occupied.
    if(destSquare->hasPiece()) {
      drawScreen();
      cout << "\nThe selected square is occupied, try again\n";
      continue;
    }

    break;
  }

  int isValid = validMove(srcCoordinate,destCoordinate);

  if(isValid == 1) {
    return executeMove(*srcSquare,*destSquare);
  } else if(isValid == 2) {
    x = (srcCoordinate.x+destCoordinate.x)/2;
    y = (srcCoordinate.y+destCoordinate.y)/2;
    jumpCoordinate = Coordinate(x,y);
    Square* toJump = &grid[jumpCoordinate.y][jumpCoordinate.x];
    return executeMove(*srcSquare,*destSquare,*toJump);
  }

  // All other cases.
  return false;
}


/// Validates moves.
int Checkers::validMove(Coordinate srcCoordinate, Coordinate destCoordinate)
const {

  // Bound checks.
  if(srcCoordinate.x >= rows || srcCoordinate.x < 0)
    return 0;
  if(srcCoordinate.y >= columns || srcCoordinate.y < 0)
    return 0;
  if(destCoordinate.x >= rows || destCoordinate.x < 0)
    return 0;
  if(destCoordinate.y >= columns || destCoordinate.y < 0)
    return 0;

  Square *srcSquare = &grid[srcCoordinate.y][srcCoordinate.x];
  Square *destSquare = &grid[destCoordinate.y][destCoordinate.x];

  // Does source square have a piece
  if(srcSquare->hasPieceOwnedBy(currentPlayer) == 0)
    return 0;

  // Is destination occupied?
  if(destSquare->hasPiece() > 0)
    return 0;

  int xValidator = abs(srcCoordinate.x-destCoordinate.x);
  int yValidator = destCoordinate.y-srcCoordinate.y;
  bool isKing = (srcSquare->getPiece(currentPlayer).getType() == 1);

  // Check for standard move.
  if(xValidator==1) {
    // Check if its a southwards move.
    if((currentPlayer == 0 || isKing) && (yValidator == 1)) {
      return 1;
    }

    // Check if its a northwards move.
    else if((currentPlayer == 1 || isKing) && (yValidator == -1)) {
      return 1;
    }
  }

  // Check for a jump.
  else if(xValidator==2) {
    int x = (srcCoordinate.x+destCoordinate.x)/2;
    int y = (srcCoordinate.y+destCoordinate.y)/2;
    Coordinate jumpCoordinate = Coordinate(x,y);
    Square* toJump = &grid[jumpCoordinate.y][jumpCoordinate.x];

    // Check if its a southwards jump.
    if(toJump->hasPiece() && toJump->hasPieceOwnedBy(getOpposition())) {

      if((currentPlayer == 0 || isKing) && (yValidator == 2)) {
        return 2;
      }

      // Check if its a northwards jump.
      else if((currentPlayer == 1 || isKing) && (yValidator == -2)) {
        return 2;
      }
    }
  }

  return 0;
}

/// Returns the opposition.
int Checkers::getOpposition() const {
  return (currentPlayer+1)%amountOfPlayers;
}

/// Checks if either of the players no longer have pieces.
int Checkers::isOver() const {
  if(players[currentPlayer]->getAmountOfPieces() != 0) {
    // If current player has zero pieces return win.
    return 0;
  } else {
    int isValid = 0;
    for(int y=0; y<columns; y++) {
      for(int x=0; x<rows; x++) {
        if(grid[y][x].hasPieceOwnedBy(currentPlayer)) {

          // Can move up and right
          isValid = validMove(Coordinate(x,y),Coordinate(x+1,y+1));
          if(isValid == 1) {
            return 1;
          }

          // Can move up and left
          isValid = validMove(Coordinate(x,y),Coordinate(x-1,y+1));
          if(isValid == 1) {
            return 1;
          }

          // Can move down and right
          isValid = validMove(Coordinate(x,y),Coordinate(x+1,y-1));
          if(isValid == 1) {
            return 1;
          }

          // Can move down and left
          isValid = validMove(Coordinate(x,y),Coordinate(x-1,y+1));
          if(isValid == 1) {
            return 1;
          }

          // Can jump up right
          isValid = validMove(Coordinate(x,y),Coordinate(x-2,y+2));
          if(isValid == 1 || isValid == 2) {
            return 1;
          }

          // Can jump up left
          isValid = validMove(Coordinate(x,y),Coordinate(x+2,y+2));
          if(isValid == 1 || isValid == 2) {
            return 1;
          }

          // Can jump down right
          isValid = validMove(Coordinate(x,y),Coordinate(x+2,y+2));
          if(isValid == 1 || isValid == 2) {
            return 1;
          }

          // Can jump down left
          isValid = validMove(Coordinate(x,y),Coordinate(x-2,y-2));
          if(isValid == 1 || isValid == 2) {
            return 1;
          }
        }
      }
    }
  }

  // Return Draw
  return 2;
}

/// Moves the piece on source square to destination square.
bool Checkers::executeMove(Square& srcSquare,Square& destSquare) {
  // Move the piece from srcSquare to destSquare.
  destSquare.addPiece(currentPlayer,srcSquare.getPiece(currentPlayer));
  srcSquare.removePiece(currentPlayer);

  // Check if a piece needs to be kinged.
  if(currentPlayer==0 && destSquare.getPosition().y == columns-1) {
    destSquare.getPiece(currentPlayer).setType(1);
  } else if(currentPlayer==1 && destSquare.getPosition().y == 0) {
    destSquare.getPiece(currentPlayer).setType(1);
  }

  // Switch Player.
  currentPlayer = getOpposition();
  return true;
}

/// Moves the piece on source square to destination square and deletes
/// the piece on the to jump square.
bool Checkers::executeMove(Square& srcSquare,Square& destSquare,
                           Square& toJump) {
  toJump.removePiece(getOpposition());
  players[getOpposition()]->removePiece();
  return executeMove(srcSquare,destSquare);
}

#include "Checkers.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

Checkers::Checkers():Game(2, 8, 8) {

  int amountOfPieceTypes = 2;
  int maxAmountOfPlayerPieces = 1;
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = "\033[31m○";
  player1PieceTypes[1] = "\033[31m◎";
  player2PieceTypes[0] = "\033[37m○";
  player2PieceTypes[1] = "\033[37m◎";

  players[0] = new Player(amountOfPieceTypes,player1PieceTypes,
                          maxAmountOfPlayerPieces);

  players[1] = new Player(amountOfPieceTypes,player2PieceTypes,
                          maxAmountOfPlayerPieces);

  string start[] = {"\033[47m ","\033[40m "};
  string end = " \033[0m";

  int identifier = 0;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      // Setup the square
      grid[i][j] = Square(identifier,start[identifier],end,amountOfPlayers,
                          Coordinate(j,i));

      // Check if its a black square
      if(identifier == 1) {
        // Add a black piece if its a black square and on the first 3 rows
        if(i<3) {
          grid[i][j].addPiece(0,players[0]->addPiece());
        }
        // Add a white piece if its a black square and on the last 3 rows
        else if(i>4) {
          grid[i][j].addPiece(1,players[1]->addPiece());
        }
      }

      // Switch identifier
      identifier = (identifier+1)%2;
    }
    // Switch identifier
    identifier = (identifier+1)%2;
  }
}

Checkers::~Checkers() {
}

void Checkers::drawScreen() {
  clearScreen();
  cout << "Player " << (currentPlayer+1) << " it is your go\n\n  ";
  for(int i=0; i<rows; i++) cout << " " << i << " ";
  cout << "\n";
  for(int i=0; i<rows; i++) {
    cout << i << " ";
    for(int j=0; j<columns; j++) {
      cout << grid[i][j].getStart();
      cout << grid[i][j];
      cout << grid[i][j].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

int Checkers::getPoint(string message, int range) {
  int point=0;
  while(true) {
    cout << message;
    cin >> point;

    // Check that input is a numeric value
    if(cin.fail()) {
      cout << "\nYou entered a non numeric value, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    // Check that input is within our grid range
    if(point < 0 || point > range) {
      cout << "\nPoint out of range, try again\n";
      continue;
    }

    return point;
  }
}

bool Checkers::getMove() {
  Coordinate sourceCoordinate, destinationCoordinate, jumpCoordinate;
  Square *sourceSquare, *destinationSquare;
  int x,y;

  while(true) {
    x = getPoint("Type the X point of the piece you would like to move:\n",
                 rows);
    y = getPoint("Type the Y point of the piece you would like to move:\n",
                 columns);

    // Setup a coordinate for the given X and Y
    sourceCoordinate = Coordinate(x,y);

    // Setup a pointer to the square at the given coordinate
    sourceSquare = &grid[sourceCoordinate.y][sourceCoordinate.x];

    // Check that the square has a piece
    if(!sourceSquare->hasPiece()) {
      cout << "\nThe selected square doesn't contain a piece, try again\n";
      continue;
    }

    // Check that the piece in the square is currentPlayers
    if(!sourceSquare->hasPieceOwnedBy(currentPlayer)) {
      cout << "\nThe selected square doesn't contain a piece owned by you,"
      << "try again\n";
      continue;
    }

    break;
  }

  while(true) {
    x = getPoint("Type the X point of the square you would like to move too:\n",
                 rows);
    y = getPoint("Type the Y point of the square you would like to move too:\n",
                 columns);

    // Setup a coordinate for the given X and Y
    destinationCoordinate = Coordinate(x,y);

    // Setup a pointer to the square at the given coordinate
    destinationSquare = &grid[destinationCoordinate.y][destinationCoordinate.x];

    // Check that the destination square is not white
    if(destinationSquare->getIdentifier() == 0) {
      cout << "\nThe selected square is invalid, try again\n";
      continue;
    }

    // Check that the destination square is not occupied
    if(destinationSquare->hasPiece()) {
      cout << "\nThe selected square is occupied, try again\n";
      continue;
    }

    break;
  }

  int xvalidator = abs(sourceCoordinate.x-destinationCoordinate.x);
  int yvalidator = destinationCoordinate.y-sourceCoordinate.y;
  bool isKing = (sourceSquare->getPiece(currentPlayer)->getType() == 1);

  // Check for standard move
  if(xvalidator==1) {
    // Check if its a southwards move
    if((currentPlayer == 0 || isKing) && (yvalidator == 1)) {
      return executeMove(sourceSquare,destinationSquare);
    }

    // Check if its a northwards move
    else if((currentPlayer == 1 || isKing) && (yvalidator == -1)) {
      return executeMove(sourceSquare,destinationSquare);
    }
  }

  // Check for a jump
  else if(xvalidator==2) {
    x = (sourceCoordinate.x+destinationCoordinate.x)/2;
    y = (sourceCoordinate.y+destinationCoordinate.y)/2;
    jumpCoordinate = Coordinate(x,y);
    Square* toJump = &grid[jumpCoordinate.y][jumpCoordinate.x];

    // Check if its a southwards jump
    if(toJump->hasPiece() && toJump->hasPieceOwnedBy(getOpposition())) {

      if((currentPlayer == 0 || isKing) && (yvalidator == 2)) {
        return executeMove(sourceSquare,destinationSquare,toJump);
      }

      // Check if its a northwards jump
      else if((currentPlayer == 1 || isKing) && (yvalidator == -2)) {
        return executeMove(sourceSquare,destinationSquare,toJump);
      }

    }
  }

  // All other cases
  return false;
}

int Checkers::getOpposition() {
  return (currentPlayer+1)%amountOfPlayers;
}

int Checkers::isOver() {
  return players[currentPlayer]->getAmountOfPieces() == 0 ? 1 : 0;
}

bool Checkers::executeMove(Square* sourceSquare,Square* destinationSquare) {
  // Move the piece from sourceSquare to destinationSquare
  destinationSquare->addPiece(currentPlayer,
                              sourceSquare->getPiece(currentPlayer));
  sourceSquare->removePiece(currentPlayer);

  // Check if a piece needs to be kinged.
  if(currentPlayer==0 && destinationSquare->getPosition().y == columns-1) {
    destinationSquare->getPiece(currentPlayer)->setType(1);
  } else if(currentPlayer==1 && destinationSquare->getPosition().y == 0) {
    destinationSquare->getPiece(currentPlayer)->setType(1);
  }

  // Switch Player
  currentPlayer = getOpposition();
  return true;
}

bool Checkers::executeMove(Square* sourceSquare,Square* destinationSquare,
                           Square* toJump) {
  toJump->removePiece(getOpposition());
  players[getOpposition()]->removePiece();
  return executeMove(sourceSquare,destinationSquare);
}

#include "Checkers.h"

using namespace std;

Checkers::Checkers() {
  this->rows = 8;
  this->columns = 8;
  this->amountOfPlayers = 2;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];
  this->grid = new Square*[rows];
  for(int i=0; i<rows; i++) {
    this->grid[i] = new Square[columns];
  }

  int amountOfPieceTypes = 2;
  int maxAmountOfPlayerPieces = 12;
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = "\033[31m○";
  player1PieceTypes[1] = "\033[31m◎";
  player2PieceTypes[0] = "\033[37m○";
  player2PieceTypes[1] = "\033[37m◎";

  this->players[0] = Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = Player(amountOfPieceTypes,
                            player2PieceTypes,maxAmountOfPlayerPieces);

  string squareStart[] = {"\033[47m ",
                          "\033[40m "
                         };
  string squareEnd = " \033[0m";

  int squareIdentifier = 0;


  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      // Color the square
      this->grid[i][j] = Square(squareIdentifier,
                                squareStart[squareIdentifier],
                                squareEnd,
                                amountOfPlayers,
                                Coordinate(j,i));

      // Check if its a black square
      if(squareIdentifier == 1) {
        if(i<3) {
          this->grid[i][j].addPiece(0,
                                    this->players[0].addPiece());
        } else if(i>4) {
          this->grid[i][j].addPiece(1,
                                    this->players[1].addPiece());
        }
      }

      // Switch identifier
      squareIdentifier = (squareIdentifier + 1)%2;
    }
    // Switch identifier
    squareIdentifier = (squareIdentifier + 1)%2;
  }

}

void Checkers::drawScreen() {
  this->clearScreen();
  cout << "Player " << (this->currentPlayer+1) << " it is your go\n\n";
  cout << "  ";
  for(int i=0; i<rows; i++) cout << " " << i << " ";
  cout << "\n";
  for(int i=0; i<rows; i++) {
    cout << i << " ";
    for(int j=0; j<columns; j++) {
      cout << grid[i][j].putSquare();
    }
    cout << "\n";
  }
  cout << "\n";
}

bool Checkers::getMove() {
  Coordinate sourceCoordinate, destinationCoordinate;
  Square *sourceSquare, *destinationSquare;
  int x,y;

  while(true) {
    while(true) {
      cout << "Type the X point of the piece you would like to move: \n";
      cin >> x;

      // Check that input is a numeric value
      if(cin.fail()) {
        cout << "\nYou entered a non numeric value, try again\n";
        cin.clear();
        cin.ignore(1000,'\n');
        continue;
      }

      // Check that input is within our grid range
      if(x < 0 || x > this->rows) {
        cout << "\nPoint out of range, try again\n";
        continue;
      }

      break;
    }

    while(true) {
      cout << "Type the Y point of the piece you would like to move: \n";
      cin >> y;

      // Check that input is a numeric value
      if(cin.fail()) {
        cout << "\nYou entered a non numeric value, try again\n";
        cin.clear();
        cin.ignore(1000,'\n');
        continue;
      }

      // Check that input is within our grid range
      if(y < 0 || y > this->columns) {
        cout << "\nPoint out of range, try again\n";
        continue;
      }

      break;
    }

    // Setup a coordinate for the given X and Y
    sourceCoordinate = Coordinate(x,y);

    // Setup a pointer to the square at the given coordinate
    sourceSquare = &grid[sourceCoordinate.y][sourceCoordinate.x];

    // Check that the square has a piece
    if(!sourceSquare->hasPiece()) {
      cout << "The selected square doesn't contain a piece, try again\n";
      continue;
    }

    // Check that the piece in the square is currentPlayers
    if(!sourceSquare->hasPieceOwnedBy(currentPlayer)) {
      cout << "The selected square doesn't contain a piece owned by you, try again\n";
      continue;
    }

    break;
  }

  while(true) {
    while(true) {
      cout << "Type the X point of the square you would like to move too: \n";
      cin >> x;

      // Check that input is a numeric value
      if(cin.fail()) {
        cout << "\nYou entered a non numeric value, try again\n";
        cin.clear();
        cin.ignore(1000,'\n');
        continue;
      }

      // Check that input is within our grid range
      if(x < 0 || x > this->rows) {
        cout << "\nPoint out of range, try again\n";
        continue;
      }

      break;
    }

    while(true) {
      cout << "Type the Y point of the square you would like to move too:  \n";
      cin >> y;

      // Check that input is a numeric value
      if(cin.fail()) {
        cout << "\nYou entered a non numeric value, try again\n";
        cin.clear();
        cin.ignore(1000,'\n');
        continue;
      }

      // Check that input is within our grid range
      if(y < 0 || y > this->columns) {
        cout << "\nPoint out of range, try again\n";
        continue;
      }

      break;
    }

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

  if(abs(sourceCoordinate.x-destinationCoordinate.x)==1) {
    if((currentPlayer == 0
        || sourceSquare->getPiece(currentPlayer)->getType() == 1)
        && ((destinationCoordinate.y-sourceCoordinate.y) == 1)
      ) {
      return this->executeMove(sourceSquare,destinationSquare);
    } else if((currentPlayer == 1
               || sourceSquare->getPiece(currentPlayer)->getType() == 1)
              && ((destinationCoordinate.y-sourceCoordinate.y) == -1)
             ) {
      return this->executeMove(sourceSquare,destinationSquare);
    }
  }

  else if(abs(sourceCoordinate.x-destinationCoordinate.x)==2) {
    Square* toJump = &grid[(sourceCoordinate.y+destinationCoordinate.y)/2][(sourceCoordinate.x+destinationCoordinate.x)/2];
    if(toJump->hasPiece() && toJump->hasPieceOwnedBy((currentPlayer+1)%2)) {
      if((currentPlayer == 0
          || sourceSquare->getPiece(currentPlayer)->getType() == 1)
          && ((destinationCoordinate.y-sourceCoordinate.y) == 2)
        ) {
        return this->executeMove(sourceSquare,destinationSquare,toJump);
      } else if((this->currentPlayer == 1
                 || sourceSquare->getPiece(currentPlayer)->getType() == 1)
                && ((destinationCoordinate.y-sourceCoordinate.y) == -2)
               ) {
        return this->executeMove(sourceSquare,destinationSquare,toJump);
      }
    }
  }

  // All other cases
  return false;
}

bool Checkers::executeMove(Square* sourceSquare,Square* destinationSquare, Square* toJump) {
  toJump->removePiece((currentPlayer+1)%2);
  players[(currentPlayer+1)%2].removePiece();
  return this->executeMove(sourceSquare,destinationSquare);
}

bool Checkers::executeMove(Square* sourceSquare,Square* destinationSquare) {
  // Move the piece from sourceSquare to destinationSquare
  destinationSquare->addPiece(this->currentPlayer,sourceSquare->getPiece(currentPlayer));
  sourceSquare->removePiece(this->currentPlayer);

  // Check if a piece needs to be kinged.
  if(this->currentPlayer==0 && destinationSquare->getPosition().y == this->columns-1) {
    destinationSquare->getPiece(currentPlayer)->setType(1);
  } else if(this->currentPlayer==1 && destinationSquare->getPosition().y == 0) {
    destinationSquare->getPiece(currentPlayer)->setType(1);
  }

  // Check if the game is over
  if(this->players[(currentPlayer+1)%2].getAmountOfPieces() == 0) {
    cout << "Changing state";
    this->state = 1;
    return true;
  }

  // Switch Player
  this->currentPlayer = (this->currentPlayer+1) % this->amountOfPlayers;
  return true;
}
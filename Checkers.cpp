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
  player1PieceTypes[0] = "\033[0;31;40m ○ \033[0m";
  player1PieceTypes[1] = "\033[0;31;40m ◎ \033[0m";
  player2PieceTypes[0] = "\033[0;37;40m ○ \033[0m";
  player2PieceTypes[1] = "\033[0;37;40m ◎ \033[0m";

  this->players[0] = Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = Player(amountOfPieceTypes,
                            player2PieceTypes,maxAmountOfPlayerPieces);

  string squareRepresentations[] = {"\033[0;37;47m   \033[0m",
                                    "\033[0;37;40m   \033[0m"
                                   };

  int squareIdentifier = 0;


  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      // Color the square
      this->grid[i][j] = Square(squareIdentifier,
                                squareRepresentations[squareIdentifier],
                                amountOfPlayers,
                                Coordinate(i,j));

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

void Game::drawScreen() {
  cout << "\033[2J\033[;H";
  cout << "Player " << (this->currentPlayer+1) << " it is your go\n\n";
  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      cout << grid[i][j].putSquare();
    }
    cout << "\n";
  }
  cout << "\n";
}

bool Game::getMove() {
  int x,y;
  do {
    cout << "Type in the X and Y coordinate of the piece you would like to "
    << "move:\n";
    cin >> x;
    cin >> y;
    if(x < 0 || x > this->rows || y < 0 || y > this->columns) {
      cout << "Invalid source coordinate, try again\n";
    }
  } while(x < 0 || x > this->rows || y < 0 || y > this->columns);

  Coordinate sourceCoordinate = Coordinate(x,y);

  do {
    cout << "Type in the X and Y coordinate of the square you would like to "
    << "move too:\n";
    cin >> x;
    cin >> y;
    if(x < 0 || x > this->rows || y < 0 || y > this->columns) {
      cout << "Invalid destination coordinate, try again\n";
    }
  } while(x < 0 || x > this->rows || y < 0 || y > this->columns);

  Coordinate destinationCoordinate = Coordinate(x,y);

  Square* sourceSquare = &grid[sourceCoordinate.y][sourceCoordinate.x];
  Square* destinationSquare = &grid[destinationCoordinate.y][destinationCoordinate.x];

  if(sourceSquare->getIdentifier() == 0) {
    cout << "Source square is white\n";
    return false;
  }

  if(destinationSquare->getIdentifier() == 0) {
    cout << "Destination square is white\n";
    return false;
  }

  if(!sourceSquare->hasPiece()) {
    cout << "Source square doesn't contain any pieces\n";
    return false;
  }

  if(destinationSquare->hasPiece()) {
    cout << "Destination square is occupied\n";
    return false;
  }

  if(!sourceSquare->hasPieceOwnedBy(currentPlayer)) {
    cout << "The select square doesn't contain a piece owned by you\n";
    return false;
  }

  if(abs(sourceCoordinate.x-destinationCoordinate.x)==1) {
    if((currentPlayer == 0
        || sourceSquare->getPiece(currentPlayer)->getType() == 1)
        && ((destinationCoordinate.y-sourceCoordinate.y) == 1)
      ) {
      cout << "Valid move for player1 piece\n";
      return this->executeMove(sourceSquare,destinationSquare);
    } else if((currentPlayer == 1
               || sourceSquare->getPiece(currentPlayer)->getType() == 1)
              && ((destinationCoordinate.y-sourceCoordinate.y) == -1)
             ) {
      cout << "Valid move for player2 piece\n";
      return this->executeMove(sourceSquare,destinationSquare);
    }
  }

  if(abs(sourceCoordinate.x-destinationCoordinate.x)==2) {
    Square* toJump = &grid[(sourceCoordinate.y+destinationCoordinate.y)/2][(sourceCoordinate.x+destinationCoordinate.x)/2];
    if(toJump->hasPiece() && toJump->hasPieceOwnedBy((currentPlayer+1)%2)) {
      if((currentPlayer == 0
          || sourceSquare->getPiece(currentPlayer)->getType() == 1)
          && ((destinationCoordinate.y-sourceCoordinate.y) == 2)
        ) {
        cout << "Valid jump";
        toJump->removePiece((currentPlayer+1)%2);
        return this->executeMove(sourceSquare,destinationSquare);
      } else if((this->currentPlayer == 1
                 || sourceSquare->getPiece(currentPlayer)->getType() == 1)
                && ((destinationCoordinate.y-sourceCoordinate.y) == -2)
               ) {
        cout << "Valid jump";
        toJump->removePiece((currentPlayer+1)%2);
        return this->executeMove(sourceSquare,destinationSquare);
      }
    }
  }

  return false;
}

bool Game::executeMove(Square* sourceSquare,Square* destinationSquare) {
  cout << "Updating the destination square";
  destinationSquare->addPiece(this->currentPlayer,sourceSquare->getPiece(currentPlayer));
  cout << "Removing the piece from the source square";
  sourceSquare->removePiece(this->currentPlayer);
  if(this->currentPlayer==0 && destinationSquare->getPosition().y == this->columns -1) {
    destinationSquare->getPiece(currentPlayer)->setType(1);
  }
  if(this->currentPlayer==1 && destinationSquare->getPosition().y == 0) {
    destinationSquare->getPiece(currentPlayer)->setType(1);
  }
  if(this->players[(currentPlayer+1)%2].getAmountOfPieces() == 0) {
    this->state = false;
    return false;
  }
  this->currentPlayer = (this->currentPlayer+1) % this->amountOfPlayers;
  return true;
}

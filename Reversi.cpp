#include "Reversi.h"
using std::cout;
using std::cin;
using std::string;
using std::vector;
Reversi::Reversi():Game(2, 8, 8)  {
  const int amountOfPieceTypes= 1;
  const int maxPlayerPieces = 64;
  vector<string> player1PieceTypes(amountOfPieceTypes);
  vector<string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = "\033[37m◎";
  player2PieceTypes[0] = "\033[30m◎";
  players[0] =new Player(amountOfPieceTypes,player1PieceTypes,maxPlayerPieces);
  players[1] =new Player(amountOfPieceTypes,player2PieceTypes,maxPlayerPieces);
  string start[] = {"\033[48;5;2m ","\033[48;5;10m "};
  string end = " \033[0m";

  int identifier = 0;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      grid[i][j] = Square(identifier,start[identifier],end,amountOfPlayers,
                          Coordinate(j,i));
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
//flushes the screen and prints  out the board
void Reversi::drawScreen() const {
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
//gets an int from the user and ensures it within  the range of the board
int Reversi::getPoint(const string message, int range) const {
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
    if(point < 0 || point >= range) {
      cout << "\nPoint out of range, try again\n";
      continue;
    }

    return point;
  }
}
//prompts a player to enter an x and y coordinate using get point
//passes the coordinate on to execute move
bool Reversi::getMove() {
  Coordinate destinationCoordinate;
  Square  *destinationSquare;
  int x,y;
  bool validInput=false;
  while(!validInput) {
    x = getPoint("Type the X point of the square you would like to move too:\n",rows);
    y = getPoint("Type the Y point of the square you would like to move too:\n",columns);
    destinationCoordinate = Coordinate(x,y);

    if(grid[y][x].hasPiece()) {
      cout << "\nThe selected square is occupied, try again\n";
      continue;
    } else {
      destinationSquare = &grid[y][x];
      validInput=executeMove(*destinationSquare);
    }
    if(validInput)currentPlayer = (currentPlayer+1)%2;

  }
  return true;
}
// call the flanks method to ensure the destination coordinate  flanks an opponents piece
//if ti does it adds the piece to the destination square
bool Reversi::executeMove(Square& destinationSquare)const {
  if(flanks(destinationSquare,true)) {
    destinationSquare.addPiece(currentPlayer,players[currentPlayer]->addPiece());
    //currentPlayer=((currentPlayer+1)%2);
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
//changes the players
int Reversi::getOpposition() const {
  return (currentPlayer+1)%amountOfPlayers;
}

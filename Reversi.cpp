#include "Reversi.h"
using std::cout;
using std::cin;
using std::string;
using std::vector;
Reversi::Reversi():Game(2, 8, 8)  {
  int amountOfPieceTypes= 1;
  int maxAmountOfPlayerPieces = 64;
  vector<string> player1PieceTypes(amountOfPieceTypes);
  vector<string> player2PieceTypes(amountOfPieceTypes);
  player1PieceTypes[0] = "\033[37m◎";
  player2PieceTypes[0] = "\033[30m◎";
  this->players[0] =new Player(amountOfPieceTypes,player1PieceTypes,maxAmountOfPlayerPieces);
  this->players[1] =new Player(amountOfPieceTypes,player2PieceTypes,maxAmountOfPlayerPieces);
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
  grid[3][3].addPiece(0,players[0]->addPiece());
  grid[4][4].addPiece(0,players[0]->addPiece());
  grid[3][4].addPiece(1,players[1]->addPiece());
  grid[4][3].addPiece(1,players[1]->addPiece());
}

Reversi::~Reversi() {
  for(int i=0; i<rows; i++) {
    delete [] grid[i];
  }
  delete [] grid;
  delete [] players;
}

void Reversi::drawScreen() {
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

int Reversi::getPoint(string message, int range) {
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
bool Reversi::isLegal(Coordinate* current,int iOffset,int jOffset) {
  //Ensure that the next square lies inside the bounds of the board
  return((current->x + jOffset < columns)&&(current->x + jOffset >= 0))
        &&(current->y + iOffset < rows)&&(current->y + iOffset >= 0)
        &&(iOffset != 0 || jOffset != 0);
}
bool Reversi::flanks(Coordinate* current) {
  bool count=false;
  bool count2=false;
  Square* orbit;
  for(int rowOffset = -1; rowOffset <= 1; rowOffset++)  {
    for(int columnOffset = -1; columnOffset <= 1; columnOffset++) {
      if(isLegal(current,rowOffset,columnOffset)) {
        orbit = &grid[current->y + rowOffset][current->x + columnOffset];
        if(orbit->hasPieceOwnedBy((currentPlayer+1)%2)&&orbit!=0) {
          Coordinate beside=orbit->getPosition();
          count= 	checkLine(beside,rowOffset,columnOffset);
        }
      }
      if(count)count2=true;
    }
  }
  return count2;
}
bool Reversi::checkLine(Coordinate current,int rowOffset,int columnOffset) {
  bool test=false;
  int xCor=current.x;
  int yCor=current.y;
  int countPieces=0;
  while (isLegal(&current,rowOffset,columnOffset) &&  grid[yCor][xCor].hasPiece() && (grid[yCor][xCor].hasPieceOwnedBy((currentPlayer+1)%2))) {
    countPieces++;
    xCor+=columnOffset;
    yCor+=rowOffset;
    cout<< "Just entered while loop in check line xcor="<<xCor<<" ycor="<<yCor<<"\n";
  }
  if(countPieces!=0&& isLegal(&current,rowOffset,columnOffset) &&(grid[yCor][xCor].hasPieceOwnedBy((currentPlayer)))) {
    test=true;
    for(int i =0; i<countPieces; i++) {
      xCor-=columnOffset;
      yCor-=rowOffset;
      Square* next = &grid[yCor][xCor];
      if (next->hasPiece())next->removePiece((currentPlayer+1)%2);
      next->addPiece(currentPlayer,players[currentPlayer]->addPiece());
    }
  }
  return test;
}

bool Reversi::getMove() {
  Coordinate destinationCoordinate;
  Square  *destinationSquare;
  int x,y;
  bool test=true;
  while(test) {
    x = getPoint("Type the X point of the square you would like to move too:\n",rows);
    y = getPoint("Type the Y point of the square you would like to move too:\n",columns);
    destinationCoordinate = Coordinate(x,y);
    destinationSquare = &grid[destinationCoordinate.y][destinationCoordinate.x];

    if(destinationSquare->hasPiece()) {
      cout << "\nThe selected square is occupied, try again\n";
      continue;
    }
    if(flanks(&destinationCoordinate)) {
      test=false;
      destinationSquare->addPiece(currentPlayer,players[currentPlayer]->addPiece());
    } else cout<<"\nDoes not flank opponent piece\n";
  }
  currentPlayer = (currentPlayer + 1) % 2;
  return true;
}

int Reversi::isOver() {
  return false;
}
int Reversi::getOpposition() {
  return (currentPlayer+1)%amountOfPlayers;
}
bool Reversi::executeMove(Square* sourceSquare,Square* destinationSquare) {
  // Not implemented yet
  destinationSquare->addPiece(currentPlayer,
                              sourceSquare->getPiece(currentPlayer));
  sourceSquare->removePiece(currentPlayer);

  currentPlayer = getOpposition();
  return true;
}

#include "SnakesAndLadders.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

SnakesAndLadders::SnakesAndLadders() {
  srand(time(NULL));
  this->rows = 10;
  this->columns = 10;
  this->amountOfPlayers = 3;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];
  this->grid = new Square*[rows];
  for(int i=0; i<rows; i++) {
    this->grid[i] = new Square[columns];
  }

  int amountOfPieceTypes = 1;
  int maxAmountOfPlayerPieces = 1;
  vector <string> player1PieceTypes(amountOfPieceTypes);
  vector <string> player2PieceTypes(amountOfPieceTypes);
  vector <string> systemPieceTypes(2);
  player1PieceTypes[0] = "\033[31m◎";
  player2PieceTypes[0] = "\033[34m◎";
  systemPieceTypes[0] = "\033[32mS";
  systemPieceTypes[1] = "\033[33mL";

  this->players[0] = Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = Player(amountOfPieceTypes,
                            player2PieceTypes,maxAmountOfPlayerPieces);

  this->players[2] = Player(amountOfPieceTypes, systemPieceTypes,10);

  string start[] = {"\033[47m","\033[40m"};
  string end = " \033[0m";
  
  int identifier = 0;
  
  int counter = 100;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      // Color the square

      this->grid[i][j] = Square(counter,start[identifier],end,
                                amountOfPlayers,Coordinate(j,i));

      counter += (i % 2 == 0) ? -1 : 1;

      // Switch identifier
      identifier = (identifier + 1)%2;
      //counter++;
    }
    // Switch identifier
    counter -= (i % 2 == 0) ? 9 : 11;
    identifier = (identifier + 1)%2;
  }
  
  grid[9][0].addPiece(0,players[0].addPiece(Coordinate(0,9)));
  grid[9][0].addPiece(1,players[1].addPiece(Coordinate(0,9)));
}

SnakesAndLadders::~SnakesAndLadders() {
  for(int i=0; i<rows; i++) {
    delete [] grid[i];
  }
  delete [] grid;
  delete [] players;
}

void SnakesAndLadders::drawScreen() {
  this->clearScreen();
  cout << "Player " << (this->currentPlayer+1) << " it is your go\n\n";
  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      cout << grid[i][j].getStart();
      printf ("%-4d",grid[i][j].getIdentifier());
      cout << grid[i][j];
      cout << grid[i][j].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

int SnakesAndLadders::rollDice() {
  return (int)rand() % 6 + 1;
}


bool SnakesAndLadders::getMove() {
  cout << "Press enter to roll a dice and make your move\n";
  cin.get();
  int roll = rollDice();
  cout << "You rolled a " << roll << "\n";
  Coordinate current = players[currentPlayer].getPiece(0)->position;
  
  return this->executeMove(current, roll);
  /*
  if(roll == 6) {
    players[currentPlayer].sixes++;
    if(players[currentPlayer].sixes == 3) {
      this->resetPlayer(current);
      players[currentPlayer].canMove = false;
    } else {
      players[currentPlayer].canMove = true;
      this->executeMove(current, roll);
      this->getMove();
    }
  } else if(players[currentPlayer].canMove) {
    players[currentPlayer].sixes = 0;
    this->executeMove(current, roll);
  } else cout << "You can't move til you roll a six\n";
  return true;
}

void SnakesAndLadders::resetPlayer(Coordinate current) {
  Square currentSquare = grid[current.y][current.x];
  grid[0][10].addPiece(currentPlayer, currentSquare.getPiece(currentPlayer));
  currentSquare.removePiece(currentPlayer);
}
*/
}
bool SnakesAndLadders::executeMove(Coordinate current,int roll) {
  Square *currentSquare = &grid[current.y][current.x];
  
  int position = currentSquare->getIdentifier()+roll;
  
  if(position == 100) {
    state = 1;
  } else if(position > 100) {
    position = 100 - (position % 100);
    
    // Check that the position actually changes
    if(position == currentSquare->getIdentifier()) {
      currentPlayer=(currentPlayer+1)%(amountOfPlayers-1);
      return true;
    }
  }
  
  Coordinate destination = squareToCoordinate(position);

  if(grid[destination.y][destination.x].hasPieceOwnedBy(2)) {
    cout << "You landed on a snake/ladder, oh no/oh yes";
    SystemPiece* piece =  (SystemPiece*)grid[destination.y][destination.x].getPiece(0);
    destination = piece->getDestination();
  }
  
  cout << destination.x << " " << destination.y << "\n";
  
  Square *destinationSquare = &grid[destination.y][destination.x];
  currentSquare->getPiece(currentPlayer)->position.x = destination.x;
  currentSquare->getPiece(currentPlayer)->position.y = destination.y;
  
  destinationSquare->addPiece(currentPlayer, currentSquare->getPiece(currentPlayer));
  currentSquare->removePiece(currentPlayer);
  
  if(state != 1) currentPlayer=(currentPlayer+1)%(amountOfPlayers-1);
  
  return true;
}

Coordinate SnakesAndLadders::squareToCoordinate(int position) {
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      if(grid[i][j].getIdentifier()==position) {
        return grid[i][j].getPosition();
      }
    } 
  }
  return Coordinate(0,0);
}
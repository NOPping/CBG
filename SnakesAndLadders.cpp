#include "SnakesAndLadders.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

SnakesAndLadders::SnakesAndLadders() {
  srand(time(NULL));
  this->rows = 10;
  this->columns = 10;
  this->amountOfPlayers = 4;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];
  this->grid = new Square*[rows];
  this->squareRefs = new Square[100];
  
  for(int i=0; i<rows; i++) {
    this->grid[i] = new Square[columns];
  }

  int maxAmountOfPlayerPieces = 1;
  vector <string> player1PieceTypes(1);
  vector <string> player2PieceTypes(1);
  vector <string> system1PieceTypes(2);
  vector <string> system2PieceTypes(2);
  player1PieceTypes[0] = "\033[38;5;160m◎";
  player2PieceTypes[0] = "\033[38;5;27m◎";
  
  system1PieceTypes[0] = "\033[38;5;208mS";
  system1PieceTypes[1] = "\033[38;5;106mL";

  system2PieceTypes[0] = "\033[38;5;226mS";
  system2PieceTypes[1] = "\033[38;5;134mL";

  this->players[0] = Player(1,player1PieceTypes,maxAmountOfPlayerPieces);

  this->players[1] = Player(1,player2PieceTypes,maxAmountOfPlayerPieces);

  this->players[2] = Player(2, system1PieceTypes,16);
  this->players[3] = Player(2, system2PieceTypes,16);

  string start[] = {"\033[48;5;16m","\033[48;5;241m"};
  string end = "\033[0m";

  int identifier = 0;

  int counter = 100;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {
      // Color the square

      grid[i][j] = Square(counter,start[identifier],end,
                                amountOfPlayers,Coordinate(j,i));
      squareRefs[counter-1] = grid[i][j];
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

  Coordinate source;
  Coordinate destination;

  Coordinate snakes[8][2] = {
    {
      squareToCoordinate(20),squareToCoordinate(17)
    },
    {
      squareToCoordinate(33),squareToCoordinate(7)
    },
    {
      squareToCoordinate(44),squareToCoordinate(22)
    },
    {
      squareToCoordinate(52),squareToCoordinate(31)
    },
    {
      squareToCoordinate(63),squareToCoordinate(54)
    },
    {
      squareToCoordinate(85),squareToCoordinate(67)
    },
    {
      squareToCoordinate(94),squareToCoordinate(71)
    },
    {
      squareToCoordinate(99),squareToCoordinate(61)
    }
  };
  
  for(int i=0;i<8;i++) {
    grid[snakes[i][0].y][snakes[i][0].x].addPiece(2,new Piece(&players[2],i,snakes[i][0],snakes[i][1]));
    grid[snakes[i][1].y][snakes[i][1].x].addPiece(3,new Piece(&players[3],i));
  }
  
  Coordinate ladders[8][2] = {
    {
      squareToCoordinate(9),squareToCoordinate(29)
    },
    {
      squareToCoordinate(15),squareToCoordinate(26)
    },
    {
      squareToCoordinate(24),squareToCoordinate(46)
    },
    {
      squareToCoordinate(40),squareToCoordinate(60)
    },
    {
      squareToCoordinate(64),squareToCoordinate(76)
    },
    {
      squareToCoordinate(69),squareToCoordinate(87)
    },
    {
      squareToCoordinate(83),squareToCoordinate(98)
    },
    {
      squareToCoordinate(48),squareToCoordinate(68)
    }
  };
  
  for(int i=0;i<8;i++) {
    grid[ladders[i][0].y][ladders[i][0].x].addPiece(2,new Piece(&players[2],i,ladders[i][0],ladders[i][1],1));
    grid[ladders[i][1].y][ladders[i][1].x].addPiece(3,new Piece(&players[3],i,1));
  }
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
  for(int currentRow=0; currentRow<rows; currentRow++) {
    for(int currentColumn=0; currentColumn<columns; currentColumn++) {
      // Start the Square
      cout << grid[currentRow][currentColumn].getStart();

      // Print square number
      printf ("%-3d",grid[currentRow][currentColumn].getIdentifier());

      // Print player piece if any.
      bool pieceFound = false;
      if(grid[currentRow][currentColumn].hasPiece()) {
        for(int i=0; i<(amountOfPlayers-2); i++) {
          if(grid[currentRow][currentColumn].hasPieceOwnedBy(i)) {
            cout << *grid[currentRow][currentColumn].getPiece(i);
            pieceFound = true;
            break;
          }
        }
      }
      if(!pieceFound) cout << " ";

      cout << " ";

      
      bool snakeLadderFound=false;
      // Print snakes/ladders if the square has some.
      if(grid[currentRow][currentColumn].hasPieceOwnedBy(2)) {
        snakeLadderFound=true;
        Piece* systemPiece = grid[currentRow][currentColumn].getPiece(2);
        cout << systemPiece->owner->getCharacter(systemPiece->getType()) << systemPiece->getIdentifier();
      }

      if(grid[currentRow][currentColumn].hasPieceOwnedBy(3)) {
        snakeLadderFound=true;
        Piece* systemPiece = grid[currentRow][currentColumn].getPiece(3);
        cout << systemPiece->owner->getCharacter(systemPiece->getType()) << systemPiece->getIdentifier();
      }      

      if(!snakeLadderFound) cout << "  ";

      // End the square
      cout << grid[currentRow][currentColumn].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

int SnakesAndLadders::rollDice() {
  return (int)rand() % 6 + 1;
  //return 1;
}

bool SnakesAndLadders::isGameOver() {
  return (grid[0][0].hasPiece());
}

bool SnakesAndLadders::getMove() {
  cout << "Press enter to roll a dice and make your move\n";
  cin.get();
  int roll = rollDice();
  cout << "You rolled a " << roll << "\n";
  Coordinate current = players[currentPlayer].getPiece(0)->position;

  // The below code doesn't work as expected and is somewhat messy.
  /*
  if(roll == 6) {
    players[currentPlayer].sixes++;
    if(players[currentPlayer].sixes == 3) {
      cout << "\nYou got three successive 6, your piece gets reset\n";
      this->resetPlayer(current);
      players[currentPlayer].canMove = false;
    } else {
      cout << ", you get to go again.\n";
      players[currentPlayer].canMove = true;
      this->executeMove(current, roll);
      this->getMove();
      currentPlayer=(currentPlayer+1)%(amountOfPlayers-1);
    }
  } else if(players[currentPlayer].canMove) {
    cout << "\n";
    players[currentPlayer].sixes = 0;
    this->executeMove(current, roll);
  } else cout << "\nYou can't move til you roll a six\n";
  */

  if(players[currentPlayer].canMove) {
    players[currentPlayer].sixes = 0;
    this->executeMove(current, roll);
  } else {
    cout << "You can't move\n";
  }

  if(isGameOver()) {
    state = 1;
    return true;
  } else {
    currentPlayer=(currentPlayer+1)%(amountOfPlayers-2);
  }

  return true;
}

// Part of the messy code on 107
/*
  void SnakesAndLadders::resetPlayer(Coordinate current) {
    Square currentSquare = grid[current.y][current.x];
    grid[9][0].addPiece(currentPlayer, currentSquare.getPiece(currentPlayer));
    currentSquare.removePiece(currentPlayer);
  }
*/

bool SnakesAndLadders::executeMove(Coordinate current,int roll) {
  Square *currentSquare = &grid[current.y][current.x];

  int position = currentSquare->getIdentifier()+roll;

  if(position == 100) {
    state = 1;
  } else if(position > 100) {
    position = 100 - (position % 100);

    // Check that the position actually changes
    if(position == currentSquare->getIdentifier()) {
      return true;
    }
  }

  Coordinate destination = squareToCoordinate(position);

  if(grid[destination.y][destination.x].hasPieceOwnedBy(2)) {
    cout << "You landed on a snake/ladder, oh no/oh yes";
    Piece* piece =  grid[destination.y][destination.x].getPiece(2);
    destination = piece->getDestination();
    if(destination.x == current.x && destination.y == current.y) return true;
  } 

  Square *destinationSquare = &grid[destination.y][destination.x];
  currentSquare->getPiece(currentPlayer)->position.x = destination.x;
  currentSquare->getPiece(currentPlayer)->position.y = destination.y;

  destinationSquare->addPiece(currentPlayer, currentSquare->getPiece(currentPlayer));
  currentSquare->removePiece(currentPlayer);

  return true;
}

Coordinate SnakesAndLadders::squareToCoordinate(int position) {
  return squareRefs[position-1].getPosition();
}
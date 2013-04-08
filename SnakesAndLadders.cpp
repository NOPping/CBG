#include "SnakesAndLadders.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

SnakesAndLadders::SnakesAndLadders() {
  srand(time(NULL));
  const int amountOfSystemItems = 2;
  this->rows = 10;
  this->columns = 10;
  this->amountOfPlayers = 2;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];

  this->systemItems = new Player[amountOfSystemItems];

  this->grid = new Square*[rows];
  this->squareRefs = new Square[100];
  for(int i=0; i<rows; i++) {
    this->grid[i] = new Square[columns];
  }

  const int playerTypes = 1;
  const int maxPlayerPieces = 1;

  vector<string> player1PieceTypes(playerTypes);
  vector<string> player2PieceTypes(maxPlayerPieces);

  player1PieceTypes[0] = "\033[38;5;160m◎";
  player2PieceTypes[0] = "\033[38;5;27m◎";

  this->players[0] = Player(playerTypes,player1PieceTypes,maxPlayerPieces);
  this->players[1] = Player(playerTypes,player2PieceTypes,maxPlayerPieces);

  const int systemTypes = 2;
  const int maxSystemPieces = 16;
  vector <string> system1PieceTypes(systemTypes);
  vector <string> system2PieceTypes(systemTypes);

  system1PieceTypes[0] = "\033[38;5;208mS";
  system1PieceTypes[1] = "\033[38;5;106mL";

  system2PieceTypes[0] = "\033[38;5;226mS";
  system2PieceTypes[1] = "\033[38;5;134mL";

  this->systemItems[0] = Player(systemTypes,system1PieceTypes,maxSystemPieces);
  this->systemItems[1] = Player(systemTypes,system2PieceTypes,maxSystemPieces);

  int totalPlayers = amountOfPlayers + amountOfSystemItems;

  string start[] = {"\033[48;5;16m","\033[48;5;241m"};
  string end = "\033[0m";

  int identifier = 0;

  int counter = 100;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {

      grid[i][j] = Square(counter,start[identifier],end,totalPlayers,Coordinate(j,i));
      squareRefs[counter-1] = grid[i][j];

      counter += (i % 2 == 0) ? -1 : 1;
      identifier = (identifier + 1)%2;
    }
    counter -= (i % 2 == 0) ? 9 : 11;
    identifier = (identifier + 1)%2;
  }

  grid[9][0].addPiece(0,players[0].addPiece(Coordinate(0,9)));
  grid[9][0].addPiece(1,players[1].addPiece(Coordinate(0,9)));

  Coordinate sl[16][2] = {
    // Snakes
    {squareToCoordinate(20),squareToCoordinate(17)},
    {squareToCoordinate(33),squareToCoordinate(7)},
    {squareToCoordinate(44),squareToCoordinate(22)},
    {squareToCoordinate(52),squareToCoordinate(31)},
    {squareToCoordinate(63),squareToCoordinate(54)},
    {squareToCoordinate(85),squareToCoordinate(67)},
    {squareToCoordinate(94),squareToCoordinate(71)},
    {squareToCoordinate(99),squareToCoordinate(61)},
    {squareToCoordinate(9),squareToCoordinate(29)},

    // Ladders
    {squareToCoordinate(15),squareToCoordinate(26)},
    {squareToCoordinate(24),squareToCoordinate(46)},
    {squareToCoordinate(40),squareToCoordinate(60)},
    {squareToCoordinate(64),squareToCoordinate(76)},
    {squareToCoordinate(69),squareToCoordinate(87)},
    {squareToCoordinate(83),squareToCoordinate(98)},
    {squareToCoordinate(48),squareToCoordinate(68)}
  };

  Piece* source;
  Piece* destination;

  for(int i=0; i<8; i++) {
    source = new Piece(&systemItems[0],i,sl[i][0],sl[i][1]);
    destination = new Piece(&systemItems[1],i);
    grid[sl[i][0].y][sl[i][0].x].addPiece(2,source);
    grid[sl[i][1].y][sl[i][1].x].addPiece(3,destination);
  }
  for(int i=8; i<16; i++) {
    source = new Piece(&systemItems[0],i-8,sl[i][0],sl[i][1],1);
    destination = new Piece(&systemItems[1],i-8,1);
    grid[sl[i][0].y][sl[i][0].x].addPiece(2,source);
    grid[sl[i][1].y][sl[i][1].x].addPiece(3,destination);
  }

  source = NULL;
  destination = NULL;
  delete source;
  delete destination;
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
        for(int i=0; i<amountOfPlayers; i++) {
          if(grid[currentRow][currentColumn].hasPieceOwnedBy(i)) {
            cout << *grid[currentRow][currentColumn].getPiece(i);
            pieceFound = true;
            break;
          }
        }
      }
      if(!pieceFound) cout << " ";

      cout << " ";

      if(!printSnakeLadder(currentColumn,currentRow)) cout << "  ";

      // End the square
      cout << grid[currentRow][currentColumn].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

bool SnakesAndLadders::printSnakeLadder(int x, int y) {
  for(int systemPlayer=2; systemPlayer<4; systemPlayer++) {
    if(grid[y][x].hasPieceOwnedBy(systemPlayer)) {
      Piece* systemPiece = grid[y][x].getPiece(systemPlayer);
      cout << systemPiece->owner->getCharacter(systemPiece->getType())
      << systemPiece->getIdentifier();
      return true;
    }
  }
  return false;
}

int SnakesAndLadders::rollDice() {
  return (int)rand() % 6 + 1;
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


  this->executeMove(current, roll);

  if(isGameOver()) {
    state = 1;
  } else {
    currentPlayer=(currentPlayer+1)%(amountOfPlayers);
  }

  return true;
}

bool SnakesAndLadders::executeMove(Coordinate current,int roll) {
  Square *currentSquare = &grid[current.y][current.x];

  int position = currentSquare->getIdentifier()+roll;

  if(position == 100) {
    state = 1;
  } else if(position > 100) {
    position = 100 - (position % 100);

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
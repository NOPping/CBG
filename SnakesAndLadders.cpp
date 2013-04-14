#include "SnakesAndLadders.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

SnakesAndLadders::SnakesAndLadders():Game(2,10,10), amountOfSystemItems(2) {
  srand(time(NULL));
  this->systemItems = new Player[amountOfSystemItems];
  this->squareRefs = new Square*[100];

  // Setup the Players
  const int playerTypes = 1;
  const int maxPlayerPieces = 1;

  vector<string> player1PieceTypes(playerTypes);
  vector<string> player2PieceTypes(maxPlayerPieces);

  player1PieceTypes[0] = "\033[38;5;160m◎";
  player2PieceTypes[0] = "\033[38;5;27m◎";

  this->players[0] = new SnakesAndLaddersPlayer(playerTypes,player1PieceTypes,maxPlayerPieces);
  this->players[1] = new SnakesAndLaddersPlayer(playerTypes,player2PieceTypes,maxPlayerPieces);

  // Setup the snakes and ladders
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

  // Setup all the squares
  int totalPlayers = amountOfPlayers + amountOfSystemItems;

  string start[] = {"\033[48;5;16m","\033[48;5;241m"};
  string end = "\033[0m";

  int identifier = 0;

  int counter = 100;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {

      grid[i][j] = Square(counter,start[identifier],end,totalPlayers,Coordinate(j,i));
      squareRefs[counter-1] = &grid[i][j];

      counter += (i % 2 == 0) ? -1 : 1;
      identifier = (identifier + 1)%2;
    }
    counter -= (i % 2 == 0) ? 9 : 11;
    identifier = (identifier + 1)%2;
  }

  // Add the players to the starting square
  Piece* player1Piece = new SourcePiece(players[0],Coordinate(0,9));
  Piece* player2Piece = new SourcePiece(players[1],Coordinate(0,9));
  squareRefs[0]->addPiece(0,(players[0]->addPiece(player1Piece)));
  squareRefs[0]->addPiece(1,(players[1]->addPiece(player2Piece)));

  Coordinate snakes[maxSystemPieces/2][2] = {
    {squareToCoordinate(20),squareToCoordinate(17)},
    {squareToCoordinate(33),squareToCoordinate(7)},
    {squareToCoordinate(44),squareToCoordinate(22)},
    {squareToCoordinate(52),squareToCoordinate(31)},
    {squareToCoordinate(63),squareToCoordinate(54)},
    {squareToCoordinate(85),squareToCoordinate(67)},
    {squareToCoordinate(94),squareToCoordinate(71)},
    {squareToCoordinate(99),squareToCoordinate(61)},
  };
  Coordinate ladders[maxSystemPieces/2][2] = {
    {squareToCoordinate(9),squareToCoordinate(29)},
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

  for(int i=0; i<maxSystemPieces/amountOfSystemItems; i++) {
    source = new SystemPiece(&systemItems[0],snakes[i][0],snakes[i][1],i);
    destination = new IdentifierPiece(&systemItems[1],i);
    grid[snakes[i][0].y][snakes[i][0].x].addPiece(2,source);
    grid[snakes[i][1].y][snakes[i][1].x].addPiece(3,destination);
  }
  for(int i=0; i<maxSystemPieces/2; i++) {
    source = new SystemPiece(&systemItems[0],ladders[i][0],ladders[i][1],i);
    destination = new IdentifierPiece(&systemItems[1],i);
    source->setType(1);
    destination->setType(1);
    grid[ladders[i][0].y][ladders[i][0].x].addPiece(2,source);
    grid[ladders[i][1].y][ladders[i][1].x].addPiece(3,destination);
  }
}

SnakesAndLadders::~SnakesAndLadders() {
  delete [] systemItems;
  delete [] squareRefs;
}

void SnakesAndLadders::drawScreen() {
  clearScreen();

  cout << "Player " << (this->currentPlayer+1) << " it is your go\n\n";

  for(int y=0; y<rows; y++) {
    for(int x=0; x<columns; x++) {

      // Start the Square
      cout << grid[y][x].getStart();

      // Print square number
      printf ("%-3d",grid[y][x].getIdentifier());

      // Print player piece if any.
      bool pieceFound = false;
      if(grid[y][x].hasPiece()) {
        for(int players=0; players<amountOfPlayers; players++) {
          if(grid[y][x].hasPieceOwnedBy(players)) {
            cout << grid[y][x];
            pieceFound = true;
            break;
          }
        }
      }
      if(!pieceFound) cout << " ";

      cout << " ";

      if(!printSnakeLadder(x,y)) cout << "  ";

      // End the square
      cout << grid[y][x].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

bool SnakesAndLadders::printSnakeLadder(int x, int y) {
  for(int systemPlayer=amountOfPlayers; systemPlayer<amountOfPlayers+amountOfSystemItems; systemPlayer++) {
    if(grid[y][x].hasPieceOwnedBy(systemPlayer)) {
      Piece* systemItem = grid[y][x].getPiece(systemPlayer);
      systemItem->print(cout);
      return true;
    }
  }
  return false;
}

int SnakesAndLadders::rollDice() {
  return (int)rand() % 6 + 1;
}

int SnakesAndLadders::isOver() {
  return squareRefs[99]->hasPiece() ? 1 : 0;
}

bool SnakesAndLadders::getMove() {
  cout << "Press enter to roll a dice and make your move\n";
  cin.get();
  int roll = rollDice();
  int total=roll;
  while((roll % 6 == 0) && (total != 6*3)) {
    cout << "You rolled a " << roll << " go again\n";
    cin.get();
    roll = rollDice();
    total += roll;
  }
  if(roll != 6) cout << "You rolled a " << roll << "\n";
  
  SnakesAndLaddersPlayer* player = dynamic_cast<SnakesAndLaddersPlayer*>(players[currentPlayer]);
  Coordinate current = dynamic_cast<SourcePiece*>(player->getPiece(0))->getSource();
  Square* sourceSquare = &grid[current.y][current.x];

  if(total == 6) {
    player->suspended = false;
  }

  if(total == 6*3) {
    player->suspended = true;
    executeMove(sourceSquare, squareRefs[0]);
    cout << "You rolled 3 sucessive 6s.\n";
  } else if(!player->suspended) {
    total = total + sourceSquare->getIdentifier()-1;
    total = total > 100 ? 100 - (total % 100) : total;
    this->executeMove(sourceSquare, squareRefs[total-1]);
  } else {
    cout << "You are suspended until you roll a 6\n";
  }

  currentPlayer=(currentPlayer+1)%(amountOfPlayers);

  return true;
}

bool SnakesAndLadders::executeMove(Square* sourceSquare, Square* destinationSquare) {
  if(destinationSquare->hasPieceOwnedBy(2)) {
    DestinationPiece* piece =  dynamic_cast<DestinationPiece*>(destinationSquare->getPiece(2));
    Coordinate modifiedDestination = piece->getDestination();
    destinationSquare = &grid[modifiedDestination.y][modifiedDestination.x];
  }
  
  if(sourceSquare == destinationSquare) {
    return true;
  } else {
    SourcePiece* piece = dynamic_cast<SourcePiece*>(sourceSquare->getPiece(currentPlayer));
    Coordinate destinationCoordinate = destinationSquare->getPosition();
    piece->setSource(destinationCoordinate);
    
    destinationSquare->addPiece(currentPlayer, piece);
    sourceSquare->removePiece(currentPlayer);
    return true;
  }
}

Coordinate SnakesAndLadders::squareToCoordinate(int position) {
  return squareRefs[position-1]->getPosition();
}
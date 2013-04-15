/// Snakes and Ladders Game.
/// @author Ian Duffy
/// @author Darren Brogan

#include "SnakesAndLadders.h"

using namespace std;

typedef SnakesAndLaddersPlayer SLPlayer;
typedef SourcePiece SrcPiece;
typedef DestinationPiece DestPiece;
typedef IdentifierPiece IDPiece;
typedef Coordinate Coord;

SnakesAndLadders::SnakesAndLadders():Game(2,10,10), amountOfSystemItems(2) {
  // Set srand a more random die roll.
  srand(time(NULL));

  // systemItems holds the snakes and ladders.
  this->systemItems = new Player[amountOfSystemItems];

  // This is simply just used an a reference instead of trying to convert
  // Coords to square ids.
  this->squareRefs = new Square*[100];

  // Setup the Players.
  const int playerTypes = 1;
  const int maxPlayerPieces = 1;

  vector<string> player1PieceTypes(playerTypes);
  vector<string> player2PieceTypes(maxPlayerPieces);

  // Set their character representations.
  player1PieceTypes[0] = FRED "◎";
  player2PieceTypes[0] = FBLUE "◎";

  players[0] = new SLPlayer(playerTypes,player1PieceTypes,maxPlayerPieces);
  players[1] = new SLPlayer(playerTypes,player2PieceTypes,maxPlayerPieces);

  // Setup the snakes and ladders.
  const int systemTypes = 2;
  const int maxSystemPieces = 16;
  vector <string> system1PieceTypes(systemTypes);
  vector <string> system2PieceTypes(systemTypes);

  // Set the start point snake/ladder character representations.
  system1PieceTypes[0] = FVIOLET "S";
  system1PieceTypes[1] = FGREEN "L";

  // Set the end point snake/ladder character representations.
  system2PieceTypes[0] = FORANGE "S";
  system2PieceTypes[1] = FMAGENTA "L";

  systemItems[0] = Player(systemTypes,system1PieceTypes,maxSystemPieces);
  systemItems[1] = Player(systemTypes,system2PieceTypes,maxSystemPieces);

  // Setup all the squares.
  int totalPlayers = amountOfPlayers + amountOfSystemItems;

  string start[] = {BBLACK,BGRAY};
  string end = RESET;

  int identifier = 0;

  int counter = 100;

  for(int i=0; i<rows; i++) {
    for(int j=0; j<columns; j++) {

      grid[i][j] = Square(counter,start[identifier],end,totalPlayers,
                          Coord(j,i));
      squareRefs[counter-1] = &grid[i][j];

      counter += (i % 2 == 0) ? -1 : 1;
      identifier = (identifier + 1)%2;
    }
    counter -= (i % 2 == 0) ? 9 : 11;
    identifier = (identifier + 1)%2;
  }

  // Add the players to the starting square.
  Piece* player1Piece = new SrcPiece(players[0],Coord(0,9));
  Piece* player2Piece = new SrcPiece(players[1],Coord(0,9));
  squareRefs[0]->addPiece(0,(players[0]->addPiece(player1Piece)));
  squareRefs[0]->addPiece(1,(players[1]->addPiece(player2Piece)));

  Coord snakes[maxSystemPieces/2][2] = {
    {squareToCoordinate(20),squareToCoordinate(17)},
    {squareToCoordinate(33),squareToCoordinate(7)},
    {squareToCoordinate(44),squareToCoordinate(22)},
    {squareToCoordinate(52),squareToCoordinate(31)},
    {squareToCoordinate(63),squareToCoordinate(54)},
    {squareToCoordinate(85),squareToCoordinate(67)},
    {squareToCoordinate(94),squareToCoordinate(71)},
    {squareToCoordinate(99),squareToCoordinate(61)},
  };
  Coord ladders[maxSystemPieces/2][2] = {
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

  // Place all the snakes onto the board.
  for(int i=0; i<maxSystemPieces/amountOfSystemItems; i++) {
    source = new SystemPiece(&systemItems[0],snakes[i][0],snakes[i][1],i);
    destination = new IDPiece(&systemItems[1],i);
    // Snake start point.
    grid[snakes[i][0].y][snakes[i][0].x].addPiece(2,source);
    // Snake end point.
    grid[snakes[i][1].y][snakes[i][1].x].addPiece(3,destination);
  }

  // Places all the ladders onto the board.
  for(int i=0; i<maxSystemPieces/2; i++) {
    source = new SystemPiece(&systemItems[0],ladders[i][0],ladders[i][1],i);
    destination = new IDPiece(&systemItems[1],i);
    // Sets the piece to use the ladder character representation.
    source->setType(1);
    destination->setType(1);
    // Ladder start point.
    grid[ladders[i][0].y][ladders[i][0].x].addPiece(2,source);
    // Ladder end point.
    grid[ladders[i][1].y][ladders[i][1].x].addPiece(3,destination);
  }
}

/// Deconstructor for snakes and ladders.
SnakesAndLadders::~SnakesAndLadders() {
  delete [] systemItems;
  delete [] squareRefs;
}

/// Prints out the board, players, snakes and ladders.
void SnakesAndLadders::drawScreen() {
  clearScreen();

  cout << "Player " << (currentPlayer+1) << " it is your go\n\n";

  for(int y=0; y<rows; y++) {
    for(int x=0; x<columns; x++) {

      // Start the Square.
      cout << grid[y][x].getStart();

      // Print square number.
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

/// Prints a snake and ladder at coordinates x,y.
bool SnakesAndLadders::printSnakeLadder(int x, int y) {
  int max = amountOfPlayers+amountOfSystemItems;
  for(int systemPlayer=amountOfPlayers; systemPlayer<max; systemPlayer++) {
    if(grid[y][x].hasPieceOwnedBy(systemPlayer)) {
      Piece* systemItem = grid[y][x].getPiece(systemPlayer);
      systemItem->print(cout);
      return true;
    }
  }
  return false;
}

/// Generate a random number between 1 and 6.
int SnakesAndLadders::rollDice() {
  return (int)rand() % 6 + 1;
}

/// Check if square with identifier 100 is occupied.
int SnakesAndLadders::isOver() {
  return squareRefs[99]->hasPiece() ? 1 : 0;
}

/// Calls rollDice() and calculates the destination square
/// Passes these too executeMove().
bool SnakesAndLadders::getMove() {
  // Setup a pointer to the current player and the square they are on.
  SLPlayer* player = dynamic_cast<SLPlayer*>(players[currentPlayer]);
  Coord current = dynamic_cast<SrcPiece*>(player->getPiece(0))->getSource();
  Square* srcSquare = &grid[current.y][current.x];

  // Prompt the user to roll.
  cout << "Press enter to roll a dice and make your move\n";
  cin.get();
  int roll = rollDice();
  int total=roll;

  // Unsuspend the player if they roll a 6.
  if(roll == 6) {
    player->suspended = false;
  }

  // Roll again if a 6 is rolled.
  while((roll % 6 == 0) && (total != 6*3)) {
    cout << "You rolled a " << roll << " go again\n";
    cin.get();
    roll = rollDice();
    total += roll;
  }
  if(roll != 6) cout << "You rolled a " << roll << "\n";

  if(total == 6*3) {
    player->suspended = true;
    executeMove(srcSquare, squareRefs[0]);
    cout << "You rolled 3 sucessive 6s.\n";
  } else if(!player->suspended) {
    total = total + srcSquare->getIdentifier()-1;
    total = total > 100 ? 100 - (total % 100) : total;
    this->executeMove(srcSquare, squareRefs[total-1]);
  } else {
    cout << "You are suspended until you roll a 6\n";
  }

  // Switch Player.
  currentPlayer=(currentPlayer+1)%(amountOfPlayers);

  return true;
}

/// Moves the piece on srcSquare to destSquare.
bool SnakesAndLadders::executeMove(Square* srcSquare, Square* destSquare) {

  // Check if the square has a snake or ladder.
  if(destSquare->hasPieceOwnedBy(2)) {
    DestPiece* piece =  dynamic_cast<DestPiece*>(destSquare->getPiece(2));
    Coord modifiedDestination = piece->getDestination();
    destSquare = &grid[modifiedDestination.y][modifiedDestination.x];
  }

  // Check if the source square and destination square are the same.
  if(srcSquare == destSquare) {
    return true;
  } else {
    SrcPiece* piece = dynamic_cast<SrcPiece*>(srcSquare->getPiece(currentPlayer));
    Coord destinationCoord = destSquare->getPosition();
    piece->setSource(destinationCoord);

    destSquare->addPiece(currentPlayer, piece);
    srcSquare->removePiece(currentPlayer);
    return true;
  }
}

/// Converts an square identifier to a coordinate.
Coord SnakesAndLadders::squareToCoordinate(int position) {
  return squareRefs[position-1]->getPosition();
}

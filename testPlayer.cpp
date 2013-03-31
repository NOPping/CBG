#include <iostream>
#include "Player.h"
#include "Piece.h"
#include "Coordinate.h"

using namespace std;

int main() {
  // Setup Player 1
  int player1AmountOfTypes = 2;
  string player1Types[] = {"x","o"};
  Player Player1 = Player(player1AmountOfTypes,player1Types,12);

  // Setup a Piece for Player 1
  Coordinate testCoordinate = Coordinate(2,2);
  Piece test = Piece(&testCoordinate,&Player1);

  // Print out the character for the piece
  // Type is 0 by default so x should be printed
  cout << test.getType() << "\n";
  cout << test.putPiece() << "\n";

  // Set type to be 1 o should be printed
  test.setType(1);
  cout << test.getType() << "\n";
  cout << test.putPiece() << "\n";

  // Set type to something out of bounds, type
  // should not change.
  test.setType(5);
  cout << test.getType() << "\n";
  cout << test.putPiece() << "\n";
  return 0;
}

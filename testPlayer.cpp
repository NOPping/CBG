#include <iostream>
#include "Player.h"
#include "Piece.h"
#include "Coordinate.h"

using namespace std;

int main() {
  // Setup Player 1
  int player1AmountOfTypes = 2;
  string player1Types[] = {"x","o"};
  Player Player1 = Player(&player1AmountOfTypes,player1Types);
  
  // Setup a Piece for Player 1
  Coordinate testCoordinate = Coordinate(2,2);
  Piece test = Piece(&testCoordinate,&Player1);
  
  // Print out the character for the piece
  cout << test.putPiece();
}

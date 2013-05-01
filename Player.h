/// Player
/// @author Ian Duffy
/// @author Darren Brogan

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Coordinate.h"

using std::string;
using std::vector;

class Piece;
class Player {
  protected:
  /// Protected Data.
  /// Int to store the amount of pieces the player currently owns.
  int amountOfPieces;

  /// Int variable to store the max amount of pieces a player could own.
  int maxPieces;

  /// Variable used to store the amount of types of pieces the player has.
  int amountOfTypes;

  /// Vector to store the different types of pieces the player could own.
  vector<string> types;

  /// Vector of type Piece pointer to store all the pieces the player owns.
  vector<Piece*> pieces;
  public:
  /// Public constructors.
  Player();
  Player(int amountOfTypes, vector<string> types, int maxPieces);
  virtual ~Player();

  /// Public functions.
  int getAmountOfPieces() const;

  /// Remove Piece from the player and return a bollean to identify
  /// if it succeded or failed.
  bool removePiece(Piece *toBeRemoved);

  /// Check if pieces vector at index type is empty
  bool hasType(int type) const;

  /// Function to check does the player have room for another piece
  /// Necessary to check before adding piece to ensure references
  /// never reference a non existant piece.
  bool hasRoomForPiece() const;

  /// Returns a string from pieces vector at index type.
  string getCharacter(int type) const;

  /// Add pieces to the pieces vector.
  Piece& addPiece();
  Piece& addPiece(Piece* insert);

  /// Returns a reference to the piece in the pieces vector at index.
  Piece& getPiece(int index) const;

  /// Return weather this player can move or not
  bool suspended;
};

#endif

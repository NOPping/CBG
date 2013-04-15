/// Snakes and Ladders Game.
/// @author Ian Duffy
/// @author Darren Brogan

#ifndef SNAKESANDLADDERS_H
#define SNAKESANDLADDERS_H

#include "Game.h"
#include "SnakesAndLaddersPlayer.h"
#include "SourcePiece.h"
#include "SystemPiece.h"

class SnakesAndLadders : public Game {
  private:
    /// Prints out the board, players, snakes and ladders.
    void drawScreen();

    /// Generate a random number between 1 and 6.
    int rollDice();

    /// Calls rollRice() and calculates the destination square
    /// Passes these too executeMove().
    bool getMove();

    /// Moves the piece on srcSquare to destSquare.
    bool executeMove(Square* sourceSquare, Square* destinationSquare);

    /// Converts an square identifier to a coordinate.
    Coordinate squareToCoordinate(int position);

    /// Pointers to the squares based on their identifiers.
    Square** squareRefs;

    /// Array that holds the snakes and ladder character representations.
    Player* systemItems;

    /// Amount of system items.
    const int amountOfSystemItems;

    /// Prints a snake and ladder at coordinates x,y.
    bool printSnakeLadder(int x, int y);

    /// Check if square with identifier 100 is occupied.
    int isOver();

  public:
    SnakesAndLadders();
    ~SnakesAndLadders();
};

#endif

/// Reversi Game.
/// @author Peter Morgan

#ifndef REVERSI_H
#define REVERSI

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "Game.h"

class Reversi:public Game {
    /// Gets a move from the player
    bool getMove();

    /// Prints out the board and the players pieces.
    void drawScreen() const;

    /// Prompts with message to get a point between 0 and range.
    int  getPoint(string message, int range) const;

    /// Returns the opposition.
    int  getOpposition() const;

    //determins if a destinaiton swuare is valid   
    bool isValidMove(int destinationX) const;  

    // call the flanks method to ensure the destination coordinate  flanks an opponents piece
    //if it does it adds the piece to the destination square
    bool executeMove(Square& destinationSquare)const;
    
    //determines the winner  of the game
    int  isOver() const;
    
    //checks a line of pieces to see if it ends with a piece that belong to the 
    //current player if it does, it flips the line of pieces to the current players colour   
    bool checkNext(Square &current,int yOffset,int xOffset,bool flip) const;
    
    //checks if a coordinate flanks an opponents piece 
    //calls check next to see if the piece is inline with an existing piece owned 
    //by the same player 
    bool flanks(Square current,bool flip) const;
    
    //checks if a move is  within the bounds of the board
    bool isLegal(Coordinate current,int iOffset,int jOffset) const;
    
public:
  Reversi();
};


#endif

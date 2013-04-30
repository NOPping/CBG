#ifndef REVERSI_H
#define REVERSI

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Game.h"
class Reversi:public Game {
    //gets a move from the player
    bool getMove();

    //flushes the screen and prints out the board
    void drawScreen() const;

    //determins if a destinaiton swuare is valid   
    bool isValidMove(int destinationX) const;  

    //Gets a single int from the user
    int  getPoint(string message, int range) const;

    // call the flanks method to ensure the destination coordinate  flanks an opponents piece
    //if it does it adds the piece to the destination square
    bool executeMove(Square& destinationSquare)const;
    //determines the winner  of the game
    int  isOver() const;
    int  getOpposition() const;
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

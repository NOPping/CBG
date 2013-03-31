#include "Checkers.h"

using namespace std;

Checkers::Checkers() {
  this->rows = 8;
  this->columns = 8;
  this->amountOfPlayers = 2;
  this->currentPlayer = 0;
  this->state = 0;
  this->players = new Player[this->amountOfPlayers];
  this->grid = new Square*[rows];
  for(int i=0;i<rows;i++) {
    this->grid[i] = new Square[columns];
  }

  int amountOfPieceTypes = 2;
  int maxAmountOfPlayerPieces = 12;
  string player1PieceTypes[] = {"\033[0;32;40m ○ \033[0m","\033[0;32;40m ◎ \033[0m"};
  string player2PieceTypes[] = {"\033[0;37;40m ○ \033[0m","\033[0;37;40m ◎ \033[0m"};
  
  this->players[0] = Player(amountOfPieceTypes,
                            player1PieceTypes,maxAmountOfPlayerPieces);
  
  this->players[1] = Player(amountOfPieceTypes,
                            player2PieceTypes,maxAmountOfPlayerPieces);
  
  string squareRepresentations[] = {"WHITE",
                                    "BLACK"};
                                    
  int squareIdentifier = 0;
  
  
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      // Color the square
      this->grid[i][j] = Square(squareIdentifier,
                                squareRepresentations[squareIdentifier],
                                amountOfPlayers,
                                Coordinate(i,j));
      
      // Check if its a black square
      /*if(squareIdentifier == 1) {
        if(i<3) {
          this->grid[i][j].addPiece(0,
          this->players[0].addPiece(Coordinate(i,j)));
        }
        else if(i>4) {
          this->grid[i][j].addPiece(1,
          this->players[1].addPiece(Coordinate(i,j)));
        }
      }
      */
      // Switch identifier
      squareIdentifier = (squareIdentifier + 1)%2;
    }
    // Switch identifier
    squareIdentifier = (squareIdentifier + 1)%2;
  }
  //players[0].addPiece(Coordinate(0,0));
  //this->grid[0][1].addPiece(0,players[0].addPiece(Coordinate(0,0)));
}

void Game::drawScreen() {
  cout << "\033[2J\033[;H";
  cout << "Player " << (this->currentPlayer+1) << " it is your go\n\n";
  cout << grid[0][0].putSquare();
  /*for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      cout << grid[i][j].putSquare() << "\n";
    }
    cout << "\n";
  }*/
  cout << "\n";
}

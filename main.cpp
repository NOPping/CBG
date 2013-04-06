#include <iostream>
#include "Checkers.h"
#include "ConnectFour.h"

using namespace std;

int main() {
  int selection=0;
  cout << "Welcome to compendium of board games" << "\n";
  cout << "====================================" << "\n";
  cout << "1) Checkers\n2) ConnectFour\n3) Snakes and Ladders\n4) Reversi\n";
  cout << "====================================" << "\n";
  cout << "\nInsert the number of the game you wish to play: ";
  cin >> selection;
  Game* games = {
      new Checkers()
      //new ConnectFour(),
      //new SnakesAndLadders(), 
      //new Reversi()
  };
  selection--;
  if(selection >= 0 && selection < 4) {
    games[selection].start();
  } else {
    cout << "Invalid Selection";
  }
  return 0;
}
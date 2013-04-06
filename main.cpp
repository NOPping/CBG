#include <iostream>
#include "Checkers.h"
#include "ConnectFour.h"

using namespace std;

int main() {
  int selection=0;
  
  std::string games[] = {
    "1) Checkers",
    "2) ConnectFour",
    "3) Snakes and Ladders",
    "4) Reversi"
  };
  
  cout << "Welcome to compendium of board games" << "\n";
  cout << "====================================" << "\n";
  
  for(int i=0;i<4;i++) {
    cout << games[i] << "\n";
  }
  
  cout << "====================================" << "\n";
  cout << "\nInsert the number of the game you wish to play: ";
  cin >> selection;
  
  if(selection >= 0 && selection < 4) {
    if(selection == 1) {
      Checkers().start();
    } else if(selection == 2) {
      ConnectFour().start();
    }
  } else {
    cout << "Invalid Selection";
  }
  return 0;
}
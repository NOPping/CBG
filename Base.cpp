#include "Base.h"
using std::cout;
using std::cin;
using std::string;
using std::vector;

Base::Base():Game(2,8,8){}

void Base::drawScreen() const {
  clearScreen();
  cout << "Player " << (currentPlayer+1) << " it is your go\n\n  ";
  for(int i=0; i<rows; i++) cout << " " << i << " ";
  cout << "\n";
  for(int i=0; i<rows; i++) {
    cout << i << " ";
    for(int j=0; j<columns; j++) {
      cout << grid[i][j].getStart();
      cout << grid[i][j];
      cout << grid[i][j].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

int Base::getPoint(string message, int range) const{
  int point=0;
  while(true) {
    cout << message;
    cin >> point;

    // Check that input is a numeric value.
    if(cin.fail()) {
      cout << "\nYou entered a non numeric value, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    // Check that input is within our grid range.
    if(point < 0 || point >= range) {
      cout << "\nPoint out of range, try again\n";
      continue;
    }

    return point;
  }
}

/// Returns the opposition.
int Base::getOpposition() const{
  return (currentPlayer+1)%amountOfPlayers;
}




/// Common functions between games that use X, Y selectors.
/// @author Peter Morgan

#include "GameWithXYSelector.h"

using std::cout;
using std::cin;

GameWithXYSelector::GameWithXYSelector(const int amountOfPlayers,
                                       const int columns, const int rows)
:Game(amountOfPlayers,columns,rows) {}

/// Prints out the board and all the players pieces.
void GameWithXYSelector::drawScreen() const {
  clearScreen();
  cout << "Player " << (currentPlayer+1) << " it is your go\n\n  ";
  for(int x=0; x<columns; x++) cout << " " << x << " ";
  cout << "\n";
  for(int y=0; y<rows; y++) {
    cout << y << " ";
    for(int x=0; x<columns; x++) {
      cout << grid[y][x].getStart();
      cout << grid[y][x];
      cout << grid[y][x].getEnd();
    }
    cout << "\n";
  }
  cout << "\n";
}

/// Prompts with message to get a point between 0 and range.
int GameWithXYSelector::getPoint(const string message, const int range) const {
  int point=0;
  while(true) {
    cout << message;
    cin >> point;

    // Check that input is a numeric value.
    if(cin.fail()) {
      drawScreen();
      cout << "\nYou entered a non numeric value, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    // Check that input is within our grid range.
    if(point < 0 || point >= range) {
      drawScreen();
      cout << "\nPoint out of range, try again\n";
      cin.clear();
      cin.ignore(1000,'\n');
      continue;
    }

    return point;
  }
}

/// Returns the opposition.
int GameWithXYSelector::getOpposition() const {
  return (currentPlayer+1)%amountOfPlayers;
}




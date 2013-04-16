/// Game Launcher.
/// @author Ian Duffy
/// @author Darren Brogan.

#include <iostream>
#include <iomanip>
#include "Checkers.h"
#include "ConnectFour.h"
#include "SnakesAndLadders.h"
#include "Colors.h"
#include "Reversi.h"

using std::cout;
using std::cin;
using std::string;

void border(int);

/// Prints out a menu of the games available.
int main() {
  int selection=0;
  const int numberOfGames = 4;
  
  vector <Game*> games(numberOfGames);
  // Create a vector of pointers to hold the locations of each game.
  games[0] =  new Checkers();
  games[1] =  new ConnectFour();
  games[2] =  new SnakesAndLadders();
  games[3] =  new Reversi();
  
  string menu[] = {
    "1) Checkers",
    "2) ConnectFour",
    "3) Snakes and Ladders",
    "4) Reversi"
  };
  cout << CLEAR FVIOLET;

  cout << "    ____                                     _ _                          __ \n";
  cout << "   / ___|___  _ __ ___  _ __   ___ _ __   __| (_)_   _ _ __ ___     ___  / _|\n";
  cout << "  | |   / _ \\| '_ ` _ \\| '_ \\ / _ \\ '_ \\ / _` | | | | | '_ ` _ \\   / _ \\| |_ \n";
  cout << "  | |__| (_) | | | | | | |_) |  __/ | | | (_| | | |_| | | | | | | | (_) |  _|\n";
  cout << "   \\____\\___/|_| |_| |_| .__/ \\___|_| |_|\\__,_|_|\\__,_|_| |_| |_|  \\___/|_|  \n";
  cout << "                       |_|                                                   \n";
  cout << "         _                         _                                   \n";
  cout << "        | |__   ___   __ _ _ __ __| |   __ _  __ _ _ __ ___   ___  ___ \n";
  cout << "        | '_ \\ / _ \\ / _` | '__/ _` |  / _` |/ _` | '_ ` _ \\ / _ \\/ __|\n";
  cout << "        | |_) | (_) | (_| | | | (_| | | (_| | (_| | | | | | |  __/\\__ \\\n";
  cout << "        |_.__/ \\___/ \\__,_|_|  \\__,_|  \\__, |\\__,_|_| |_| |_|\\___||___/\n";
  cout << "                                       |___/                           \n";

  cout << RESET;
  cout << FRED "\n";
  border(80);
  cout << RESET "\n";
  // Print out the titles of each game.
  for(int i=0; i<numberOfGames; i++) {
    cout << menu[i] << "\n";
  }
  cout << FRED "\n";
  border(80);
  cout << RESET;
  bool validSelection = false;
  while(!validSelection) {
    cout << "\nInsert the number of the game you wish to play: ";
    cin >> selection;
    cin.clear();
    cin.ignore(10000,'\n');
    // Ensure that the selection is valid.
    if(selection > 0 && selection <= numberOfGames) {
      validSelection = true;
      // Launch selected game.
      games[selection-1]->start();
    } else {
      cout << "\nInvalid Selection";
    }
  }
  
  games.clear();
  
  return 0;
}

/// Prints a border of the specified width.
void border(int width) {
  for(int i=0; i<width/2; i++)cout << "=-";
  cout << "\n";
}

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

  string menu[] = {
    "1) Checkers",
    "2) ConnectFour",
    "3) Snakes and Ladders",
    "4) Reversi"
  };

  // Flush the screen and set the foreground color to violet.
  cout << CLEAR FVIOLET;

  // Print out ASCII art of the product name.
  cout << "    ____                                     _ _                  "
  << "        __ \n"
  << "   / ___|___  _ __ ___  _ __   ___ _ __   __| (_)_   _ _ __ ___   "
  << "  ___  / _|\n"
  << "  | |   / _ \\| '_ ` _ \\| '_ \\ / _ \\ '_ \\ / _` | | | | | '_ ` "
  << "_ \\   / _ \\| |_ \n"
  << "  | |__| (_) | | | | | | |_) |  __/ | | | (_| | | |_| | | | | | | "
  << "| (_) |  _|\n"
  << "   \\____\\___/|_| |_| |_| .__/ \\___|_| |_|\\__,_|_|\\__,_|_| |_|"
  << " |_|  \\___/|_|  \n"
  << "                       |_|                                        "
  << "           \n"
  << "         _                         _                              "
  << "     \n"
  << "        | |__   ___   __ _ _ __ __| |   __ _  __ _ _ __ ___   ___ "
  << " ___ \n"
  << "        | '_ \\ / _ \\ / _` | '__/ _` |  / _` |/ _` | '_ ` _ \\ / "
  << " _\\/ __|\n"
  << "        | |_) | (_) | (_| | | | (_| | | (_| | (_| | | | | | |  __/"
  << "\\__ \\\n"
  << "        |_.__/ \\___/ \\__,_|_|  \\__,_|  \\__, |\\__,_|_| |_| |_|"
  << "\\___||___/\n"
  << "                                       |___/\n";

  // Switch the forground color to red.
  cout << RESET << FRED "\n";

  // Create a border.
  const int borderWitdh = 80;
  border(borderWitdh);
  cout << RESET "\n";

  // Print out the titles of each game.
  for(int i=0; i<numberOfGames; i++) {
    cout << menu[i] << "\n";
  }

  // Create a closing border.
  cout << FRED "\n";
  border(borderWitdh);
  cout << RESET;

  // Prompt and read in the users selection.
  cout << "\nInsert the number of the game you wish to play: \n";
  while(true) {
    cin >> selection;
    cin.clear();
    cin.ignore(1000,'\n');

    // Check that input is a numeric value.
    if(cin.fail()) {
      cout << "\nYou entered a non numeric value, try again\n";
      continue;
    }

    if(selection < 1 || selection > 4) {
      cout << "\nYou didn't enter a valid number, please enter a number in the "
      << "range 1-4\n";
      continue;
    }

    switch(selection) {
    case  1: {
      Checkers checkers = Checkers();
      checkers.start();
      return 0;
    }
    case 2: {
      ConnectFour connectFour = ConnectFour();
      connectFour.start();
      return 0;
    }
    case 3: {
      SnakesAndLadders snakesAndLadders = SnakesAndLadders();
      snakesAndLadders.start();
      return 0;
    }
    case 4: {
      Reversi reversi = Reversi();
      reversi.start();
      return 0;
    }
    }
  }
  return 0;
}

/// Prints a border of the specified width.
void border(const int width) {
  cout.width(width+1);
  cout.fill('=');
  cout << "\n";
}

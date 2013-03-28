#include "Game.h"

virtual void start() {
    while(state == 0) {
        if(getMove()) {
          currentPlayer = (currentPlayer == 0) ? 1 : 0;
        }
        drawScreen();
    }
}
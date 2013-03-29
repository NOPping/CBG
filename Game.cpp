#include "Game.h"

void Game::start() {
    while(this->state == 0) {
        if(this->getMove()) {
          this->currentPlayer = (this->currentPlayer == 0) ? 1 : 0;
        }
        this->drawScreen();
    }
}
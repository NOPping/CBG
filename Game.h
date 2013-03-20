#ifndef GAME_H
#define GAME_H
 
class Game {
private:
  Squares*  grid[][];
  Player*   players[];
  Player*   whoseGo;
  bool      isOver;
  
  virtual   bool            getMove();
  virtual   void            drawScreen();
public:
  virtual   void            Start();
};
 
#endif
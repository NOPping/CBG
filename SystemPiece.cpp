#include "SystemPiece.h"

SystemPiece::SystemPiece(Player* owner, Coordinate source,
                         Coordinate destination, int identifier) 
                         : PositionPiece(owner, source) {
    this->destination = destination;
    this->identifier = identifier;
}
#include "SystemPiece.h"

SystemPiece::SystemPiece(Player* owner, Coordinate source, Coordinate destination, int identifier)
: Piece(owner), SourcePiece(owner, source), DestinationPiece(owner, destination), IdentifierPiece(owner, identifier) {
}

SystemPiece::~SystemPiece() {}
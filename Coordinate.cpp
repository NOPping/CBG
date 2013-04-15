/// Encapsulates the idea of a location made up of an X point and a Y point.
/// @author Darren Brogan

#include "Coordinate.h"

/// Default constructor.
Coordinate::Coordinate() {}

/// Constructor with paramaters.
Coordinate::Coordinate(int x, int y) {
  this->x = x;
  this->y = y;
}

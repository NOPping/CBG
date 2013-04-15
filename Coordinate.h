/// Encapsulates the idea of a location made up of an X point and a Y point.
/// @author Darren Brogan

#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate {
    /// The X position.
    int x;
    
    /// The Y position.
    int y;
    
    Coordinate();    
    Coordinate(int x, int y);
};

#endif
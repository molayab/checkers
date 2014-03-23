#ifndef STRUCT_H
#define STRUCT_H

struct CGCoordinate2D {
    long x; // ROWS
    long y; // COLS

    bool operator==(const CGCoordinate2D &c) const {
        return (x == c.x && y == c.y);
    }
};

#endif

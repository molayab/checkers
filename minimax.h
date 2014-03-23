#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include "node.h"
#include "struct.h"

struct minmax_t {
    Node * node;
    uint8_t heuristc;
};

class Minimax {
private:
    Node * root;
    minmax_t minimax(Node *, unsigned int, bool);
    static uint8_t heuristic[8][8];

public:
    Minimax(Board);
    ~Minimax();

    CGCoordinate2D run();
    static uint8_t getHeuristic(CGCoordinate2D);
};

#endif

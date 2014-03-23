#ifndef NODE_H
#define NODE_H

#include <vector>
#include "board.h"
#include "struct.h"


class Node {
    std::vector<Node> childs;
    //Board board;
    CGCoordinate2D move;
    uint8_t heuristic;

public:
    Node(Board *, int);

    uint8_t getHeuristic();
    bool isLeaf();
    size_t getLength();
    Node * getNodeAt(int);
    CGCoordinate2D getMove();
    void setHeuristic(uint8_t);
};

#endif

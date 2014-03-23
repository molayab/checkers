#include "minimax.h"
#include <algorithm>

uint8_t Minimax::heuristic[8][8] =
    {{3,3,3,3,3,3,3,3},
    {3,2,2,2,2,2,2,3},
    {3,2,1,1,1,1,2,3},
    {3,2,1,0,0,1,2,3},
    {3,2,1,0,0,1,2,3},
    {3,2,1,1,1,1,2,3},
    {3,2,2,2,2,2,2,3},
    {3,3,3,3,3,3,3,3}};

Minimax::Minimax(Board board) {
    root = new Node(&board, 8);
}

Minimax::~Minimax() {

}

CGCoordinate2D Minimax::run() {
    minmax_t mm = minimax(root, 8, true);

    printf("HOLA ?? %d", mm.heuristc);
}

minmax_t Minimax::minimax(Node * node, unsigned int depth, bool isMax) {
    if (depth == 0 || node->isLeaf()) {
        node->setHeuristic(getHeuristic(node->getMove()));

        minmax_t ret;
        ret.node = node;
        ret.heuristc = node->getHeuristic();

        return ret;
    }

    if (isMax) {
        uint8_t best = INT8_MAX;

        for (int i = 0; i < node->getLength(); ++i) {
            minmax_t val = minimax(node->getNodeAt(i), depth - 1, true);
            best = std::min(best, val.heuristc);
        }

        minmax_t ret;
        ret.node = node;
        ret.heuristc = best;

        return ret;
    } else {
        uint8_t best = INT8_MIN;

        for (int i = 0; i < node->getLength(); ++i) {
            minmax_t val = minimax(node->getNodeAt(i), depth - 1, false);
            best = std::max(best, val.heuristc);
        }

        minmax_t ret;
        ret.node = node;
        ret.heuristc = best;

        return ret;
    }
}

uint8_t Minimax::getHeuristic(CGCoordinate2D coor) {
    if (coor.x < 8 && coor.y < 8) return heuristic[coor.x][coor.y];
    return 0;
}

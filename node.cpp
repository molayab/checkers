#include "node.h"
#include "minimax.h"
#include "game.h"

//Node::Node(Board * board, int depht) {
//    Game * context = Game::instance();

//    for (size_t i = 0, d = 0; i < board->getRows() && d < depht; ++i, ++d) {
//        for (size_t j = 0; j < board->getColumns(); ++j) {
//            token_t token = board->getDataAt(i, j);
//            if (token == NIL || token == WHITE) continue;

//            CGCoordinate2D m;
//            m.x = i;
//            m.y = j;

//            std::vector<CGCoordinate2D> moves = context->getPossibleMoves(m);

//            printf("i: %d, j: %d, size: %d\n", i, j, moves.size());

//            for (size_t k = 0; k < moves.size(); ++k) {
//                Board * newBoard = board;
//                newBoard->setDataAt(i, j, NIL);
//                newBoard->setDataAt(moves[k].x, moves[k].y, token);

//                move = moves[k];
//                //this->board = newBoard;
//                //heuristic = Minimax::getHeuristic(moves[k]);
//                printf("--> move: x: %d, y: %d\n", moves[k].x, moves[k].y);

//                childs.push_back(new Node(newBoard, depht - 1));
//            }
//        }
//    }

//}

Node::Node(Board * board, int depth) {
    if (depth < 8) {
        Game * context = Game::instance();

        for (unsigned int i = 0; i < board->getColumns(); ++i) {
            //printf("hola?? %d", i);

            token_t token = board->getDataAt(depth, i);
            if (context->getTokenKind(token) == BLACK) {
                CGCoordinate2D m;
                m.x = depth;
                m.y = i;

                std::vector<CGCoordinate2D> moves = context->getPossibleMoves(m);

                printf("i: %d, j: %d, size: %d\n", depth, i, moves.size());

                for (size_t j = 0; j < moves.size(); ++j) {
                    board->setDataAt(depth, i, NIL);
                    board->setDataAt(moves[j].x, moves[j].y, token);

                    childs.push_back(Node(board, depth + 1));
                }
            }
        }

        childs.push_back(Node(board, depth + 1));
    }
}

uint8_t Node::getHeuristic() {
    return this->heuristic;
}

bool Node::isLeaf() {
    return (this->childs.size() == 0);
}

size_t Node::getLength() {
    return this->childs.size();
}

Node * Node::getNodeAt(int index) {
    return &childs.at(index);
}

CGCoordinate2D Node::getMove() {
    return move;
}

void Node::setHeuristic(uint8_t h) {
    heuristic = h;
}

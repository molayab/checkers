#include "game.h"

Game * Game::m_inst = NULL;

Game::Game() {
    board = new Board(ROWS, COLS);

    init();
}

Game * Game::instance() {
    if (!m_inst) m_inst = new Game();

    return m_inst;
}

Game::~Game() {
    delete board;
}

void Game::init() {
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            if ((i % 2 == 0 && j % 2 > 0) || (i % 2 > 0 && j % 2 == 0)) {
                if (i < 3) board->setDataAt(i, j, BLACK);
                else if (i > 4) board->setDataAt(i, j, WHITE);
                else board->setDataAt(i, j, NIL);
            }
        }
    }

    turn = 0;
}

Board * Game::getBoard() const {
    return board;
}

bool Game::play(const CGCoordinate2D from, const CGCoordinate2D to) {
    token_t token = board->getDataAt(from.x, from.y);
    turn++;

    if(isValid(from, to)) {
        perform(from, to);

       Node n(board, 0);
       printf("%d", n.getLength());

        return true;
    }

    return false;
}

bool Game::isValid(const CGCoordinate2D from, const CGCoordinate2D to, bool isEat) {
    /*
   * REGLAS DEL JUEGO
   */

    token_t tokenFrom = board->getDataAt(from.x, from.y);
    token_t tokenTo   = board->getDataAt(to.x, to.y);

    if (from == to) return false;
    if (from.x < 0 || to.x < 0) return false;
    if (from.y < 0 || to.y < 0) return false;
    if (from.x >= ROWS || to.x >= ROWS) return false;
    if (from.y >= ROWS || to.y >= ROWS) return false;
    if (tokenFrom == NIL) return false;

    if (tokenTo == NIL) {

      /*
       * Movimiento basico
       */

        if (isKing(tokenFrom) && abs(from.x - to.x) == 1) {
            if (abs(from.x - to.x) == 1 && from.y != to.y) {
                return true;
            }
        } else if (abs(from.x - to.x) == 1) {
            token_t token = getTokenKind(tokenFrom);

            if (token == WHITE) {
                if ((from.x - to.x) > 0 && from.y != to.y) {
                    return true;
                }
            } else {
                if ((from.x - to.x) < 0 && from.y != to.y) {
                    return true;
                }
            }
        }


      /*
       * Movimiento comiendo
       */

        if (!isKing(tokenFrom)) { 
            if (abs(from.x - to.x) == 2 && from.y != to.y) {
                CGCoordinate2D tmp = from;

                if (getTokenKind(tokenFrom) == WHITE) {
                    if (to.x > from.x) return false;
                } else {
                    if (to.x < from.x) return false;
                }

                switch(getJumpKind(from, to)) {
                case RIGHT:
                    if (getTokenKind(tokenFrom) == BLACK) {
                        tmp.x++;
                        tmp.y--;
                    } else if (getTokenKind(tokenFrom) == WHITE) {
                        tmp.x--;
                        tmp.y++;
                    }
                    break;
                case LEFT:
                    if (getTokenKind(tokenFrom) == BLACK) {
                        tmp.x++;
                        tmp.y++;
                    } else if (getTokenKind(tokenFrom) == WHITE) {
                        tmp.x--;
                        tmp.y--;
                    }
                    break;
                default:
                    break;
                }

                token_t token = board->getDataAt(tmp.x, tmp.y);

                if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                    if (isEat) eat(tmp);
                    return true;
                }
            }
        } else {
            if (abs(from.x - to.x) == 2 && from.y != to.y) {
                CGCoordinate2D tmp = from;
                CGCoordinate2D tmpInverse = from;

                token_t token;
                token_t tokenInverse;

                switch(getJumpKind(from, to)) {
                case RIGHT:

                        tmp.x++;
                        tmp.y--;

                        tmpInverse.x++;
                        tmpInverse.y++;

                        token = board->getDataAt(tmp.x, tmp.y);
                        tokenInverse = board->getDataAt(tmpInverse.x, tmpInverse.y);

                        if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                            if (isEat) eat(tmp);
                            return true;
                        }

                        if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {

                            if (isEat) eat(tmp);
                            return true;
                        }

                        tmp.x--;
                        tmp.y++;

                        tmpInverse.x--;
                        tmpInverse.y--;

                        token = board->getDataAt(tmp.x, tmp.y);
                        tokenInverse = board->getDataAt(tmpInverse.x, tmpInverse.y);

                        if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                            if (isEat) eat(tmp);
                            return true;
                        }

                        if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {
                            if (isEat) eat(tmp);

                            return true;
                        }

                    break;
                case LEFT:

                        tmp.x++;
                        tmp.y++;

                        tmpInverse.x--;
                        tmpInverse.y++;

                        token = board->getDataAt(tmp.x, tmp.y);
                        tokenInverse = board->getDataAt(tmpInverse.x, tmpInverse.y);

                        if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                            if (isEat) eat(tmp);
                            return true;
                        }

                        if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {

                            if (isEat) eat(tmp);
                            return true;
                        }

                        tmp.x--;
                        tmp.y--;

                        tmpInverse.x++;
                        tmpInverse.y--;

                        token = board->getDataAt(tmp.x, tmp.y);
                        tokenInverse = board->getDataAt(tmpInverse.x, tmpInverse.y);

                        if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                            if (isEat) eat(tmp);
                            return true;
                        }

                        if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {

                            if (isEat) eat(tmp);
                            return true;
                        }
                    break;
                default:
                    break;
                }
            }
        }
    }

    return false;
}

jump_t Game::getJumpKind(const CGCoordinate2D from, const CGCoordinate2D to) {
    if (from.x > to.x) {
        if (from.y > to.y) return LEFT;
        else if (from.y < to.y) return RIGHT;
        else return SAME;
    } else {
        if (from.y < to.y) return LEFT;
        else if (from.y > to.y) return RIGHT;
        else return SAME;
    }
}

bool Game::isKing(const token_t token) {
    /*
   * Comparamos si es reina, movemos 4 bits a la
   * izquierda y de estos solo leemos 8 bits que
   * si corresponden a 0b11110000 o 0xF0 quiere
   * decir que es una reina.
   */

    return (((token << 4) & 0xFF) == 0xF0);
}

token_t Game::getTokenKind(const token_t token) {
    return (token_t)(token & 0xF0);
}

token_t Game::getOppositeToken(const token_t token) {
    return (token_t)(~token & 0xF0);
}

void Game::perform(const CGCoordinate2D from, const CGCoordinate2D to)
{
    token_t tmp = board->getDataAt(from.x, from.y);
    board->setDataAt(from.x, from.y, NIL);
    board->setDataAt(to.x, to.y, tmp);

    if (to.x == 0 || to.x == ROWS - 1) {
        crown(to);
    }
}

void Game::eat(const CGCoordinate2D token) {
    board->setDataAt(token.x, token.y, NIL);
}

void Game::crown(const CGCoordinate2D token) {
    token_t crown = (token_t)(board->getDataAt(token.x, token.y) | 0x0F);

    board->setDataAt(token.x, token.y, crown);
}

std::vector<CGCoordinate2D> Game::getPossibleMoves(const CGCoordinate2D coor) {
    std::vector<CGCoordinate2D> moves;
    CGCoordinate2D to;

    for (int i = 0, j = 0; i < 16; ++i) {
        int mod = i % 4;
        to = coor;

        if (mod == 0) {
            j++;
        }

        switch(mod) {
        case 1:
            to.x += j;
            to.y += j;
            break;
        case 2:
            to.x += j;
            to.y -= j;
            break;
        case 3:
            to.x -= j;
            to.y -= j;
            break;
        default:
            to.x -= j;
            to.y += j;
            break;
        }

        if (isValid(coor, to, false)) {
            moves.push_back(to);
        }  
    }

    return moves;
}

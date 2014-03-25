#include "game.h"
#include "node.h"
#include "minimax.h"
#include <sstream>
#include <time.h>

Game * Game::m_inst = NULL;

Game::Game() : board(ROWS, COLS) {
    //board = Board(ROWS, COLS);
    init();
}

Game * Game::instance() {
    if (!m_inst) m_inst = new Game();

    return m_inst;
}

Game::~Game() {
    //delete board;
}

void Game::init() {
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            if ((i % 2 == 0 && j % 2 > 0) || (i % 2 > 0 && j % 2 == 0)) {
                if (i < 3) board.setDataAt(i, j, BLACK);
                else if (i > 4) board.setDataAt(i, j, WHITE);
                else board.setDataAt(i, j, NIL);
            }
        }
    }

    turn = 0;
    blackp = 12;
    whitep = 12;
    history_stack.clear();
}

Board * Game::getBoard() {
    return &board;
}

bool Game::play(const CGCoordinate2D from, const CGCoordinate2D to) {
    if(isValid(from, to)) {
        perform(from, to);
        ++turn;

        if (whitep == 0) {
            if (delegate) {
                delegate->didWonGame(this, PLAYER2);
            }
        }

        if (blackp == 0) {
            if (delegate) {
                delegate->didWonGame(this, PLAYER1);
            }
        }

        if ((turn % 2) > 0) {
            compute();
        }

        return true;
    }

    return false;
}

bool Game::isValid(const CGCoordinate2D from, const CGCoordinate2D to, bool isEat, bool trace) {
    /*
   * REGLAS DEL JUEGO
   */

    token_t tokenFrom = board.getDataAt(from.x, from.y);
    token_t tokenTo   = board.getDataAt(to.x, to.y);

    if (from == to) return false;
    if (from.x < 0 || to.x < 0) return false;
    if (from.y < 0 || to.y < 0) return false;
    if (from.x >= ROWS || to.x >= ROWS) return false;
    if (from.y >= ROWS || to.y >= ROWS) return false;
    if (tokenFrom == NIL) return false;
    if (tokenTo != NIL) return false;



    /*
       * Movimiento basico
       */

    if (isKing(tokenFrom) && abs(from.x - to.x) == 1) {
        if (abs(from.x - to.x) == 1 && from.y != to.y) {
            if (trace) {
                history(from, to);
            }

            return true;
        }
    } else if (abs(from.x - to.x) == 1) {
        token_t token = getTokenKind(tokenFrom);

        if (token == WHITE) {
            if ((from.x - to.x) > 0 && from.y != to.y) {
                if (trace) {
                    history(from, to);
                }

                return true;
            }
        } else {
            if ((from.x - to.x) < 0 && from.y != to.y) {
                if (trace) {
                    history(from, to);
                }

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

            token_t token = board.getDataAt(tmp.x, tmp.y);

            if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                if (isEat) {
                    if (trace) {
                        history(from, to, true);
                    }

                    eat(tmp);
                    --turn;
                } else {
                    if (trace) {
                        history(from, to);
                    }
                }
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

                token = board.getDataAt(tmp.x, tmp.y);
                tokenInverse = board.getDataAt(tmpInverse.x, tmpInverse.y);

                if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }
                    return true;
                }

                if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {

                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }
                    return true;
                }

                tmp.x--;
                tmp.y++;

                tmpInverse.x--;
                tmpInverse.y--;

                token = board.getDataAt(tmp.x, tmp.y);
                tokenInverse = board.getDataAt(tmpInverse.x, tmpInverse.y);

                if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }
                    return true;
                }

                if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {
                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }

                    return true;
                }

                break;
            case LEFT:

                tmp.x++;
                tmp.y++;

                tmpInverse.x--;
                tmpInverse.y++;

                token = board.getDataAt(tmp.x, tmp.y);
                tokenInverse = board.getDataAt(tmpInverse.x, tmpInverse.y);

                if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }
                    return true;
                }

                if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {

                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }
                    return true;
                }

                tmp.x--;
                tmp.y--;

                tmpInverse.x++;
                tmpInverse.y--;

                token = board.getDataAt(tmp.x, tmp.y);
                tokenInverse = board.getDataAt(tmpInverse.x, tmpInverse.y);

                if (getTokenKind(getOppositeToken(token)) == getTokenKind(tokenFrom)) {

                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }
                    return true;
                }

                if (getTokenKind(getOppositeToken(tokenInverse)) == getTokenKind(tokenFrom)) {

                    if (isEat) {
                        if (trace) {
                            history(from, to, true);
                        }

                        eat(tmp);
                        --turn;
                    } else {
                        if (trace) {
                            history(from, to);
                        }
                    }
                    return true;
                }
                break;
            default:
                break;
            }
        }
    }


    return false;
}

jump_t Game::getJumpKind(const CGCoordinate2D from, const CGCoordinate2D to) {
    token_t token = getTokenKind(board.getDataAt(from.x, from.y));

    if (token == WHITE) {
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
    if (token != NIL) {
        return (token_t)(~token & 0xF0);
    }

    return NIL;
}

void Game::perform(const CGCoordinate2D from, const CGCoordinate2D to)
{
    token_t tmp = board.getDataAt(from.x, from.y);
    board.setDataAt(from.x, from.y, NIL);
    board.setDataAt(to.x, to.y, tmp);

    if (to.x == 0 || to.x == ROWS - 1) {
        history(from, to, false, true);
        crown(to);
    }
}

void Game::history(CGCoordinate2D from, CGCoordinate2D to, bool eat, bool crown) {
    std::stringstream stream;
    if (eat) {
        stream << "C ";
    }
    stream << (from.x + 1) << (from.y + 1);
    stream << " ";
    stream << (to.x + 1) << (to.y + 1);

    if (crown) {
        stream << " R";
    }

    history_t h;
    h.move = stream.str();
    h.player = ((turn % 2 == 0) ? "JUGADOR1" : "CPU");

    history_stack.push_back(h);
}

void Game::eat(const CGCoordinate2D token) {
    token_t kind = getTokenKind(board.getDataAt(token.x, token.y));

    if (kind == BLACK) {
        --blackp;
    } else {
        --whitep;
    }

    if (delegate) {
        delegate->didChangeScore(this, whitep, blackp);
    }

    board.setDataAt(token.x, token.y, NIL);
}

void Game::crown(const CGCoordinate2D token) {
    token_t crown = (token_t)(board.getDataAt(token.x, token.y) | 0x0F);

    board.setDataAt(token.x, token.y, crown);
}

std::vector<CGCoordinate2D> Game::getPossibleMoves(const CGCoordinate2D coor, bool onlyEat) {
    std::vector<CGCoordinate2D> moves;
    CGCoordinate2D to;

    token_t token = board.getDataAt(coor.x, coor.y);

    if (token != NIL) {
        for (int i = 0, j = 0; i < 8; ++i) {
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

            if (isValid(coor, to, false, false)) {
                if (onlyEat) {
                    if (j == 2) {
                        moves.push_back(to);
                    }
                } else {
                    moves.push_back(to);
                }

            }
        }
    }

    return moves;
}

std::vector<moves_t> Game::getAllPosiiblesMoves(Board * board) {
    std::vector<moves_t> ret;

    if (board != NULL) {
        for (int i = 0; i < board->getRows(); ++i) {
            for (int j = 0; j < board->getColumns(); ++j) {
                token_t token = board->getDataAt(i, j);

                if (token != NIL) {
                    moves_t move;

                    CGCoordinate2D coor;
                    coor.x = i;
                    coor.y = j;

                    move.inital = coor;
                    move.moves = getPossibleMoves(coor);

                    ret.push_back(move);
                }
            }
        }
    }

    return ret;
}

void Game::compute() {
    CGCoordinate2D bestx, besty;
    int heuristic = 0;

    struct wait {
        void operator()(double t)
        {
            clock_t endwait;
            endwait = clock () + t * CLOCKS_PER_SEC ;
            while (clock() < endwait);
        }
    } wait;

    for (int i = 0; i < board.getRows(); ++i) {
        for (int j = 0; j < board.getColumns(); ++j) {
            if (getTokenKind(board.getDataAt(i, j)) == BLACK) {
                CGCoordinate2D move;
                move.x = i;
                move.y = j;

                std::vector<CGCoordinate2D> eats = getPossibleMoves(move, true);

                for (CGCoordinate2D coor : eats) {
                    if (play(move, coor)) {
                        wait(0.05);
                        return;
                    }
                }
            }
        }
    }

    for (int i = 0; i < board.getRows(); ++i) {
        for (int j = 0; j < board.getColumns(); ++j) {
            if (getTokenKind(board.getDataAt(i, j)) == BLACK) {
                CGCoordinate2D move;
                move.x = i;
                move.y = j;

                std::vector<CGCoordinate2D> candidates = getPossibleMoves(move);

                for (CGCoordinate2D coor : candidates) {
                    if (Minimax::getHeuristic(coor) > heuristic) {
                        bestx = move;
                        besty = coor;

                        heuristic = Minimax::getHeuristic(coor);
                    }
                }
            }
        }
    }

    wait(0.05);
    play(bestx, besty);
}

std::vector<history_t> Game::getHistory() {
    return history_stack;
}

uint8_t Game::getTurn() {
    return turn;
}

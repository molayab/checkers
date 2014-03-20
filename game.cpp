#include "game.h"

Game::Game() {
	board = new Board(8, 8);

	init();
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
}

Board * Game::getBoard() const {
	return board;
}

bool Game::play(const CGCoordinate2D from, const CGCoordinate2D to) {
  if(isValid(from, to)) {
    perform(from, to);

    return true;
  }

  return false;
}

bool Game::isValid(const CGCoordinate2D from, const CGCoordinate2D to) {
  /*
   * REGLAS DEL JUEGO
   */

  token_t tokenFrom = board->getDataAt(from.x, from.y);
  token_t tokenTo   = board->getDataAt(to.x, to.y);

  if (from == to) return false;

  if (!isKing(tokenFrom) && tokenTo == NIL) {
    if (abs(from.x - to.x) == 1 && from.y != to.y) {
      return true;
    }

    if (abs(from.x - to.x) == 2 && from.y != to.y) {
      CGCoordinate2D tmp = to;

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
            tmp.x--;
            tmp.y--;

          } else if (getTokenKind(tokenFrom) == WHITE) {
            tmp.x++;
            tmp.y++;

          }
          break;
        default:
          break;
      }

      token_t token = board->getDataAt(tmp.x, tmp.y);
      return (getOppositeToken(token) != tokenFrom);
    }
  }
  
  return false;
}

jump_t Game::getJumpKind(const CGCoordinate2D from, const CGCoordinate2D to) {
  if (from.y > to.y) return LEFT;
  else if (from.y < to.y) return RIGHT;
  else return SAME;
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
  return (token_t)((token >> 4) << 4);
}

token_t Game::getOppositeToken(const token_t token) {
  return (token_t)(~token & 0xF0);
}

void Game::perform(const CGCoordinate2D from, const CGCoordinate2D to , bool eat) {
  if (!eat) {
    token_t tmp = board->getDataAt(from.x, from.y);
    board->setDataAt(to.x, to.y, tmp);
  } else {

  }
}
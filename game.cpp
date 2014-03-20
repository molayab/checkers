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
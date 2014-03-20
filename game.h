#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <cstdint>

#define ROWS 8
#define COLS 8

class Game {
	Board * board;
	uint8_t turn;

public:
	Game();
	~Game();

	void init();
	bool play();
	void autoPlay();
	Board * getBoard() const;
};

#endif
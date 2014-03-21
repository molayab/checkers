#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <cstdint>
#include <cstdlib>

#define ROWS 8
#define COLS 8

struct CGCoordinate2D {
	long x; // ROWS
	long y; // COLS

	bool operator==(const CGCoordinate2D &c) const {
		return (x == c.x && y == c.y);
	}
};

typedef enum jump_t {
	RIGHT,
	LEFT,
	SAME
} jump_t;

class Game {
	Board * board;
	uint8_t turn;

	void perform(const CGCoordinate2D, const CGCoordinate2D, bool=false);

public:
	Game();
	~Game();

	void init();
	void autoPlay();
	bool play(const CGCoordinate2D, const CGCoordinate2D);
	bool isValid(const CGCoordinate2D, const CGCoordinate2D);
	bool isKing(const token_t);
	token_t getTokenKind(const token_t);
	token_t getOppositeToken(const token_t);
	jump_t getJumpKind(const CGCoordinate2D, const CGCoordinate2D);
	Board * getBoard() const;
};

#endif

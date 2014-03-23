#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "minimax.h"
#include <cstdint>
#include <cstdlib>
#include <vector>

#define ROWS 8
#define COLS 8

typedef enum jump_t {
	RIGHT,
	LEFT,
	SAME
} jump_t;

class Game {
    static Game * m_inst;
	Board * board;
	uint8_t turn;

    void perform(const CGCoordinate2D, const CGCoordinate2D);
    void eat(const CGCoordinate2D);

protected:
    Game();
    ~Game();

public:
    static Game * instance();

	void init();
	void autoPlay();
	bool play(const CGCoordinate2D, const CGCoordinate2D);
    bool isValid(const CGCoordinate2D, const CGCoordinate2D, bool=true);
	bool isKing(const token_t);
	token_t getTokenKind(const token_t);
	token_t getOppositeToken(const token_t);
    jump_t getJumpKind(const CGCoordinate2D, const CGCoordinate2D);
	Board * getBoard() const;
    void crown(const CGCoordinate2D);
    std::vector<CGCoordinate2D> getPossibleMoves(const CGCoordinate2D);
};

#endif

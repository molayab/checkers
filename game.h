#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "struct.h"
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>

#define ROWS 8
#define COLS 8

typedef enum jump_t {
	RIGHT,
	LEFT,
	SAME
} jump_t;

struct moves_t {
    CGCoordinate2D inital;
    std::vector<CGCoordinate2D> moves;
};

typedef enum player_t {
    PLAYER1 = 0x00,
    PLAYER2 = 0xFF
} player_t;


struct history_t {
    std::string move;
    std::string player;
};

class Game;

class GameDelegate {
public:
    virtual void didWonGame(Game *, player_t) = 0;
    virtual void didChangeScore(Game *, uint8_t, uint8_t) = 0;
};

class Game {
    static Game * m_inst;
    Board board;
	uint8_t turn;
    uint8_t whitep;
    uint8_t blackp;

    std::vector<history_t> history_stack;

    void perform(const CGCoordinate2D, const CGCoordinate2D);
    void eat(const CGCoordinate2D);
    void history(CGCoordinate2D, CGCoordinate2D, bool=false, bool=false);

protected:
    Game();
    ~Game();

public:
    static Game * instance();
    GameDelegate * delegate;

	void init();
	void autoPlay();
    bool play(const CGCoordinate2D, const CGCoordinate2D);
    bool isValid(const CGCoordinate2D, const CGCoordinate2D, bool=true, bool=true);
	bool isKing(const token_t);
	token_t getTokenKind(const token_t);
	token_t getOppositeToken(const token_t);
    jump_t getJumpKind(const CGCoordinate2D, const CGCoordinate2D);
    Board * getBoard();
    void crown(const CGCoordinate2D);
    std::vector<CGCoordinate2D> getPossibleMoves(const CGCoordinate2D, bool=false);
    std::vector<moves_t> getAllPosiiblesMoves(Board *);
    void compute();
    std::vector<history_t> getHistory();
    uint8_t getTurn();
};

#endif

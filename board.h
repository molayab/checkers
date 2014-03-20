#ifndef BOARD_H
#define BOARD_H

typedef enum token_t {
	WHITE = 0xA0,
	BLACK = 0xB0,
	WHITE_KING = 0xAF,
	BLACK_KING = 0xBF,
	NIL = 0x0
} token_t;

class Board {
	token_t ** data;
	unsigned int rows;
	unsigned int columns;

public:
	Board(unsigned int, unsigned int);
	~Board();

	void setDataAt(unsigned int, unsigned int, token_t);
	token_t getDataAt(unsigned int, unsigned int) const;
	token_t ** getContext() const;
};

#endif
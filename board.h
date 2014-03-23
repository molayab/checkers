#ifndef BOARD_H
#define BOARD_H

typedef enum token_t {
	WHITE = 0xA0, 		// BIN 1010 0000
	BLACK = 0x50, 		// BIN 0101 0000
	WHITE_KING = 0xAF,	// BIN 1010 1111
	BLACK_KING = 0x5F,	// BIN 0101 1111
	NIL = 0x00          // BIN 0000 0000
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
    unsigned int getRows();
    unsigned int getColumns();
};

#endif

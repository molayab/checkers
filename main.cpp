#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char * argv[]) {
	Game g;

	CGCoordinate2D from;
	from.x = 5;
	from.y = 0;

	CGCoordinate2D to;
	to.x = 5;
	to.y = 0;
	
	cout << g.getOppositeToken(BLACK) << endl;

	Board * b = g.getBoard();

	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			cout << b->getDataAt(i, j) << " ";
		}

		cout << endl;
	}

	return 0;
}
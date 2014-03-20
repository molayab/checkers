#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char * argv[]) {
	Game g;

	Board * b = g.getBoard();

	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			cout << b->getDataAt(i, j) << " ";
		}

		cout << endl;
	}

	return 0;
}
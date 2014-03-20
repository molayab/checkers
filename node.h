#ifndef NODE_H
#define NODE_H

#include <cstdlib>
#include "board.h"

class Node {
	Board * value;
	Node * child[];
	unsigned long size;
	unsigned long length;

public:
	Node(unsigned long size);
	~Node();

	void add(Board * value);
	Board * value();
};

#endif
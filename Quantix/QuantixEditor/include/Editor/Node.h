#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "Type.h"

struct Node
{
	std::vector<Node>			child;
	QXstring					name;
	QXuint						id;
	QXbool						state;
};

#endif _NODE_H_
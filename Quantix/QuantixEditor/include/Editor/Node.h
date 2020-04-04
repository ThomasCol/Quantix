#ifndef _NODE_H_
#define _NODE_H_

#include <vector>

struct Node
{
	std::vector<Node>			child;
	std::string					name;
	unsigned int				id;
	bool						state;
};

#endif _NODE_H_
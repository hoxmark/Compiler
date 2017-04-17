#ifndef _MAX_HPP
#define _MAX_HPP

#include "tree.hpp"
#include <limits>

// You will need to implement a complete visitor that
// finds the maximum element in the tree. You can use
// the print and sum visitors for reference.

// WRITEME
class MaxVisitor : public Visitor {
public:
	int max;
	//Setting max = -inf so it can do all negative ints. 
	MaxVisitor() : max(-(std::numeric_limits<int>::max())) {}
	void visitNode(Node* node);
};

#endif

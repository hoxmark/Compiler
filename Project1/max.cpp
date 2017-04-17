#include "max.hpp"
#include <iostream>

// You will need to implement a complete visitor that
// finds the maximum element in the tree. You can use
// the print and sum visitors for reference.

// WRITEME
void MaxVisitor::visitNode(Node* node) {

	if (node->value > max){
        max = node->value;
    }
	node->visit_children(this);
}
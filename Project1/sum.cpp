#include "sum.hpp"
#include <iostream>


void SumVisitor::visitNode(Node* node) {
	// Hint: for this function, you will need to to use the sum
	// member of the object.
	sum = sum + node->value;
	// std::cout << "node: ";
	// std::cout << node->value << std:endl;
	// std::cout << sum << std::endl;
	node->visit_children(this);	
}

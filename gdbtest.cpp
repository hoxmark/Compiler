#include <iostream>

void otherFunction() {
	int* x = NULL;
	std::cout << *x << std::endl;
}

int main(int argc, char* argv[]) {
	otherFunction();
	return 0;
}
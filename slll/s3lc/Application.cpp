#include <iostream>
#include "Scanner.h"

int main(int argc, const char *argv[]) {
	std::cout << "Hello, World!" << std::endl;
	auto scanner = slll::Scanner("1+2*3");
	std::cout << scanner.NextToken() << std::endl;
	int i;
	std::cin >> i;
	return 0;
}
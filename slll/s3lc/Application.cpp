#include <iostream>
#include <fstream>

#include "Parser.h"
#include "GASVisitor.h"

int main(int argc, const char *argv[]) {
	slll::Parser p("res(a, b) { return a * b } test(b) { print2(1, b) } main() { test(res(12, 25)) } ");
	auto tree = p.Parse();

	std::ofstream file;
	file.open("out.S");

	slll::GASVisitor gas(file);
	//slll::GASVisitor gas(std::cout);
	tree->AcceptVisitor(&gas);

	file.close();

	std::system("pause");
	return 0;
}
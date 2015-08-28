#include <iostream>
#include <fstream>

#include "Parser.h"
#include "GASVisitor.h"

int main(int argc, const char *argv[]) {
	slll::Parser p(" { if 0 && 0 printi 1 if 0 && 1 printi 2 if 1 && 0 printi 3 if 1 && 1 printi 4  if 0 || 0 printi 5 if 0 || 1 printi 6 if 1 || 0 printi 7 if 1 || 1 printi 8 }");
	auto tree = p.Parse();

	std::ofstream file;
	file.open("out.S");

	slll::GASVisitor gas(file);
	//slll::GASVisitor gas(std::cout);
	gas.WriteProgramPrefix();
	tree->AcceptVisitor(&gas);
	gas.WriteProgramSuffix();

	file.close();

	std::system("pause");
	return 0;
}
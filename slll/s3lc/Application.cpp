#include <iostream>
#include <fstream>

#include "Parser.h"
#include "GASVisitor.h"

int main(int argc, const char *argv[]) {
	slll::Parser p("{ x1 := 5 x2 := 1 while x1 { x1 = x1 - 1 x3 := x2 while x3 { x2 = x2 + x1 x3 = x3 - 1 } } printi x2 }");
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
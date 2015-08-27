#include <iostream>
#include <fstream>

#include "Parser.h"
#include "GASVisitor.h"

int main(int argc, const char *argv[]) {
	slll::Parser p("{ a := 1 printi a println { a:= 2 printi a println } printi a println }");
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
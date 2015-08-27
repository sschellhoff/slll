#include <iostream>
#include <fstream>

#include "Parser.h"
#include "GASVisitor.h"

int main(int argc, const char *argv[]) {
	slll::Parser p("{ a := 5 while a { printi a a = a - 1 } }");
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
#include <iostream>
#include <fstream>

#include "Parser.h"
#include "GASVisitor.h"

int main(int argc, const char *argv[]) {
	slll::Parser p("square(a) { return a * a } pow(a, b) { result := 1 while b > 0 { result = result * a b = b - 1 } return result } main() { print_int(square(1337)) print_nl() print_int(pow(5, 3)) print_nl() print2(5, 3) } ");
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
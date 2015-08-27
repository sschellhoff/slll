#include "Variable.h"

using namespace slll;

unsigned int Variable::NextId = 0;

Variable::Variable(std::string name, size_t size):id(Variable::NextId++), name(name), size(size)
{
}


Variable::~Variable()
{
}

Variable::Variable(const Variable &var) :id(var.id), name(var.name), size(var.size) {
}

const std::string &Variable::Name()const {
	return name;
}

unsigned int Variable::Id()const {
	return id;
}

size_t Variable::Size()const {
	return size;
}

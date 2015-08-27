#include "Environment.h"
#include "VariableNotFoundExeption.h"

using namespace slll;

Environment::Environment(Environment *parent):parent(parent)
{
}


Environment::~Environment()
{
}

bool Environment::ExistsInScope(unsigned int id)const {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if ((*it).Id() == id) {
			return true;
		}
	}
	if(parent == nullptr) {
		return false;
	}
	return parent->ExistsInScope(id);
}

bool Environment::ExistsInScope(std::string name)const {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if ((*it).Name() == name) {
			return true;
		}
	}
	if (parent == nullptr) {
		return false;
	}
	return parent->ExistsInScope(name);
}

bool Environment::Contains(std::string name)const {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if ((*it).Name() == name) {
			return true;
		}
	}
	return false;
}

bool Environment::Contains(unsigned int id)const {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if ((*it).Id() == id) {
			return true;
		}
	}
	return false;
}

unsigned int Environment::AddVariable(std::string name, size_t size) {
	variables.push_back(Variable(name, size));
	return (variables.end() - 1)->Id();
}

unsigned int Environment::GetId(std::string name)const {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if ((*it).Name() == name) {
			return (*it).Id();
		}
	}
	if (parent == nullptr) {
		throw VariableNotFoundExeption();
	}
	return parent->GetId(name);
}

size_t Environment::GetSize()const {
	size_t size = 0;
	for (auto it = variables.begin(); it != variables.end(); it++) {
		size += (*it).Size();
	}
	return size;
}

size_t Environment::GetSizeFromParents()const {
	if (parent != nullptr) {
		return parent->GetSize() + parent->GetSizeFromParents();
	}
	return 0;
}

int Environment::GetRelativeAdress(unsigned int id)const {
	if (Contains(id)) {
		unsigned int offset = GetSizeFromParents();

		for (auto it = variables.begin(); it != variables.end(); it++) {
			if ((*it).Id() == id) {
				return offset + (*it).Size();
			}
			else {
				offset += (*it).Size();
			}
		}
	}

	if (parent == nullptr) {
		throw VariableNotFoundExeption();
	}

	return parent->GetRelativeAdress(id);
}

#include "VariablesEnvironment.h"
#include "VariableNotFoundExeption.h"

using namespace slll;

VariablesEnvironment::VariablesEnvironment(VariablesEnvironment *parent):parent(parent), isParameterEnvironment(false)
{
}


VariablesEnvironment::VariablesEnvironment(VariablesEnvironment *parent, bool isParamEnv) :parent(parent), isParameterEnvironment(isParamEnv) {
}

VariablesEnvironment::~VariablesEnvironment()
{
}

bool VariablesEnvironment::ExistsInScope(unsigned int id)const {
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

bool VariablesEnvironment::ExistsInScope(std::string name)const {
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

bool VariablesEnvironment::Contains(std::string name)const {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if ((*it).Name() == name) {
			return true;
		}
	}
	return false;
}

bool VariablesEnvironment::Contains(unsigned int id)const {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if ((*it).Id() == id) {
			return true;
		}
	}
	return false;
}

unsigned int VariablesEnvironment::AddVariable(std::string name, size_t size) {
	variables.push_back(Variable(name, size));
	return (variables.end() - 1)->Id();
}

unsigned int VariablesEnvironment::GetId(std::string name)const {
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

size_t VariablesEnvironment::GetSize()const {
	size_t size = 0;
	for (auto it = variables.begin(); it != variables.end(); it++) {
		size += (*it).Size();
	}
	return size;
}

size_t VariablesEnvironment::GetSizeFromParentsWithoutParamEnv()const {
	if (parent != nullptr) {
		return parent->GetSize() + parent->GetSizeFromParentsWithoutParamEnv();
	}
	return 0;
}

int VariablesEnvironment::GetRelativeAdress(unsigned int id)const {
	if (IsParameter(id)) {
		return GetRelativeAdressOfParameter(id);
	}
	if (Contains(id)) {
		unsigned int offset = GetSizeFromParentsWithoutParamEnv();

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

int VariablesEnvironment::GetRelativeAdressOfParameter(unsigned int id)const {
	if (isParameterEnvironment && Contains(id)) {
		int offset = 4; //TODO maybe take constant for this, it is the size of ebp on the stack

		for (auto it = variables.rbegin(); it != variables.rend(); it++) {
			if ((*it).Id() == id) {
				return -(offset + (int)(*it).Size());
			} else {
				offset += (*it).Size();
			}
		}
	}

	if (parent == nullptr) {
		throw VariableNotFoundExeption();
	}

	return parent->GetRelativeAdressOfParameter(id);
}

bool VariablesEnvironment::IsParameterEnvironment()const {
	return isParameterEnvironment;
}

bool VariablesEnvironment::IsParameter(unsigned int id)const {
	if (Contains(id)) {
		return isParameterEnvironment;
	}
	if (parent != nullptr) {
		return parent->IsParameter(id);
	}
	throw VariableNotFoundExeption();
}
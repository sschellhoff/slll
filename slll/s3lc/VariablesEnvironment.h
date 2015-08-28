#pragma once

#include <string>
#include <vector>
#include "Variable.h"

namespace slll {

	class VariablesEnvironment
	{
	private:
		VariablesEnvironment *parent;
		std::vector<Variable> variables;
	public:
		VariablesEnvironment(VariablesEnvironment *parent);
		~VariablesEnvironment();
		bool ExistsInScope(unsigned int id)const;
		bool ExistsInScope(std::string name)const;
		bool Contains(std::string name)const;
		bool Contains(unsigned int id)const;
		unsigned int AddVariable(std::string name, size_t size);
		unsigned int GetId(std::string name)const;
		size_t GetSize()const;
		size_t GetSizeFromParents()const;
		int GetRelativeAdress(unsigned int id)const;
	};

}
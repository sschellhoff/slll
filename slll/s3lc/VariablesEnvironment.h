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
		bool isParameterEnvironment;
	public:
		VariablesEnvironment(VariablesEnvironment *parent);
		VariablesEnvironment(VariablesEnvironment *parent, bool isParamEnv);
		~VariablesEnvironment();
		bool ExistsInScope(unsigned int id)const;
		bool ExistsInScope(std::string name)const;
		bool Contains(std::string name)const;
		bool Contains(unsigned int id)const;
		unsigned int AddVariable(std::string name, size_t size);
		unsigned int GetId(std::string name)const;
		size_t GetSize()const;
		size_t GetSizeFromParentsWithoutParamEnv()const;
		int GetRelativeAdress(unsigned int id)const;
		int GetRelativeAdressOfParameter(unsigned int id)const;
		bool IsParameterEnvironment()const;
		bool IsParameter(unsigned int id)const;
	};

}
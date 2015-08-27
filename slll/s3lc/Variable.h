#pragma once

#include <string>

namespace slll {

	class Variable
	{
	private:
		size_t size;
		std::string name;
		unsigned int id;

		static unsigned int NextId;
	public:
		Variable(std::string name, size_t size);
		~Variable();
		Variable(const Variable &var);
		const std::string &Name()const;
		unsigned int Id()const;
		size_t Size()const;
	};

}
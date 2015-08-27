#pragma once

#include <exception>

namespace slll {

	class ParseException : public std::exception
	{
	private:
		const char *msg;
	public:
		ParseException();
		ParseException(const char* msg);
		virtual ~ParseException() throw();

		virtual const char* what() const throw ();
	};

}
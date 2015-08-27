#include "ParseException.h"

using namespace slll;

ParseException::ParseException()
{
	msg = "";
}

ParseException::ParseException(const char* msg):msg(msg) {
}

ParseException::~ParseException()
{
}

const char* ParseException::what() const {
	return msg;
}
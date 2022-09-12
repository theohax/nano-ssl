#include "private/log/log.hpp"

#include <iostream>

namespace nanossl::prv
{

void log(const std::string_view& message)
{
	std::cout << message << "\n" << std::flush;
}

}

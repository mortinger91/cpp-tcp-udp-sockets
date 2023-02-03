#include "utility.h"

#include <sstream>
#include <iomanip>

namespace Utility
{
	std::string HelloWorld()
	{
		return "Hello World!";
	}


	std::string raw_bytes_to_hex(char* data, size_t size)
	{
		std::stringstream ss;
		ss << std::hex << std::setfill('0');
		for (size_t i = 0; data[i] != '\n' && i < size; ++i) 
		{
			ss << std::setw(2) << static_cast<int>(data[i]);
		}
		return ss.str();
	}
}

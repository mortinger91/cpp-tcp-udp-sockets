#pragma once

#include <string>

namespace Utility
{
	std::string rawBytesToHexString(char* data, size_t size);

	std::vector<char> rawBytesToHexVector(char* data, size_t size);
}

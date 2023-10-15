#pragma once

#include <string>
#include <vector>

namespace Utility
{
    std::string rawBytesToHexString(char* data, size_t size);

    std::vector<char> rawBytesToHexVector(char* data, size_t size);
}  // namespace Utility

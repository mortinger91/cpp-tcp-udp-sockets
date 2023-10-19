#pragma once

#include <string>
#include <vector>

namespace Utility
{
    std::string rawBytesToHexString(const std::string& data);

    std::vector<char> rawBytesToHexVector(char* data, size_t size);
}  // namespace Utility

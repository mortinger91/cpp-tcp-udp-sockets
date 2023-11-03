#include "utility.h"

#include <iomanip>
#include <sstream>

std::string Utility::rawBytesToHexString(const std::string& data)
{
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; data[i] != '\n' && i < data.length(); ++i)
    {
        ss << std::setw(2)
           << static_cast<uint32_t>(static_cast<uint8_t>(data[i]));
        ss << " ";
    }
    return ss.str();
}

std::vector<char> Utility::rawBytesToHexVector(char* data, size_t size)
{
    size_t hexVectorSize = size * 2 + 1;
    char hexStr[hexVectorSize];
    size_t i;
    for (i = 0; i < size; i++)
    {
        sprintf(hexStr + i * 2, "%02x", data[i]);
    }
    hexStr[i * 2] = 0;
    std::vector<char> hexVector;
    for (i = 0; i < hexVectorSize; i++)
    {
        hexVector.push_back(hexStr[i]);
    }
    hexVector.pop_back();
    return hexVector;
}

#include "test.h"

#include "../src/lib/utility.h"
#include <vector>
#include <iostream>
#include <string>

void testRawBytesToHexVector()
{
    char data[3] = {17, 10, 15};
    size_t size = 3;
    auto res = Utility::rawBytesToHexVector(data, size);
    std::vector<char> res2{'1', '1', '0', 'a', '0', 'l'};
    test::assertVectorContentIsEqual(res, res2);
}

int main()
{
    testRawBytesToHexVector();

    return 0;
}

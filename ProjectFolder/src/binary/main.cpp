// main.cpp: This file contains the 'main' function. Program execution begins and ends there.

#include "src/lib/utility.h"
#include "server.h"

int main()
{
	Server s(9000, Protocol::TCP);
	s.start();

	return 0;
}

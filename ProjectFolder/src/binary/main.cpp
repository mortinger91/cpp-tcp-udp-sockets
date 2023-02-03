// main.cpp: This file contains the 'main' function. Program execution begins and ends there.

#include "../lib/utility.h"
#include "../lib/server.h"

int main()
{
	Server s(9000, Protocol::TCP);
	s.start();

	return 0;
}

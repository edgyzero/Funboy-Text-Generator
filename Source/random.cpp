#include "random.h"

unsigned int calls = 0;

int fb::Random(const int& n)
{
	srand(time(NULL) * calls++);
	return rand() % n;
}
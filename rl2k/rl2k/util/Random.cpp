#include "Random.h"

int Random::Next(int min, int max)
{
	int r = rand() % (max - min + 1) + min;
	return r;
}

///rolls XdY die and returns the sum
///if zeroMin is false, X will be added to the result to
///simulate dice starting at 1
///runs in O(X) time
int Random::Dice(int x, int y, bool zeroMin = true)
{
	int sum = 0;
	for (int i = 0; i < x; i++)
	{
		int r = Next(0, y);
		sum += r;
	}
	//if you roll the minimum of 1 on all rolls, you have a minimum sum
	//equal to the number of die
	if (!zeroMin)
		sum += x;
	return sum;
}
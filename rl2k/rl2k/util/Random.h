#pragma once
#include <math.h>
#include <random>
using namespace std;
namespace Random
{
	int Next(int min, int max);
	int Dice(int count, int size, bool zeroMin);
};


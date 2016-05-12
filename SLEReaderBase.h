#pragma once
#include <string>
#include <vector>
#include "Fraction.h"

using namespace std;

class SLEReaderBase
{
public:
	virtual vector< vector<Fraction>> ReadSLEAugmentedMatrix() = 0;
	virtual ~SLEReaderBase() {}
};
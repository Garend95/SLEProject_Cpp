#pragma once
#include "SLEReaderBase.h"
#include <string>

class ConsoleSLEReader :
	public SLEReaderBase
{
private:
	int ReadIntegerInput(std::string errorMessage);
public:
	vector< vector<Fraction>> ReadSLEAugmentedMatrix();
};


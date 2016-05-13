#pragma once
#include <string>
#include <vector>
#include "Fraction.h"
#include "SLEContainer.h"

using namespace std;

class SLEReaderBase
{
public:
	virtual vector< SLEContainer> ReadSLEAugmentedMatrices() = 0;
	virtual ~SLEReaderBase() {}
};
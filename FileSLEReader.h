#pragma once
#include "SLEReaderBase.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class FileSLEReader :
	public SLEReaderBase
{
private:
	string _sleInputFilePath;
public:
	FileSLEReader(string sleInputFilePath);
	vector< SLEContainer> ReadSLEAugmentedMatrices();
};


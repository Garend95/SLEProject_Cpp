#include "FileSLEReader.h"



FileSLEReader::FileSLEReader(string sleInputFilePath)
{
	_sleInputFilePath = sleInputFilePath;
}

vector< vector<Fraction>> FileSLEReader::ReadSLEAugmentedMatrix()
{
	ifstream inputFileStream(_sleInputFilePath);
	if (!inputFileStream.is_open())
	{
		throw exception("Cannot open input file!");
	}
	vector< vector<Fraction>> augmentedMatrix;
	int lastFoundColumnCount = 0;
	string currentLine;
	while (getline(inputFileStream, currentLine))
	{
		currentLine += ' ';
		string currentFractionString;
		int currentRowFractionCount = 0;
		vector<Fraction> currentFractionRow;
		for (int i = 0; i < currentLine.length(); i++)
		{
			if (currentLine[i] == ' ')
			{
				currentRowFractionCount++;
				currentFractionRow.push_back(Fraction::ParseFraction(currentFractionString));
				currentFractionString = "";
			}
			else 
			{
				currentFractionString += currentLine[i];
			}
		}
		if (lastFoundColumnCount > 0)
		{
			if (currentRowFractionCount != lastFoundColumnCount)
			{
				throw exception("Invalid augmented matrix");
			}
		}
		else if (currentRowFractionCount < 2)
		{
			throw exception("Invalid augmented matrix");
		}
		else {
			lastFoundColumnCount = currentRowFractionCount;
		}
		augmentedMatrix.push_back(currentFractionRow);
	}
	inputFileStream.close();
	return augmentedMatrix;
}

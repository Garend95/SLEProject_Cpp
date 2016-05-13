#include "FileSLEReader.h"



FileSLEReader::FileSLEReader(string sleInputFilePath)
{
	_sleInputFilePath = sleInputFilePath;
}

vector< SLEContainer> FileSLEReader::ReadSLEAugmentedMatrices()
{
	ifstream inputFileStream(_sleInputFilePath);
	if (!inputFileStream.is_open())
	{
		throw exception("Cannot open input file!");
	}
	bool allSLEsRead = false;
	vector< SLEContainer> sleContainers;
	vector< vector<Fraction>> fractionList;
	int lastFoundColumnCount = 0;
	while (!allSLEsRead)
	{
		string currentLine;
		if (!getline(inputFileStream, currentLine))
		{
			if (fractionList.size() > 0)
			{
				SLEContainer container(fractionList);
				sleContainers.push_back(container);
			}
			allSLEsRead = true;
		}
		else if (currentLine == "--")
		{
			if (fractionList.size() > 0)
			{
				SLEContainer container(fractionList);
				sleContainers.push_back(container);
			}
			fractionList.clear();
			lastFoundColumnCount = 0;
		}
		else
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
					string currentMatrixNumberString = to_string(sleContainers.size() + 1);
					throw exception(("Matrix #" + currentMatrixNumberString  + ": Invalid augmented matrix").c_str());
				}
			}
			else if (currentRowFractionCount < 2)
			{
				string currentMatrixNumberString = to_string(sleContainers.size() + 1);
				throw exception(("Matrix #" + currentMatrixNumberString + ": Invalid augmented matrix").c_str());
			}
			else {
				lastFoundColumnCount = currentRowFractionCount;
			}
			fractionList.push_back(currentFractionRow);
		}	
	}
	inputFileStream.close();
	return sleContainers;
}

#include "ConsoleSLEReader.h"
#include <iostream>

using namespace std;

int ConsoleSLEReader::ReadIntegerInput(std::string errorMessage)
{
	string input;
	bool valid = false;
	int intInput = 0;
	while (!valid)
	{
		getline(cin, input);
		try {
			intInput = stoi(input);
			valid = true;
		}
		catch (exception& ex)
		{
			cout << errorMessage;
		}
	}
	return intInput;
	
}

vector< SLEContainer> ConsoleSLEReader::ReadSLEAugmentedMatrices()
{
	int sleCount;
	cout << "Input the number of systems if linear equations: ";
	string nonIntegerSleCount = "Please input integer for the number of SLEs: ";
	sleCount = ReadIntegerInput(nonIntegerSleCount);
	while (sleCount <= 0)
	{
		cout << "The number of sles should be positive: ";
		sleCount = ReadIntegerInput(nonIntegerSleCount);
	}
	vector< SLEContainer> sleContainers;
	for (int k = 0; k < sleCount; k++)
	{
		int rowCount, columnCount;
		cout << "Input the number of rows of the augmented matrix: ";
		string nonIntegerRowErrorMessage = "Please input integer for the number of rows: ";
		rowCount = ReadIntegerInput(nonIntegerRowErrorMessage);
		while (rowCount <= 0)
		{
			cout << "The number of rows should be positive: ";
			rowCount = ReadIntegerInput(nonIntegerRowErrorMessage);
		}
		cout << "Input the number of columns of the augmented matrix: ";
		string nonIntegerColumnErrorMessage = "Please input integer for the number of columns: ";
		columnCount = ReadIntegerInput(nonIntegerColumnErrorMessage);
		while (columnCount < 2)
		{
			cout << "The number of columns should be at least 2: ";
			columnCount = ReadIntegerInput(nonIntegerColumnErrorMessage);
		}
		vector< vector<Fraction>> augmentedMatrix;
		for (int i = 0; i < rowCount; i++)
		{
			vector< Fraction> currentRow;
			for (int j = 0; j < columnCount; j++)
			{
				while (true)
				{
					try
					{
						cout << "Input [" << (i + 1) << "][" << (j + 1) << "]: ";
						string input;
						getline(cin, input);
						Fraction currentFraction = Fraction::ParseFraction(input);
						currentRow.push_back(currentFraction);
						break;
					}
					catch (exception& ex)
					{
						cout << "Invalid fraction!";
					}
				}
			}
			augmentedMatrix.push_back(currentRow);
		}
		sleContainers.push_back(augmentedMatrix);
	}
	return sleContainers;
}

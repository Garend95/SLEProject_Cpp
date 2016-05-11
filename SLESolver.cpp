#include "SLESolver.h"
#include <exception>

using namespace std;

void SLESolver::PrintMatrix(vector< vector<Fraction> >& matrixToPrint)
{
	int* columnLengths = new int[matrixToPrint[0].size()];
	for (int j = 0; j < matrixToPrint[0].size(); j++) {
		int maxColumnLength = 1;
		for (int i = 0; i < matrixToPrint.size(); i++) {
			int currentFractionLength = matrixToPrint[i][j].GetString().length();
			if (currentFractionLength > maxColumnLength) {
				maxColumnLength = currentFractionLength;
			}
		}
		columnLengths[j] = maxColumnLength;
	}
	for (int i = 0; i < matrixToPrint.size(); i++) {
		for (int j = 0; j < matrixToPrint[i].size(); j++) {
			int currentFractionLength = matrixToPrint[i][j].GetString().length();
			int spaceCount = columnLengths[j] - currentFractionLength;
			for (int k = 0; k < spaceCount; k++) {
				_solutionWriter->Write(" ");
			}
			_solutionWriter->Write(matrixToPrint[i][j].GetString() + "\t");
		}
		_solutionWriter->WriteLine("");
	}
	delete columnLengths;
}

vector< vector<Fraction> > SLESolver::BringToReducedRowEchelonForm(vector< vector<Fraction> > rowEchelonForm)
{
	int rowCount = rowEchelonForm.size();
	int columnCount = rowEchelonForm[0].size();
	bool* pivotArray = new bool[columnCount - 1];
	int pivotCount = 0;
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < columnCount; j++) {
			if (rowEchelonForm[i][j].GetNumerator() != 0) {
				pivotCount++;
				pivotArray[j] = true;
				if ((rowEchelonForm[i][j].GetDenominator() != 1) || (rowEchelonForm[i][j].GetNumerator() != 1))
				{
					Fraction multiplyBy(rowEchelonForm[i][j]);
					multiplyBy.SetNumeratorAndDenominator(multiplyBy.GetDenominator(), multiplyBy.GetNumerator());
					rowEchelonForm[i][j].SetNumeratorAndDenominator(1, 1);
					_solutionWriter->WriteLine("R" + to_string(i + 1) + " * (" + multiplyBy.GetString() + ")");
					for (int k = j + 1; k < rowEchelonForm[i].size(); k++) {
						rowEchelonForm[i][k].Multiply(multiplyBy);
					}
					PrintMatrix(rowEchelonForm);
				}
				break;
			}
		}
	}
	for (int i = columnCount- 2; i >= 0; i--) {
		if (pivotArray[i] == true) {
			int row = --pivotCount;
			for (int j = row - 1; j >= 0; j--) {
				if (rowEchelonForm[j][i].GetNumerator() != 0) {
					Fraction fractionToAdd(rowEchelonForm[j][i]);
					fractionToAdd.SetNumerator(-1 * fractionToAdd.GetNumerator());
					_solutionWriter->WriteLine("R" + to_string(row + 1) + " * (" + fractionToAdd.GetString() + ")" + " + R" + to_string(j + 1));
					for (int k = i; k <= columnCount - 1; k++) {
						Fraction multiply(rowEchelonForm[row][k]);
						multiply.Multiply(fractionToAdd);
						rowEchelonForm[j][k].Add(multiply);
					}
					PrintMatrix(rowEchelonForm);
				}
			}
		}
	}
	delete pivotArray;
	return rowEchelonForm;
}

vector< vector<Fraction> > SLESolver::BringToRowEchelonForm(std::vector< std::vector<Fraction> > augmentedMatrix)
{
	int rowLength = augmentedMatrix.size();
	int columnLength = augmentedMatrix[0].size();
	int lastPivotIndex = 0;
	for (int j = 0; j < columnLength; j++) {
		Fraction currentFraction = augmentedMatrix[lastPivotIndex][j];
		bool pivotFound = false;
		int nextLineIndex = lastPivotIndex + 1;
		if (currentFraction.GetNumerator() == 0) {
			int nonZeroRowIndex = 0;
			for (int k = nextLineIndex; k < rowLength; k++) {
				if (augmentedMatrix[k][j].GetNumerator() != 0) {
					nonZeroRowIndex = k;
					pivotFound = true;
					break;
				}
			}
			if (pivotFound) {
				_solutionWriter->WriteLine("R" + to_string(lastPivotIndex + 1) + "<->" + "R" + to_string(nonZeroRowIndex + 1));
				for (int k = j; k < columnLength; k++) {
					Fraction temp = augmentedMatrix[lastPivotIndex][k];
					augmentedMatrix[lastPivotIndex][k] = augmentedMatrix[nonZeroRowIndex][k];
					augmentedMatrix[nonZeroRowIndex][k] = temp;
				}
				PrintMatrix(augmentedMatrix);
			}
		}
		else {
			pivotFound = true;
		}
		if (pivotFound) {
			for (int k = nextLineIndex; k < rowLength; k++) {
				Fraction fractionToCheck = augmentedMatrix[k][j];
				if (fractionToCheck.GetNumerator() != 0) {
					int newNumerator = -fractionToCheck.GetNumerator() * augmentedMatrix[lastPivotIndex][j].GetDenominator();
					int newDenominator = fractionToCheck.GetDenominator() * augmentedMatrix[lastPivotIndex][j].GetNumerator();
					Fraction fractionToMultiplyBy(newNumerator, newDenominator);
					_solutionWriter->WriteLine("R" + to_string(lastPivotIndex + 1) + "*(" + fractionToMultiplyBy.GetString() + ") + " + "R" + to_string(k + 1));
					for (int t = j; t < columnLength; t++) {
						Fraction fractionToAdd(augmentedMatrix[lastPivotIndex][t]);
						fractionToAdd.Multiply(fractionToMultiplyBy);
						augmentedMatrix[k][t].Add(fractionToAdd);
					}
					PrintMatrix(augmentedMatrix);
				}
			}
			lastPivotIndex++;
			if (lastPivotIndex == rowLength) {
				break;
			}
		}
	}
	return augmentedMatrix;
}

void SLESolver::SolveByGaussJordanElimination(vector< vector<Fraction> > augmentedMatrix)
{
	_solutionWriter->StartWriting();
	int rowCount = augmentedMatrix.size();
	int columnCount = augmentedMatrix[0].size();
	_solutionWriter->WriteLine("We have the following augmented matrix:");
	PrintMatrix(augmentedMatrix);
	_solutionWriter->WriteLine("To bring it to row-echelon form, let\'s perform the following elementary row operations:");
	vector< vector<Fraction> > rowEchelonForm = BringToRowEchelonForm(augmentedMatrix);
	int pivotCount = 0;
	bool* pivotArray = new bool[columnCount - 1];
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < columnCount - 1; j++) {
			if (rowEchelonForm[i][j].GetNumerator() != 0) {
				pivotArray[j] = true;
				pivotCount++;
				break;
			}
		}
	}
	bool hasSolution = true;
	for (int i = pivotCount; i < rowCount; i++) {
		if (rowEchelonForm[i][columnCount - 1].GetNumerator() != 0) {
			hasSolution = false;
			break;
		}
	}
	if (!hasSolution) {
		_solutionWriter->WriteLine("The rank of the coefficients matrix is not equal to the rank of the augmented matrix => the system does not have a solution!");
	}
	else {
		_solutionWriter->WriteLine("Now bring the matrix to reduced row-echelon form by performing the following row-elementary operations");
		vector< vector<Fraction> > reducedRowEchelonForm = BringToReducedRowEchelonForm(rowEchelonForm);
		_solutionWriter->WriteLine("The solution of the system is: ");
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < columnCount - 1; j++) {
				if (reducedRowEchelonForm[i][j].GetNumerator() == 1) {
					_solutionWriter->Write("x" + to_string(j + 1) + " = " + reducedRowEchelonForm[i][columnCount - 1].GetString());
					for (int k = j + 1; k < columnCount - 1; k++) {
						if (reducedRowEchelonForm[i][k].GetNumerator() != 0) {
							Fraction coefficient(reducedRowEchelonForm[i][k]);
							coefficient.SetNumerator(-1 * coefficient.GetNumerator());
							_solutionWriter->Write(" + (" + coefficient.GetString() + ") * x" + to_string(k + 1));
						}
					}
					_solutionWriter->WriteLine("");
					break;
				}
			}
		}
	}
	_solutionWriter->EndWriting();
	delete pivotArray;
}

void SLESolver::SetSolutionWriter(SolutionWriterBase* solutionWriter)
{
	if (!solutionWriter)
	{
		throw std::exception("solutionWriter should not be null");
	}
	_solutionWriter = solutionWriter;
}

SLESolver::SLESolver(SolutionWriterBase* solutionWriter)
{
	SetSolutionWriter(solutionWriter);
}


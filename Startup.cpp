#include <iostream>
#include "Fraction.h"
#include "SolutionWriterBase.h"
#include "ConsoleSolutionWriter.h"
#include "ConsoleSLEReader.h"
#include "FileSolutionWriter.h"
#include "FileSLEReader.h"
#include "SLESolver.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	SolutionWriterBase* solutionWriter = NULL;
	SLEReaderBase* sleReader = NULL;
	for (int i = 1; i < argc - 1; i += 2)
	{
		if (strcmp(argv[i],"--inputfile") == 0) {
			sleReader = new FileSLEReader(argv[i + 1]);
		}
		else if (strcmp(argv[i], "--outputfile") == 0) {
			solutionWriter = new FileSolutionWriter(argv[i + 1]);
		}
	}
	if (!sleReader) {
		sleReader = new ConsoleSLEReader();
	}
	if (!solutionWriter) {
		solutionWriter = new ConsoleSolutionWriter();
	}
	try {
		vector< vector<Fraction>> augmentedMatrix = sleReader->ReadSLEAugmentedMatrix();
		SLESolver solver(solutionWriter);
		solver.SolveByGaussJordanElimination(augmentedMatrix);
	}
	catch (exception& exc) {
		cout << exc.what();
	}
	delete solutionWriter;
	delete sleReader;
	return 0;
}
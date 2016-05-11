#pragma once
#include <vector>
#include "SolutionWriterBase.h"
#include "Fraction.h"

using namespace std;

class SLESolver
{
private:
	SolutionWriterBase* _solutionWriter;
	void PrintMatrix(vector< vector<Fraction> >& fractionMatrix);
	vector< vector<Fraction> > BringToRowEchelonForm(vector< vector<Fraction> > augmentedMatrix);
	vector< vector<Fraction> > BringToReducedRowEchelonForm(vector< vector<Fraction> > rowEchelonForm);
public:
	void SetSolutionWriter(SolutionWriterBase* solutionWriter);
	void SolveByGaussJordanElimination(vector< vector<Fraction> > augmentedMatrix);
	SLESolver(SolutionWriterBase* solutionWriter);
};


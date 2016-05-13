#pragma once
#include <vector>
#include "Fraction.h"

using namespace std;

class SLEContainer
{
private:
	vector< vector <Fraction>> _sle;
public:
	SLEContainer(vector< vector <Fraction>> &sle);
	void SetSLE(vector< vector <Fraction>> &sle);
	vector< vector <Fraction>>& GetSLE();
};


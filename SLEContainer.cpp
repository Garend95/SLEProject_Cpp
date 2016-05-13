#include "SLEContainer.h"

void SLEContainer::SetSLE(vector< vector <Fraction>>& sle)
{
	_sle = sle;
}

vector< vector <Fraction>>& SLEContainer::GetSLE()
{
	return _sle;
}

SLEContainer::SLEContainer(vector< vector <Fraction>>& sle)
{
	SetSLE(sle);
}



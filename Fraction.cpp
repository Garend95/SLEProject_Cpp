#include "Fraction.h"
#include <exception>
#include <cmath>
#include <string>

using namespace std;

void Fraction::Reduce()
{
	int firstNumber = _numerator;
	int secondNumber = _denominator;
	while (firstNumber % secondNumber != 0)
	{
		int remainder = firstNumber % secondNumber;
		firstNumber = secondNumber;
		secondNumber = remainder;
	}
	_numerator = _numerator / secondNumber;
	_denominator = _denominator / secondNumber;
}

int Fraction::GetNumerator()
{
	return _numerator;
}

int Fraction::GetDenominator()
{
	return _denominator;
}

void Fraction::SetNumerator(int newNumerator)
{
	_numerator = newNumerator;
	Reduce();
}

void Fraction::SetDenominator(int newDenominator)
{
	if (newDenominator == 0)
	{
		throw exception("Denominator cannot be 0!");
	}
	_denominator = newDenominator;
	Reduce();
}

void Fraction::SetNumeratorAndDenominator(int numerator, int denominator)
{
	_numerator = numerator;
	SetDenominator(denominator);
}

void Fraction::Add(Fraction& fractionToAdd)
{
	int newNumerator = _numerator * fractionToAdd.GetDenominator() + _denominator * fractionToAdd.GetNumerator();
	int newDenominator = _denominator * fractionToAdd.GetDenominator();
	this->SetNumeratorAndDenominator(newNumerator, newDenominator);
}

void Fraction::Multiply(Fraction& fractionToMultiplyBy)
{
	_numerator = _numerator * fractionToMultiplyBy.GetNumerator();
	SetDenominator(_denominator * fractionToMultiplyBy.GetDenominator());
}

std::string Fraction::GetString()
{
	if (_numerator % _denominator == 0)
	{
		return to_string(_numerator / _denominator);
	}
	else
	{
		string sign;
		if ((_numerator ^ _denominator) < 0) {
			sign = "-";
		}
		else {
			sign = "";
		}
		return sign + to_string(abs(_numerator)) + "/" + to_string(abs(_denominator));
	}
}

Fraction Fraction::ParseFraction(std::string stringToParse)
{
	int newNumerator, newDenominator;
	size_t divisionIndex = stringToParse.find("/");
	try
	{
		if (divisionIndex == string::npos)
		{
			newNumerator = stoi(stringToParse);
			newDenominator = 1;
		}
		else
		{
			string numeratorString = stringToParse.substr(0, divisionIndex);
			string denominatorString = stringToParse.substr(divisionIndex + 1, string::npos);
			newNumerator = stoi(numeratorString);
			newDenominator = stoi(denominatorString);
		}
	}
	catch (exception& exc)
	{
		throw exception("Invalid fraction");
	}
	return Fraction(newNumerator, newDenominator);
}

Fraction::Fraction(int numerator, int denominator)
{
	_numerator = numerator;
	SetDenominator(denominator);
}





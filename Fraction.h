#pragma once
#include <string>

class Fraction
{
private:
	int _numerator;
	int _denominator;
	void Reduce();
public:
	int GetNumerator();
	int GetDenominator();
	void SetNumerator(int newNumerator);
	void SetDenominator(int newDenominator);
	void SetNumeratorAndDenominator(int numerator, int denominator);
	void Add(Fraction& fractionToAdd);
	void Multiply(Fraction& fractionToMultiplyBy);
	std::string GetString();
	static Fraction ParseFraction(std::string stringToParse);
	Fraction(int numerator, int denominator);
};


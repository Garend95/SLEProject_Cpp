#include "ConsoleSolutionWriter.h"
#include <string>
#include <iostream>


void ConsoleSolutionWriter::StartWriting()
{}

void ConsoleSolutionWriter::EndWriting()
{}

void ConsoleSolutionWriter::Write(std::string stringToWrite)
{
	std::cout << stringToWrite;
}

void ConsoleSolutionWriter::WriteLine(std::string stringToWrite)
{
	std::cout << stringToWrite << std::endl;
}

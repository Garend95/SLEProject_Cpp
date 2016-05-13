#include "ConsoleSolutionWriter.h"
#include <string>
#include <iostream>


void ConsoleSolutionWriter::StartWriting()
{
	std::cout << std::endl;
}

void ConsoleSolutionWriter::EndWriting()
{
	std::cout << "--------------";
}

void ConsoleSolutionWriter::Write(std::string stringToWrite)
{
	std::cout << stringToWrite;
}

void ConsoleSolutionWriter::WriteLine(std::string stringToWrite)
{
	std::cout << stringToWrite << std::endl;
}

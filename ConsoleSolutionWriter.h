#pragma once
#include "SolutionWriterBase.h"
#include <string>

class ConsoleSolutionWriter :
	public SolutionWriterBase
{
public:
	void StartWriting();
	void Write(std::string stringToWrite);
	void WriteLine(std::string stringToWrite);
	void EndWriting();
};


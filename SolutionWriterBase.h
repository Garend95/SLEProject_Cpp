#pragma once
#include <string>

class SolutionWriterBase
{
public:
	virtual void StartWriting() = 0;
	virtual void Write(std::string stringToWrite) = 0;
	virtual void WriteLine(std::string stringToWrite) = 0;
	virtual void EndWriting() = 0;
	virtual ~SolutionWriterBase() {}
};


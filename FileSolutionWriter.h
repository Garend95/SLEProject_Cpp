#pragma once
#include "SolutionWriterBase.h"
#include <string>
#include <fstream>


class FileSolutionWriter :
	public SolutionWriterBase
{
private:
	std::string _solutionFilePath;
	std::ofstream* _fileOutputStream;
public:
	void StartWriting();
	void Write(std::string stringToWrite);
	void WriteLine(std::string stringToWrite);
	void EndWriting();
	FileSolutionWriter(std::string solutionFilePath);
	~FileSolutionWriter();
};


#include "FileSolutionWriter.h"
#include <string>
#include <fstream>
#include <exception>

FileSolutionWriter::FileSolutionWriter(std::string solutionFilePath)
{
	_solutionFilePath = solutionFilePath;
	_fileOutputStream = new std::ofstream();
}

void FileSolutionWriter::StartWriting()
{
	_fileOutputStream->open(_solutionFilePath, std::fstream::app);
	if (!_fileOutputStream->is_open()) 
	{
		throw std::exception("Unable to open file");
	}
	(*_fileOutputStream) << std::endl;
}

void FileSolutionWriter::Write(std::string stringToWrite)
{
	(*_fileOutputStream) << stringToWrite;
}

void FileSolutionWriter::WriteLine(std::string stringToWrite)
{
	(*_fileOutputStream) << stringToWrite << std::endl;
}

void FileSolutionWriter::EndWriting()
{
	(*_fileOutputStream) << "--------------";
	_fileOutputStream->close();
}



FileSolutionWriter::~FileSolutionWriter()
{
	delete _fileOutputStream;
}

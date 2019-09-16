#include "FileReader.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::bad_alloc;
using std::ios;

FileReader::FileReader() :arrFile(nullptr), size(0)
{
	createArr();
}

FileReader::~FileReader()
{
	clearArr();
}

void FileReader::createArr()
{
	try{ arrFile = new char[MAXPORTION]; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
}

void FileReader::clearArr()
{
	delete[] arrFile;
}

void FileReader::openFile(const char* file, ArrLetters& letters)
{
	ifstream in(file,ios::in);
	if (in.good())
	{
		distribute(in, letters);
		in.close();
	}
}

void FileReader::distribute(ifstream& in, ArrLetters& letters)
{
	while (!in.eof())
	{
		in.read((char*) arrFile, MAXPORTION);
		if (in.eof())					
		{
			size = in.gcount();
			inicialArr(letters);
			break;
		}
		size = MAXPORTION;
		inicialArr(letters);
	}
	letters.sortUp();					
}

void FileReader::inicialArr(ArrLetters& letters)
{
	for (int i = 0; i < size; ++i)
	{
		letters.add(arrFile[i]);
	}
}

void FileReader::printContent() const
{
	for (int i = 0; i < size; ++i)
		cout << arrFile[i] <<" ";
	cout << endl;
}


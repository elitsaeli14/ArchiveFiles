#ifndef __FileReader_H__
#define __FileReader_H__
#include"ArrLetters.h"

#include<iostream>
using std::ifstream;

const int MAXPORTION = 2048;

class FileReader
{
private:
	char* arrFile;
	int size;

public:
	FileReader();
	~FileReader();

	void openFile(const char* file, ArrLetters& letters);
	void distribute(ifstream& in, ArrLetters& letters);

	void printContent() const;

private:
	void createArr();
	void clearArr();

	void inicialArr(ArrLetters& letters);

	FileReader(const FileReader&);
	FileReader& operator=(const FileReader&);
};


#endif //!__FileReader_H__
#ifndef __FileSave_H__
#define __FileSave_H__
#include"ArrLetters.h"
#include"PriorityQueue.h"


#include<fstream>
using std::ofstream;
using std::ifstream;

const int MAXREAD = 2048;
const int MAXSAVE = 256;

class FileSave
{
private:
	char* arrRead;
	int sizeRead;
	short* arrSave;
	int sizeSave;
	int capacitySave;
	Node* root;

public:
	FileSave();
	~FileSave();

	void saveFile(Node* newRoot,ArrLetters& letters, int sizeDic, char* file);

	void printArrSave();

private:
	void createRead();
	void createSave();
	void clearArrSave();

	void saveDic(ofstream& out, int sizeDic, ArrLetters& letters);
	void openFile(char* file, ofstream& out);
	void distrFile(ifstream& in, ofstream& out);
	void saveContent(ofstream& out, int& cnt, short& temp);

	void  findLen(Node* newRoot, int i, short& len);
	void findBites(Node* root, int i, short& bites);

	FileSave(const FileSave&);
	FileSave& operator=(const FileSave&);
};

#endif//!__FileSave_H__
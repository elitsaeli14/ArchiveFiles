#ifndef __Unpack_H__
#define __Unpack_H__

#include"ArrLetters.h"
#include"PriorityQueue.h"

#include<fstream>
using std::ofstream;
using std::ifstream;

class Unpack
{
private:
	ArrLetters letters;
	PriorityQueue queue;
	char* file;
	Node* root;
	int sizeDic;

public:
	Unpack();
	~Unpack();

	void setFile(char* newFile);
	void saveUnpackFile();

	void printTree(Node* newRoot);

private:
	void clear(Node* newRoot);
	void createNode(Node*& temp);
	void bin(short number);

	void distrArr(ifstream& in);
	void distrQueue();
	void inicialNode(Node*& temp, int i);

	void createTree();
	void codesLetters(Node* newRoot, short tempBit, short tempLen);

	Unpack(const Unpack&);
	Unpack& operator=(const Unpack&);
};


#endif//!__Unpack_H__
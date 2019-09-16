#ifndef __Huffman_H__
#define __Huffman_H__

#include"FileReader.h"
#include"PriorityQueue.h"
#include"FileSave.h"

class Huffman
{
private:
	FileReader fileReader;
	PriorityQueue queue;
	ArrLetters letters;
	FileSave fileSave;
	char* file; 
	Node* root;
	int sizeDic;

public:
	Huffman();
	~Huffman();

	void setFile(char* newFile);
	void distributeLetters();
	void fillQueue();
	void makeTree();
	void makeCodesLetters(Node* newRoot,short tempB, short tempL);
	void saveFile();

	void printTree(Node* newRoot);

private:
	void clear(Node* newRoot);
	void createNode(Node*& temp);
	void bin(short number);


	Huffman(const Huffman&);
	Huffman& operator=(const Huffman&);
};

#endif//!__Huffman_H__
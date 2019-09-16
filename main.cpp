#include <iostream>
#include "FileReader.h"
#include "PriorityQueue.h"
#include "Node.h"
#include "Huffman.h"
#include "Unpack.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	char* file = "test.txt";
	Huffman huffman;
	huffman.setFile(file);
	huffman.distributeLetters();
	huffman.fillQueue();
	huffman.makeTree();
	huffman.saveFile();

	Unpack unpack;
	unpack.setFile("testCompress.arc");
	unpack.saveUnpackFile();

	return 0;
}
#include"Unpack.h"

#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::bad_alloc;

Unpack::Unpack() : file(nullptr), root(nullptr), sizeDic(0){}

Unpack::~Unpack()
{
	clear(root);
}

void Unpack::clear(Node* newRoot)
{
	if (!newRoot) return;
	clear(newRoot->left);
	clear(newRoot->right);
	delete newRoot;
}

void Unpack::createNode(Node*& temp)
{
	try{ temp = new Node; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
}

void Unpack::setFile(char* newFile)
{
	file = newFile;
}

void Unpack::saveUnpackFile()
{
	ifstream in(file, ios::binary | ios::in);
	if (in.good())
	{
		in.read((char*)&sizeDic, sizeof(int));	
		distrArr(in);							
		distrQueue();							 
		createTree();							
		codesLetters(root, 0, 0);				
	}
	in.close();
}

void Unpack::distrArr(ifstream& in)
{
	for (int i = 0; i < sizeDic; ++i)
	{
		char tempChar;
		in.read((char*)&tempChar, sizeof(char));
		int tempCnt;
		in.read((char*)&tempCnt, sizeof(int));
		letters.addStruct(tempChar, tempCnt);
	}
}


void Unpack::distrQueue()
{
	for (int i = 0; i < sizeDic; ++i)
	{
		Node* temp;
		inicialNode(temp, i);
		queue.push(temp);
	}
}

void Unpack::inicialNode(Node*& temp, int i)
{	
	createNode(temp);
	temp->symbol = letters.getLett(i);
	temp->cnt = letters.getCnt(i);
}

void Unpack::createTree()
{
	while (true)
	{
		Node* newRoot;
		createNode(newRoot);
		newRoot->right = queue.pop();
		newRoot->left = queue.pop();
		newRoot->cnt = newRoot->left->cnt + newRoot->right->cnt;
		if (queue.isEmpty())
		{
			root = newRoot;
			break;
		}
		queue.push(newRoot);
	}
}

void Unpack::codesLetters(Node* newRoot, short tempBit, short tempLen)
{
	if (!newRoot->left)
	{
		newRoot->bites = tempBit;
		newRoot->len = tempLen;
		return;
	}
	codesLetters(newRoot->left, tempBit << 1, tempLen + 1);
	codesLetters(newRoot->right, (tempBit << 1) + 1, tempLen + 1);
}

void Unpack::printTree(Node* newRoot)
{
	if (!newRoot->left)
	{
		cout << newRoot->symbol << " " << newRoot->len << " ";
		bin(newRoot->bites);
		cout << endl << endl;
		return;
	}
	printTree(newRoot->left);
	printTree(newRoot->right);
}

void Unpack::bin(short number)
{
	for (int mask = 1 << 15; mask != 0; mask >>= 1)
	{
		if (number & mask)
			cout << 1;
		else cout << 0;
	}
}
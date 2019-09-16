#include"Huffman.h"

#include<iostream>
using std::bad_alloc;
using std::cout;
using std::endl;

Huffman::Huffman() :root(nullptr),sizeDic(0){}

Huffman::~Huffman()
{
	clear(root);
}

void Huffman::clear(Node* newRoot)
{
	if (!newRoot) return;
	clear(newRoot->left);
	clear(newRoot->right);
	delete newRoot;
}

void Huffman::setFile(char* newFile)
{
	file = newFile;
}

void Huffman::distributeLetters()
{
	fileReader.openFile(file, letters);
}

void Huffman::fillQueue() 
{
	sizeDic = letters.getSize();
	for (int i = 0; i < sizeDic; ++i)
	{
		Node* temp;
		createNode(temp);
		temp->symbol = letters.getLett(i);
		temp->cnt = letters.getCnt(i);

		queue.push(temp);
	}
}

void Huffman::createNode(Node*& temp)
{
	try{ temp = new Node; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
}

void Huffman::makeTree() 
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
	makeCodesLetters(root, 0, 0);
}

void Huffman::makeCodesLetters(Node* newRoot,short tempB,short tempL)
{					
	if (!newRoot->left)
	{
		newRoot->bites = tempB;
		newRoot->len = tempL;
		return;
	}
	makeCodesLetters(newRoot->left,tempB << 1,tempL + 1);
	makeCodesLetters(newRoot->right,(tempB << 1) + 1, tempL + 1);
}

void Huffman::saveFile()
{
	fileSave.saveFile(root, letters, sizeDic, file);
}

void Huffman::printTree(Node* newRoot)
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

void Huffman::bin(short number)
{
	for (int mask = 1 << 15; mask != 0; mask >>= 1)
	{
		if (number & mask)
			cout << 1;
		else cout << 0;
	}
}
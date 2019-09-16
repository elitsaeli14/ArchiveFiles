#include"FileSave.h"

#include<iostream>
#include<fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::bad_alloc;

FileSave::FileSave() : arrRead(nullptr),sizeRead(0), arrSave(nullptr),
sizeSave(0), capacitySave(MAXSAVE)
{
	createRead();
	createSave();
}

FileSave::~FileSave()
{
	delete[] arrRead;
	delete[] arrSave;
}

void FileSave::createRead()
{
	try{ arrRead = new char[MAXREAD]; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
}

void FileSave::createSave()
{
	try{ arrSave = new short[capacitySave]; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
}

void FileSave::saveFile(Node* newRoot, ArrLetters& letters, int sizeDic, char* file)
{
	root = newRoot;
	ofstream out("testCompress.arc", ios::binary | ios::out);
	if (out.good())
	{
		saveDic(out, sizeDic, letters);				
		out.write((char*)&root->cnt, sizeof(int));	
		openFile(file, out);						
	}
	out.close();
}

void FileSave::saveDic(ofstream& out, int sizeDic, ArrLetters& letters)
{
	out.write((char*)&sizeDic, sizeof(int));	
	for (int i = 0; i < sizeDic; ++i)			
	{
		char tempSymbol = letters.getLett(i);
		out.write((char*)&tempSymbol, sizeof(char));
		int tempCnt = letters.getCnt(i);
		out.write((char*)&tempCnt, sizeof(int));
	}
}

void FileSave::openFile(char* file,ofstream& out)
{
	ifstream in(file, ios::in);
	if (in.good())
	{
		distrFile(in, out); 
		in.close();
	}
}

void FileSave::distrFile(ifstream& in, ofstream& out)
{
	int cnt = 1;
	short tempS = 0;
	while (!in.eof())
	{
		in.read((char*)arrRead, MAXREAD);
		if (in.eof())
		{
			sizeRead = in.gcount();
			saveContent(out, cnt, tempS);	
			if (cnt > 0)					 
			{
				out.write((char*)&tempS, sizeof(short));
			}
			break;
		}
		sizeRead = MAXREAD;
		saveContent(out, cnt, tempS);
	}
}

void FileSave::saveContent(ofstream& out, int& cnt, short& tempS)
{
	for (int i = 0; i < sizeRead; ++i)
	{
		short len = 0;
		findLen(root, i, len);						
		short bites = 0;
		findBites(root, i, bites);					
		for (int j = 1; j <= len; ++j)
		{
			short temp = (bites >> (len - j)) & 1;	
			if (cnt == 17)							
			{
				arrSave[sizeSave] = tempS;			
				++sizeSave;
				if (sizeSave >= capacitySave)
				{
					out.write((char*)&arrSave, sizeSave*2); 
					sizeSave = 0;
				}
				tempS = 0;							
				cnt = 1;
			}
			if (temp != 0)
				tempS = tempS | (temp << (16 - cnt)); 
			++cnt;	
		}
	}
	if (sizeSave > 0)			
	{
		out.write((char*)&arrSave, sizeSave*2);
	}
	clearArrSave();
}


void FileSave::findLen(Node* newRoot, int i, short& len)
{
	if (!newRoot->left)
	{
		if (newRoot->symbol == arrRead[i])
		{
			len = newRoot->len;
			return;
		}
		return;
	}
	findLen(newRoot->left, i, len);
	findLen(newRoot->right, i, len);
}

void FileSave::findBites(Node* newRoot, int i, short& bites)
{
	if (!newRoot->left)
	{
		if (newRoot->symbol == arrRead[i])
		{
			bites = newRoot->bites;
			return;
		}
		return;
	}
	findBites(newRoot->left, i, bites);
	findBites(newRoot->right, i, bites);

}

void FileSave::clearArrSave()
{
	for (int i = 0; i < sizeSave; ++i)
		arrSave[i] = 0;
	sizeSave = 0;
}

void FileSave::printArrSave()
{
	for (int i = 0; i < sizeSave; ++i)
	{
		cout << arrSave[i] << " ";
	}
	cout << endl;
}
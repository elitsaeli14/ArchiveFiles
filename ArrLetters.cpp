#include "ArrLetters.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::bad_alloc;
using std::ios;

ArrLetters::ArrLetters() :content(nullptr), size(0), capacity(MAXARR)
{
	createArr();
}

ArrLetters::~ArrLetters()
{
	clearContent();
}

void ArrLetters::createArr()
{
	try{ content = new Letter*[capacity]; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
}

void ArrLetters::createStruct()
{
	if (size == capacity)
		resize();
	try{ content[size] = new Letter; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
	++size;
}

void ArrLetters::resize()
{
	Letter** temp;
	try{ temp = new Letter*[size * 2]; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}
	for (int i = 0; i < size; ++i)
	{
		temp[i] = content[i];
	}
	delete[] content;
	content = temp;
	capacity = size * 2;
}

void ArrLetters::clearContent()
{
	for (int i = 0; i < size; ++i)
		delete content[i];
	delete[] content;
}

int ArrLetters::getSize() const
{
	return size;
}

char ArrLetters::getLett(int i) const
{
	return content[i]->lett;
}

int ArrLetters::getCnt(int i) const
{
	return content[i]->cnt;
}

void ArrLetters::add(char lett) 
{								
	if (size == 0)
	{
		createStruct();
		content[size - 1]->lett = lett;
		(++content[size - 1]->cnt);
	}
	else if (findLett(lett))
		return;
	else
		addLett(lett);
}

bool ArrLetters::findLett(char letter) 
{
	for (int i = 0; i < size; ++i)
	{
		if (letter == content[i]->lett)
		{
			++content[i]->cnt;
			return true;
		}
	}
	return false;
}

void ArrLetters::addLett(char lett)				
{
	createStruct();
	content[size - 1]->lett = lett;
	(++content[size - 1]->cnt);
}

void ArrLetters::addStruct(char lett, int cnt)	
{
	createStruct();
	content[size - 1]->lett = lett;
	content[size - 1]->cnt = cnt;
}

void ArrLetters::sortUp()					
{
	Letter* min = content[0];
	int poz = 0;
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i; j < size - 1; ++j)
		{
			if (min->cnt > content[j + 1]->cnt)
			{
				min = content[j + 1];
				poz = j + 1;
			}
		}
		putRight(i, poz, min);
		min = content[i + 1];
		poz = i + 1;
	}
}

void ArrLetters::putRight(int& i, int& poz, Letter*& min)
{
	for (int y = poz; y > i; --y)
	{
		content[y] = content[y - 1];
	}
	content[i] = min;
}

void ArrLetters::printContent() const
{
	for (int i = 0; i < size; ++i)
		cout << content[i]->lett << content[i]->cnt << " ";
	cout << endl;
}
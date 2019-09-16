#ifndef __ArrLetters_H__
#define __ArrLetters_H__
#include<iostream>

const int MAXARR = 256;

class ArrLetters
{
private:
	struct Letter
	{
		char lett;
		int cnt;
		Letter() : lett('\0'), cnt(0){}
	};

	Letter** content;
	int size;
	int capacity;

public:
	ArrLetters();
	~ArrLetters();

	void add(char lett);
	void addStruct(char lett, int cnt);
	void sortUp();

	int getSize() const;
	char getLett(int i) const;
	int getCnt(int i) const;
	
	void printContent() const;

private:
	void createArr();
	void createStruct();
	void copyArr(const ArrLetters& newArrLetters);
	void clearContent();
	void resize();
	void putRight(int& i, int& poz, Letter*& min);

	bool findLett(char letter);
	void addLett(char letter);

	ArrLetters(const ArrLetters&);
	ArrLetters& operator=(const ArrLetters&);
};


#endif //!__ArrLetters_H__
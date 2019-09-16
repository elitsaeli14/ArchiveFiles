#ifndef __PriorityQueue_H__
#define __PriorityQueue_H__
#include"Node.h"

const int MAXSIZE = 256;

class PriorityQueue
{
private:
	Node** arr;
	int size;
	int capacity;

public:
	PriorityQueue();
	~PriorityQueue();

	bool isEmpty() const;
	void push(Node*& newNode);
	Node* pop();
	int getSize() const;

	void print() const;

private:
	void createArr();
	void resize();
	void clearContent();

	void putDownRight(int index);
	void putUpRight(int index);
	
	bool cmpBoth(int& index);
	bool cmpLeft(int& index);
	bool cmpRight(int& index);

	int parent(int index) const;
	int childL(int index) const;
	int childR(int index) const;

	void swap(Node*& first, Node*& second);

	PriorityQueue(const PriorityQueue&);
	PriorityQueue& operator=(const PriorityQueue&);
};



#endif //!__PriorityQueue_H__
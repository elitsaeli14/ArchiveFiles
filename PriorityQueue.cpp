#include "PriorityQueue.h"

#include<iostream>
using std::cout;
using std::endl;
using std::bad_alloc;

PriorityQueue::PriorityQueue() : arr(nullptr), size(0), capacity(MAXSIZE)
{
	createArr();
}

PriorityQueue::~PriorityQueue()
{
	clearContent();
}

void PriorityQueue::clearContent()
{
	delete[] arr;
}

void PriorityQueue::createArr()
{
	try{ arr = new Node*[capacity]; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}

	for (int i = 0; i < capacity; ++i)
		arr[i] = nullptr;
}

void PriorityQueue::resize()
{
	Node** temp;
	try{ temp = new Node*[capacity *= 2]; }
	catch (bad_alloc& e)
	{
		cout << "Not enough memory!"; throw;
	}

	for (int i = 0; i < size; ++i)
		temp[i] = arr[i];

	delete[] arr;
	arr = temp;
}

int PriorityQueue::getSize() const
{
	return size;
}

bool PriorityQueue::isEmpty() const
{
	if (size == 0)
		return true;
	return false;
}


void PriorityQueue::push(Node*& newNode)
{
	if (isEmpty())
	{
		arr[0] = newNode;
		++size;
	}
	else		
	{
		if (size == capacity)
			resize();
		arr[size] = newNode;				
		putUpRight(size);	
		++size;
	}
}


void PriorityQueue::putDownRight(int index)
{
	while (true)
	{
		int parent = arr[index]->cnt;
		if (arr[childL(index)] && arr[childR(index)]) 
		{
			int leftChild = arr[childL(index)]->cnt;
			int rightChild = arr[childR(index)]->cnt;
			if (parent > leftChild || parent > rightChild)
			{
				if (cmpBoth(index))
					continue;
				else break;
			}
			else break;
		}
		else if (arr[childL(index)]) 
		{
			if (cmpLeft(index))
				continue;
			else break;
		}
		else if (arr[childR(index)]) 
		{
			if (cmpRight(index))
				continue;
			else break;
		}
		else break;
	}
}

bool PriorityQueue::cmpBoth(int& index)
{
	int leftChild = arr[childL(index)]->cnt;
	int rightChild = arr[childR(index)]->cnt;

	if (leftChild < rightChild)
	{
		swap(arr[index], arr[childL(index)]);
		index = childL(index);
		return true;
	}
	else if (rightChild <= leftChild)
	{
		swap(arr[index], arr[childR(index)]);
		index = childR(index);
		return true;	
	}
	else return false;
}

bool PriorityQueue::cmpLeft(int& index)
{
	int parent = arr[index]->cnt;
	int leftChild = arr[childL(index)]->cnt;
	if (parent > leftChild)
	{
		swap(arr[index], arr[childL(index)]);
		index = childL(index);
		return true;
	}
	else return false;
}

bool PriorityQueue::cmpRight(int& index)
{
	int parent = arr[index]->cnt;
	int rightChild = arr[childR(index)]->cnt;
	if (parent > rightChild)
	{
		swap(arr[index], arr[childR(index)]);
		index = childR(index);
		return true;
	}
	else return false;
}

void PriorityQueue::putUpRight(int index)
{
	while (true)
	{
		if (index != 0)
		{
			if (arr[index]->cnt < arr[parent(index)]->cnt)
			{
				swap(arr[index], arr[parent(index)]);
				index = parent(index);
			}
			else break;
		}
		else break;
	}
}

Node* PriorityQueue::pop()
{
	if (isEmpty())
		return nullptr;
	
	Node* temp = arr[0];
	arr[0] = arr[size - 1];
	arr[size - 1] = nullptr;
	if (size > 1)
		putDownRight(0);
	--size;

	return temp;
}

int PriorityQueue::parent(int index) const
{
	return (index - 1) / 2;
}

int PriorityQueue::childL(int index) const
{
	return index * 2 + 1;
}

int PriorityQueue::childR(int index) const
{
	return index * 2 + 2;
}

void PriorityQueue::swap(Node*& first, Node*& second)
{
	Node* temp = first;
	first = second;
	second = temp;
}

void PriorityQueue::print() const
{
	for (int i = 0; i < size; ++i)
		cout << arr[i]->symbol << arr[i]->cnt << " ";
	cout << endl;
}
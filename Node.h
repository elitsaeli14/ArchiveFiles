#ifndef _Node_H__
#define _Node_H__

struct Node
{
	char symbol;
	Node *left, *right;
	int cnt;
	short len;
	short bites;

	Node() : symbol(';'), left(nullptr), right(nullptr), cnt(0),
	len(0), bites(0){}
};

#endif//!_Node_H__
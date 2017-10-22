#pragma once

#include "Enemy.h"
#include "LLNode.h"

template <typename T>
class LinkedList
{
public:
	LinkedList(LLNode<T> *begin);
	LinkedList();
	~LinkedList();

	//returns the start of the linked list; the beginning node
	LLNode<T> * getBeg();

	//returns the size of the linked list
	int size();

	//destroy all the nodes, freeing the memory
	void destroyNodes();

	//insert a node at position p (default is beginning)
	void insertNode(T data, int p = 0);

	//adds a node to the back
	void pushBack(T data);

	//print all the nodes out starting from position p (default is 0)
	void printNodes(int p = 0);

	//deletes a node at a position p
	void deleteNode(int p);

	//deletes the last node in the linked list
	void popBack();

	//reverses the linked list! basically makes all the pointers point backwards and the 
	//head node is at the "back" after calling this function. iterative not recursive
	void reverse();

private:
	LLNode<T> *_beginNode;
	int _size;
};
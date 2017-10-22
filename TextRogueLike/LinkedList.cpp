#include <iostream>
#include <string>

#include "LinkedList.h"
#include "Error.h"

template <typename T>
LinkedList<T>::LinkedList(LLNode<T> *begin)
{
	_beginNode = begin;
	_size = 1;
}

template <typename T>
LinkedList<T>::LinkedList()
{

}

template <typename T>
LLNode<T> * LinkedList<T>::getBeg()
{
	if (_size < 1)
	{
		Error err("Error: could not get beginning node, list has no elements");
		std::cerr << err.what() << std::endl;
	}

	//get the node at the beginning
	return _beginNode;
}

template <typename T>
int LinkedList<T>::size()
{
	return _size;
}

template <typename T>
void LinkedList<T>::destroyNodes()
{
	if (_size > 1)
	{
		//free memory from the heap!
		LLNode<T> *it = _beginNode;
		LLNode<T> *next = _beginNode;

		//loops through and deletes the nodes
		while (it->nextNode != nullptr)
		{
			next = it->nextNode;
			delete it;
			it = next;
		}
		//delete the last one!
		delete it;
	}
	if (_size == 1)
	{
		delete _beginNode;
		_size--;
	}
}

template <typename T>
void LinkedList<T>::pushBack(T data)
{
	//basically just insert a node at the _size position
	insertNode(data, _size);
}

template <typename T>
void LinkedList<T>::insertNode(T data, int p)
{
	//if its an invalid position, make and error and return
	if (p < 0 || p > _size)
	{
		Error invPos("Error inserting new node, invalid position at: " + std::to_string(p));
		std::cerr << invPos.what() << std::endl;
		return;
	}

	//if they want to insert it to the front, create a new node that points to the (previous) beginning element
	if (p == 0)
	{
		LLNode<T> *n = new LLNode<T>(data, _beginNode);
		_beginNode = n;
	}

	//if they want to insert it anywhere else
	else if (p <= _size)
	{
		//we are going to end at one before the actual value, because i can't go backwards
		//in a link list. Meaning since I can't modify the value BEFORE it (the variable),
		//i have to make it the value i actually want to modify. I could have set this up
		//as a condition in the while loop as well.
		p--;

		int pos = 0;
		LLNode<T> *it = _beginNode;

		//go through the list up to the position they enter
		while (pos != p)
		{
			it = it->nextNode;
			pos++;
		}
		//if the node is at the end
		if (it->nextNode == nullptr)
			it->nextNode = new LLNode<T>(data, nullptr);
		//if the node is not at the end
		else
			it->nextNode = new LLNode<T>(data, it->nextNode);
	}

	//increase the size of the linked list!
	_size++;
}

template <typename T>
void LinkedList<T>::printNodes(int p)
{
	//this basically creates an iterator to go through all the nodes
	//and then prints their values out. pretty simple

	//if there are no elements, tell us!
	if (_size == 0)
	{
		Error err("Error printing nodes, list size is zero");
		std::cerr << err.what() << std::endl;
		return;
	}

	LLNode<T> *it = _beginNode;
	int count = 0;
	while (it->nextNode != nullptr)
	{
		if (count >= p)
			std::cout << it->data << std::endl;

		it = it->nextNode;
		count++;
	}
	std::cout << it->data << std::endl;
}

template <typename T>
void LinkedList<T>::deleteNode(int p)
{
	//pretty much does the same thing as the insert, just deletes the node.
	//We end at one before the actual value of p because if i delete it->nextNode then that's all good.
	//However, if i delete the iterator itself, im screwed.



	//if the size of the node is 1 (just the root node), and we delete it, the list doens't exist anymore
	if (_size == 1)
	{
		destroyNodes();
		_size--;
		return;
	}

	//if the position is outside the range of the linked list, tough titties
	if (p > _size || p < 0)
	{
		Error err("Error deleting node, invalid position at: " + std::to_string(p));
		std::cerr << err.what() << std::endl;
		return;
	}

	//if the positoin is 0, then make the next node the new head node
	if (p == 0)
	{
		LLNode<T> *it = _beginNode->nextNode;
		delete _beginNode;
		_beginNode = it;
		_size--;
		return;
	}

	p--;

	int pos = 0;
	LLNode<T> *it = _beginNode;

	while (pos != p)
	{
		it = it->nextNode;
		pos++;
	}

	//if this is the last node, then the new last node's nextNode needs to be nullptr
	if (it->nextNode == nullptr)
	{
		delete it->nextNode;
		it->nextNode = nullptr;
	}
	else
	{
		//we are about to delete the next node so we need to store the value
		LLNode<T> *it2 = it->nextNode->nextNode;
		delete it->nextNode;
		it->nextNode = it2;
	}

	//our LL is now one element smaller. The size should reflect that!
	_size--;
}

template <typename T>
void LinkedList<T>::reverse()
{
	//create some variables we need. since we need to modify nodes infront of and behind us, we need three.
	//one for the next node, one for the current, and one for the previous
	LLNode<T> *next = _beginNode;
	LLNode<T> *curr = _beginNode;
	LLNode<T> *prev = curr;

	//loop through the entire LL
	for (int i = 0; i != _size; i++)
	{
		//move the next node to be one ahead from the current node, at all times
		next = next->nextNode;

		//if this is the first node, then we make it the new ending node
		if (i == 0)
			curr->nextNode = nullptr;
		//else, the node now points to the one behind it!
		else
			curr->nextNode = prev;

		//the previous node is now the current, and the current node is now the next
		prev = curr;
		curr = next;
	}
	//finally the beginning node is equal to the node that used to be at the end.
	//after the loop finishes, next and curr are both NULL, and prev is the last value
	_beginNode = prev;
}

template <typename T>
void LinkedList<T>::popBack()
{
	//just call the deleteNode() function with the position set to the end
	deleteNode(_size - 1);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	//made a separate function for destroy nodes, just incase you want to delete
	//them all for whatever reason (without running the destructor)
	destroyNodes();
}

template class LinkedList<Enemy *>;
template class LinkedList<StatusInfo *>;
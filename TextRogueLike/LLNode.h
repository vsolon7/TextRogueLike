#pragma once

#include "Enemy.h"

template<typename T>

struct LLNode
{
	LLNode(T d, LLNode *next = nullptr)
	{
		data = d;
		nextNode = next;
	}

	T data;
	LLNode *nextNode;
};
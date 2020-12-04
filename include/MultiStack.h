#pragma once
#include "Stack.h"

template <class T>
class TMultiStack
{
protected:

	int stackCount;
	TStack<T>* stacks;

	void reallocate(int free_cells, int n)
	{
		int for_each = free_cells / stackCount;
		int extra = free_cells - for_each * stackCount;

		for (int i = 0; i < stackCount; i++)
		{
			if (i == n)
				stacks[i].resize(stacks[i].GetCount() + for_each + extra);

			else
				stacks[i].resize(stacks[i].GetCount() + for_each);
		}
	}

	int get_free_cells() 
	{
		int free_cells = 0;
		for (int i = 0; i < stackCount; i++)
			free_cells += stacks[i].GetSize() - stacks[i].GetCount();
		return free_cells;
	}

public:
	TMultiStack(int sizeStack = 1, int _stackCount = 1);
	TMultiStack(TMultiStack<T>& _v);
	~TMultiStack();

	TMultiStack<T>& operator =(TMultiStack<T>& _v);

	void Push(T d, int i);
	T Pop(int i);

	bool IsEmpty(int i) const;
	bool IsFull(int i) const;
};

template<class T>
TMultiStack<T>::TMultiStack(int sizeStack, int _stackCount)
{
	if (sizeStack <= 0 || _stackCount <= 0) throw logic_error("invalid size");
	stackCount = _stackCount;
	stacks = new TStack<T>[_stackCount];
	for (int i = 0; i < _stackCount; i++)
		stacks[i] = TStack<T>(sizeStack, true);
}

template <class T>
TMultiStack<T>::TMultiStack(TMultiStack<T>& _v)
{
	stacks = new TStack<T>[_v.stackCount];
	stackCount = _v.stackCount;
	for (int i = 0; i <_v.stackCount; i++) {

		stacks[i] = TStack<T>(1, false);
		stacks[i] = _v.stacks[i];
	}
}

template<class T>
TMultiStack<T>::~TMultiStack()
{
	if (stacks != 0)
	{
		//for (int i = 0; i < stackCount; i++)
			//stacks[i].~TStack();
		delete[] stacks;
		//stacks = 0;
	}
}

template<class T>
inline TMultiStack<T>& TMultiStack<T>::operator=(TMultiStack<T>& _v)
{
	if (this == &_v)
		return *this;

	if (stacks != 0)
	{
		delete[] stacks;
	}

	this->size = _v.size;
	this->stackCount = _v.stackCount;

	this->stacks = new TStack<T>[stackCount];
	for (int i = 0; i < stackCount; i++)
	{
		stacks[i] = _v.stacks[i];
	}

	return *this;
}

template<class T>
void TMultiStack<T>::Push(T d, int n)
{
	if (n < 0 || n >= stackCount)
		throw - 1;
	if (stacks[n].IsFull())
	{
		int free_cells = get_free_cells();
		if (free_cells > 0)
			reallocate(free_cells, n);
		else
			throw - 1;
	}
	stacks[n].Push(d);
}

template<class T>
T TMultiStack<T>::Pop(int i)
{
	if (i < 0 || i >= stackCount) throw - 1;
	return stacks[i].Pop();
}

template<class T>
inline bool TMultiStack<T>::IsEmpty(int i) const
{

	if ((i < 0) || (i >= stackCount)) throw logic_error("invalid_size");
	return stacks[i].IsEmpty();
}

template<class T>
inline bool TMultiStack<T>::IsFull(int i) const
{
	if ((i < 0) || (i >= stackCount)) throw logic_error("invalid_size");
	return stacks[i].IsFull();
}

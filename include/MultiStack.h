#include "Stack.h"

template <class T>
class TMultiStack
{
protected:

	int count;
	int size;
	T* x;
	TStack<T>* stacks;

	T** oldX;

	void StackRelocation(int index);

public:
	TMultiStack(int size = 1, int count = 1);
	TMultiStack(TMultiStack<T>& _v);
	~TMultiStack();

	TMultiStack<T>& operator =(TMultiStack<T>& _v);

	void Push(T d, int i);
	T Pop(int i);

	bool IsEmpty(int i) const;
	bool IsFull(int i) const;

	//template<class T1>
	friend ostream& operator<< (ostream& ostr, const TMultiStack<T>& A)
	{
		for (int i = 0; i < A.count; i++)
			ostr << A.stacks[i] << endl;
		return ostr;
	}
};

template<class T>
inline void TMultiStack<T>::StackRelocation(int index)
{
	int freeSize = 0;
	for (int i = 0; i < count; i++)
		freeSize += stacks[i].GetSize() - stacks[i].GetCount();

	if (freeSize == 0)
		throw - 2;

	int for_each = freeSize / count;
	int* sizes = new int[count];
	for (int i = 0; i < count - 1; i++)
		sizes[i] = stacks[i].GetCount() + for_each;
	sizes[count - 1] = stacks[count - 1].GetCount() + freeSize - for_each * (count - 1);

	T** newX = new T *[count];
	int k = 0;
	for (int i = 0; i < count; i++)
	{
		newX[i] = &(x[k]);
		k += sizes[i];
	}

	for (int i = 0; i < count; i++)
	{
		if (newX[i] == oldX[i])
			stacks[i].SetData(newX[i], sizes[i], stacks[i].GetCount());
		else if (newX[i] < oldX[i])
		{
			for (int j = 0; j < stacks[i].GetCount(); j++)
				newX[i][j] = oldX[i][j];
			stacks[i].SetData(newX[i], sizes[i], stacks[i].GetCount());
		}
		else if (newX[i] > oldX[i])
		{
			for (k = i; k < count; k++)
				if (newX[k] > oldX[k])
					continue;
				else
					break;
			k--;

			for (int s = k; s >= i; s--)
			{
				for (int j = stacks[s].GetCount() - 1; j >= 0; j--)
					newX[s][j] = oldX[s][j];
				stacks[s].SetData(newX[s], sizes[s], stacks[s].GetCount());
			}
		}

	}

	T** buffer = oldX;
	oldX = newX;
	delete[] buffer;
	delete[] sizes;
}

template<class T>
TMultiStack<T>::TMultiStack(int size, int count)
{
	if (size <= 0 || count <= 0)
		throw logic_error("invalid size");
	this->count = count;
	this->size = size;

	x = new T[size];
	for (int i = 0; i < size; i++)
		x[i] = 0;

	int for_each = size / count;
	int* sizes = new int[count];
	for (int i = 0; i < count - 1; i++)
		sizes[i] = for_each;
	sizes[count - 1] = size - for_each * (count - 1);

	oldX = new T *[count];

	stacks = new TStack<T>[count];
	int k = 0;
	for (int i = 0; i < count; i++)
	{
		stacks[i].SetData(&(x[k]), sizes[i], 0);
		oldX[i] = &(x[k]);
		k += sizes[i];
	}
}

template <class T>
TMultiStack<T>::TMultiStack(TMultiStack<T>& _v)
{
	size = _v.size;
	count = _v.count;

	x = new T[size];
	for (int i = 0; i < size; i++)
		x[i] = _v.x[i];

	stacks = new TStack<T>[count];

	for (int i = 0; i < count; i++)
		stacks[i] = _v.stacks[i];
}

template<class T>
TMultiStack<T>::~TMultiStack()
{
	size = 0;
	count = 0;
	if (x != 0)
	{
		delete[] x;
		delete[] stacks;
		x = 0;
	}
}

template<class T>
inline TMultiStack<T>& TMultiStack<T>::operator=(TMultiStack<T>& _v)
{
	if (this == &_v)
		return *this;

	if (x != 0)
	{
		delete[] x;
		delete[] stacks;
	}

	size = _v.size;
	count = _v.count;

	stacks = new TStack<T>[count];
	x = new T[size];

	for (int i = 0; i < size; i++)
		x[i] = _v.x[i];

	for (int i = 0; i < count; i++)
		stacks[i] = _v.stacks[i];

	return *this;
}

template<class T>
void TMultiStack<T>::Push(T d, int i)
{
	if (i < 0 || i >= count)
		throw - 1;

	if (stacks[i].IsFull())
		StackRelocation(i);

	stacks[i].Push(d);
}

template<class T>
T TMultiStack<T>::Pop(int i)
{
	if (i < 0 || i >= count)
		throw - 1;
	return stacks[i].Pop();
}

template<class T>
inline bool TMultiStack<T>::IsEmpty(int i) const
{

	if ((i < 0) || (i >= count))
		throw logic_error("invalid_size");
	return stacks[i].IsEmpty();
}

template<class T>
inline bool TMultiStack<T>::IsFull(int i) const
{
	if ((i < 0) || (i >= count))
		throw logic_error("invalid_size");
	return stacks[i].IsFull();
}

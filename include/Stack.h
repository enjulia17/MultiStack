#pragma once

#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
	int length;
	T* data;
	int top;
	bool dataPresent;
public:
	TStack(int size = 1, bool _f = true);
	TStack(TStack<T>& _v);
	~TStack();

	TStack<T>& operator =(TStack<T>& _v);

	void Push(T d);
	T Pop();
	void SetData(T* _x, int size, int top_);

	void resize(int s)
	{
		T* newArr = new T[s];

		int temp = 0;
		if (s > length)
			temp = length;
		else
			temp = s;

		for (int i = 0; i < temp; i++)
			newArr[i] = data[i];

		length = s;
		delete[] data;
		data = newArr;
	}

	bool IsEmpty(void) const;
	bool IsFull(void) const;

	template <class T1>
	friend ostream& operator<< (ostream& ostr, const TStack<T1> &A);
	template <class T1>
	friend istream& operator >> (istream& istr, TStack<T1> &A);

	int GetSize();
	int GetCount();
};

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1> &A) {
	for (int i = 0; i < A.top; i++) {
		ostr << A.data[i] << endl;
	}
	return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1> &A) {
	int count;
	istr >> count;
	for (int i = 0; i < count; i++)
	{
		T1 d;
		istr >> d;
		A.Push(d);
	}
	return istr;
}

template<class T>
inline TStack<T>::TStack(int size, bool _f)
{
	if (size > 0)
	{
		this->length = size;
		this->dataPresent = _f;
		if (dataPresent)
		{
			data = new T[length];
			for (int i = 0; i < length; i++)
				data[i] = 0;
		}
		this->top = 0;
	}
	else
		throw - 1;
}

template <class T>
TStack<T>::TStack(TStack<T>& _v)
{
	length = _v.length;
	top = _v.top;
	dataPresent = _v.dataPresent;
	if (dataPresent)
	{
		data = new T[length];
		for (int i = 0; i < length; i = i + 1)
			data[i] = _v.data[i];
	}
	else
	{
		data = _v.data;
	}
}
template <class T>
TStack<T>::~TStack()
{
	length = 0;
	if (dataPresent)
		if (data != 0)
		{
			delete[] data;
			//data = 0;
		}
}

template <class T>
TStack<T>& TStack<T>::operator =(TStack<T>& _v)
{
	if (this == &_v)
		return *this;

	length = _v.length;
	dataPresent = _v.dataPresent;
	if (dataPresent)
	{
		delete[] data;
		data = new T[length];
		for (int i = 0; i < length; i++)
			data[i] = _v.data[i];
	}
	else
	{
		data = _v.data;
	}
	top = _v.top;
	return *this;
}

template<class T>
inline void TStack<T>::Push(T d)
{
	if (top >= length)
		throw - 1;

	data[top] = d;
	top++;
}

template<class T>
inline T TStack<T>::Pop()
{
	if (top == 0)
		throw - 1;

	T d = data[top - 1];
	top--;
	return d;
}

template<class T>
inline void TStack<T>::SetData(T* _x, int size, int top_)
{
	if (dataPresent)
		delete[] data;

	length = size;
	dataPresent = false;
	data = _x;
	top = top_;

}

template<class T>
inline bool TStack<T>::IsEmpty(void) const
{
	return (top == 0);
}

template<class T>
inline bool TStack<T>::IsFull(void) const
{
	return (top >= length);
}

template <class T>
int TStack<T>::GetSize()
{
	return length;
}

template<class T>
inline int TStack<T>::GetCount()
{
	return top;
}




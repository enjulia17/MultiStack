
#include <iomanip>
#include "Stack.h"
#include "MultiStack.h"
#include <stack>


int main() 
{
	TMultiStack<int> A(9, 3);
	A.Push(3, 0);
	A.Push(2, 1);
	A.Push(-1, 0);
	A.Push(5, 0);
	A.Push(6, 1);
	A.Push(-1, 0);
	A.Push(5, 0);
	return 0;
}

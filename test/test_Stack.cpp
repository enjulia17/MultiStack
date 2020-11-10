#include "Stack.h"

#include <gtest.h>

TEST(TStack, can_create_TStack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> v(13));
}

TEST(TStack, throws_when_create_TStack_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> v(-13));
}

TEST(TStack, IsFull)
{
	TStack<int>q(1);
	int t = 2;
	q.Push(t);
	EXPECT_EQ(q.IsFull(), 1);
}

TEST(TStack, IsEmpty)
{
	TStack<int>q(1);
	int t = 2;
	q.Push(t);
	q.Pop();
	EXPECT_EQ(q.IsEmpty(), 1);
}

TEST(TStack, can_create_copied_TStack)
{
 TStack<int> v(7);

  ASSERT_NO_THROW(TStack<int> v1(v));
}

TEST(TStack, can_get_size)
{
  TStack<int> v(12);

  EXPECT_EQ(v.GetSize(), 12);
}

TEST(TStack, can_push_and_pop)
{
	TStack<int> A(7);
	int q = 7;
	A.Push(q);
	EXPECT_EQ(A.Pop(), 7);
}

TEST(TStack, can_pop_with_any_size)
{
	TStack<int> A;
	ASSERT_ANY_THROW(A.Pop());
}

TEST(TStack, can_not_pop_out_of_size)
{
	TStack<int> A(13);
	ASSERT_ANY_THROW(A.Pop());
}
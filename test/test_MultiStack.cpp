#include "MultiStack.h"

#include <gtest.h>

TEST(multistack, can_create_multistack_by_default)
{
	ASSERT_NO_THROW(TMultiStack<int> A);
}

TEST(multistack, can_create_multistack)
{
	ASSERT_NO_THROW(TMultiStack<int> A(9, 2));
}

TEST(multistack, can_push_and_pop)
{
	TMultiStack<int> B(9, 3);
	B.Push(1, 0);
	B.Push(2, 1);
	B.Push(3, 2);
	EXPECT_EQ(1, B.Pop(0));
	EXPECT_EQ(2, B.Pop(1));
	EXPECT_EQ(3, B.Pop(2));
}

TEST(multistack, can_push_and_pop_out_of_size)
{
	TMultiStack<int> B(9, 3);
	B.Push(1, 0);
	B.Push(2, 0);
	B.Push(3, 0);
	B.Push(4, 0);
	EXPECT_EQ(4, B.Pop(0));
	EXPECT_EQ(3, B.Pop(0));
	EXPECT_EQ(2, B.Pop(0));
	EXPECT_EQ(1, B.Pop(0));
}

TEST(multistack, multisatck_is_empty)
{
	TMultiStack<char> B(8, 3);
	B.Push('U', 0);
	B.Push('O', 0);
	B.Push('Q', 1);
	B.Push('T', 1);

	ASSERT_ANY_THROW(B.Pop(2));
}

TEST(multistack, reallocation_works)
{
	TMultiStack<int> A(3, 3);
	A.Push(3, 0);
	A.Push(2, 1);
	A.Push(-1, 0);
	A.Push(5, 0);
	A.Push(6, 1);
	ASSERT_NO_THROW(A.Push(-1, 0));
}


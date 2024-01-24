#include "doktests.h"
#include "StaticQueue.h"

using IntQueue = StQueue<int>;

TEST_CASE("Defaut constructor makes an empty queue")
{
	IntQueue qu;
	CHECK(qu.empty());
}

TEST_CASE("Pushing element")
{
	SUBCASE("Pushing element in an empty queue")
	{
		IntQueue qu;
		qu.push(42);
		CHECK(qu.peek() == 42);
	}

	SUBCASE("Pushing multiple elements")
	{
		IntQueue qu;
		for (size_t i = 0; i < 10; i++)
		{
			qu.push(i);
		}
		CHECK(qu.peek() == 0);
	}
}

TEST_CASE("Poping Elements")
{
	SUBCASE("Pushing element and the poping gives as an empty queue")
	{
		IntQueue qu;
		qu.push(42);
		qu.pop();
		CHECK(qu.empty());
	}

	SUBCASE("Pushing the popingmultiple elements")
	{
		IntQueue qu;
		for (size_t i = 0; i < 10; i++)
		{
			qu.push(i);
			qu.pop();
		}
		CHECK(qu.empty());
	}
}

TEST_CASE("Copy constructor creates a valid copy") {
	IntQueue qu;
	qu.push(42);
	IntQueue mq(qu);

	CHECK(mq.peek() == 42);
}

TEST_CASE("Operator= creates a valid copy") {
	IntQueue qu;
	qu.push(42);
	IntQueue mq;
	mq.push(13);
	mq = qu;

	CHECK(mq.peek() == 42);
}


TEST_CASE("Move constructor creates the same Stack") {
	IntQueue qu;
	qu.push(42);
	IntQueue mq(std::move(qu));

	CHECK(mq.peek() == 42);
}

TEST_CASE("Move operator= creates the same Stack") {
	IntQueue qu;
	qu.push(42);
	IntQueue mq;
	mq.push(13);
	mq = std::move(qu);

	CHECK(mq.peek() == 42);
}



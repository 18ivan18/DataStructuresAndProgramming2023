#include "docktest.h"
#include "Stack.h"

using IntStack = Stack<int>;

TEST_CASE("Default constructor creates empty Stack") {
    IntStack s;
    CHECK(s.isEmpty());
}

TEST_CASE("Copy constructor creates a valid copy") {
    IntStack s;
    s.push(42);
    IntStack ms(s);

    CHECK(ms.top() == 42);
}

TEST_CASE("Operator= creates a valid copy") {
    IntStack s;
    s.push(42);
    IntStack ms;
    ms.push(13);
    ms = std::move(s);

    CHECK(ms.top() == 42);
}


TEST_CASE("Move constructor creates the same Stack") {
    IntStack s;
    s.push(42);
    IntStack ms(std::move(s));

    CHECK(ms.top() == 42);
}

TEST_CASE("Move operator= creates the same Stack") {
    IntStack s;
    s.push(42);
    IntStack ms;
    ms.push(13);
    ms = std::move(s);

    CHECK(ms.top() == 42);
}

TEST_CASE("Pushing an element creates a non-empty Stack") {
    IntStack s;
    s.push(42);
    CHECK(!s.isEmpty());
}

TEST_CASE("Top retrieves the element that was just pushed") {
    IntStack s;
    const int X = 24;
    s.push(X);
    CHECK(s.top() == X);
}

TEST_CASE("Pop after push preserves the Stack") {
    const int N = 10;

    SUBCASE("Pop after push preserves the empty Stack") {
        IntStack s;
        s.push(N);
        s.pop();
        CHECK(s.isEmpty());
    }

    SUBCASE("Pop after push preserves a non-empty Stack") {
        IntStack s;
        for (int i = 0; i < N; i++)
            s.push(i);

        s.push(N);
        s.pop();

        for (int i = N - 1; i >= 0; i--) {
            CHECK(s.top() == i);
            s.pop();
        }

        CHECK(s.isEmpty());
    }
}
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cmath>

struct Book
{
    std::string name, genre;

    bool operator==(const Book &other) const
    {
        return (name == other.name && genre == other.genre);
    }
};

std::istream &operator>>(std::istream &is, Book &object)
{
    is >> object.name >> object.genre;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Book &object)
{
    os << object.name << " " << object.genre;
    return os;
}

template <typename T, typename U>
struct Pair
{
    T first;
    U second;

    Pair(const T &first, const U &second) : first(first), second(second) {}
};

Pair<std::queue<Book>, std::queue<Book>> read(std::stack<Book> pile)
{
    std::queue<Book> to_read, for_next_pile;
    std::string previous_genre = "";

    while (!pile.empty())
    {
        Book book = pile.top();
        pile.pop();

        if (book.genre == previous_genre)
        {
            for_next_pile.push(book);
        }
        else
        {
            to_read.push(book);
            previous_genre = book.genre;
        }
    }

    return Pair<std::queue<Book>, std::queue<Book>>(to_read, for_next_pile);
}

bool can_read(const std::stack<Book> &pile, const int previous_size, const int max_difference)
{
    return (previous_size - pile.size()) <= max_difference;
}

Pair<bool, std::queue<Book>> read(std::queue<std::stack<Book>> piles, const int max_difference)
{
    bool all_read = true;
    std::queue<Book> to_read;
    int previous_size = piles.front().size();

    std::stack<Book> circle;

    while (!piles.empty() && all_read)
    {
        std::stack<Book> pile = piles.front();
        piles.pop();

        if (can_read(pile, previous_size, max_difference))
        {
            Pair<std::queue<Book>, std::queue<Book>> result = read(pile);

            std::queue<Book> to_read_from_pile = result.first, for_next_pile = result.second;
            previous_size = to_read_from_pile.size();

            while (!to_read_from_pile.empty())
            {
                to_read.push(to_read_from_pile.front());
                to_read_from_pile.pop();
            }

            while (!for_next_pile.empty())
            {
                piles.front().push(for_next_pile.front());
                for_next_pile.pop();
            }
        }
        else if (circle == pile)
        {
            all_read = false;
        }
        else
        {
            piles.push(pile);
            if (circle.empty())
            {
                circle = pile;
            }
        }
    }

    return Pair<bool, std::queue<Book>>(all_read, to_read);
}

int main()
{
    size_t n;
    int x;
    std::queue<std::stack<Book>> piles;

    std::cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        std::stack<Book> pile;
        size_t m;
        std::cin >> m;

        for (size_t j = 0; j < m; j++)
        {
            Book book;
            std::cin >> book;
            pile.push(book);
        }

        piles.push(pile);
    }
    std::cin >> x;

    Pair<bool, std::queue<Book>> result = read(piles, x);
    if (!result.first)
    {
        std::cout << "Not possible" << std::endl;
    }
    else
    {
        std::queue<Book> to_read = result.second;
        while (!to_read.empty())
        {
            std::cout << to_read.front() << std::endl;
            to_read.pop();
        }
    }
}
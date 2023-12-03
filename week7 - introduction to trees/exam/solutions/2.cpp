#include <iostream>

template <typename T>
struct DCLE
{
    T inf;
    DCLE<T> *prev, *next;
};

bool shouldFilter(DCLE<int> *head)
{
    return head->inf == head->next->inf + head->prev->inf;
}

// bool shouldFilter(DCLE<int> *head)
// {
//     return head->inf % head->next->inf == 0 && head->inf % head->prev->inf == 0;
// }

void deleteDCLE(DCLE<int> *&toBeDeleted)
{
    if (toBeDeleted == toBeDeleted->next)
    {
        delete toBeDeleted;
        toBeDeleted = nullptr;
        return;
    }

    DCLE<int> *prev = toBeDeleted->prev, *next = toBeDeleted->next;
    prev->next = next;
    next->prev = prev;
    delete toBeDeleted;
}

int size(DCLE<int> *head)
{
    DCLE<int> *node = head;
    int size = 0;
    do
    {
        size++;
        node = node->next;
    } while (node != head);
    return size;
}

DCLE<int> *filterList(DCLE<int> *head)
{
    int listSize = size(head), curr = 0;
    do
    {
        if (shouldFilter(head))
        {
            DCLE<int> *toBeDeleted = head;
            head = head->next;
            deleteDCLE(toBeDeleted);
            listSize--;
            curr = 0;
            continue;
        }
        head = head->next;
        curr++;
    } while (head && curr != listSize);

    return head;
}

void print(DCLE<int> *head)
{
    DCLE<int> *node = head;
    do
    {
        std::cout << node->inf << ' ';
        node = node->next;
    } while (node != head);
    std::cout << '\n';
}

DCLE<int> *insertAtEnd(DCLE<int> *head, int nextElem)
{
    if (!head)
    {
        DCLE<int> *h = new DCLE<int>{nextElem, nullptr, nullptr};
        h->next = h;
        h->prev = h;
        return h;
    }
    DCLE<int> *tail = head->prev, *next = new DCLE<int>{nextElem, tail, head};
    tail->next = next;
    head->prev = next;
    return head;
}

int main()
{
    DCLE<int> *head = insertAtEnd(nullptr, 5);
    insertAtEnd(head, 2);
    insertAtEnd(head, 4);
    insertAtEnd(head, 7);
    insertAtEnd(head, 1);
    insertAtEnd(head, 3);
    print(head);
    DCLE<int> *newHead = filterList(head);
    print(newHead);
}
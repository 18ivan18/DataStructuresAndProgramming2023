#ifndef STATIC_QUEUE_H_
#define STATIC_QUEUE_H_
#include <exception>

//template <typename T>
//struct Node
//{
//	T element;
//	Node* next;
//
//};

const unsigned MAX_SIZE = 1024;

template <typename T>
class StQueue
{
private:
	T elements[MAX_SIZE];
	int head;
	int end;

public:
	StQueue();
	void push(const T& element);
	void pop();
	const T& peek() const;
	bool empty() const;
	bool full() const;

};


#endif 

template<typename T>
StQueue<T>::StQueue():head(-1), end(-1)
{
}

template<typename T>
void StQueue<T>::push(const T& element)
{
	if (empty())
	{
		head = end = 0;
		elements[end] = element;
		return;
	}

	if (full())
	{
		throw std::exception("Can not push elements in a full stack");
	}

	end = (end + 1) % MAX_SIZE;
	elements[end] = element;

}

template<typename T>
void StQueue<T>::pop()
{
	if (empty())
	{
		throw std::exception("Can not pop elements in an empty stack");
	}

	if (head == end)
	{
		head = -1;
		return;
	}

	head = (head + 1) % MAX_SIZE;
}

template<typename T>
const T& StQueue<T>::peek() const
{
	if (empty())
	{
		throw std::exception("Can not see the top element in an empty stack");
	}
	
	return elements[head];
}

template<typename T>
bool StQueue<T>::empty() const
{
	return head == -1;
}

template<typename T>
inline bool StQueue<T>::full() const
{
	return ((end + 1) % MAX_SIZE  == head);
}

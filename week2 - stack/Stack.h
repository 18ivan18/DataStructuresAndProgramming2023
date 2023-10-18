#ifndef ARRAY_STACK_H_
#define ARRAY_STACK_H_
#include <iostream>

static const unsigned INITIAL_CAPACITY = 16;

template <typename T>
class Stack
{
private:
	T* data;
	unsigned capacity;
	int topIndex;

	void copy(const Stack& other);   // Copy a stack
	void erase();       // delete alocated memmory
	bool full();  // Shows if the stack is full
	void resize(unsigned newCapacity);      
	
public:
	//          Rulе of five        //
	Stack();
	Stack(const Stack& other);
	Stack& operator =(const Stack& other);
	Stack(Stack&& other);
	Stack& operator =(Stack&& other);
	~Stack();

	void push(const T& element);
	bool pop();
	const T& top() const;
	bool isEmpty() const;

};


#endif 

template<typename T>
void Stack<T>::copy(const Stack& other)
{
	data = new T[other.capacity];

	for (size_t i = 0; i <= other.topIndex; i++)
	{
		data[i] = other.data[i];
	}

	topIndex = other.topIndex;
	capacity = other.capacity;
}

template<typename T>
void Stack<T>::erase()
{
	delete[] data;
	data = nullptr;
}

template<typename T>
bool Stack<T>::full()
{
	int tempCapacity = capacity;
	return (topIndex >= tempCapacity - 1);
}

template<typename T>
void Stack<T>::resize(unsigned newCapacity)
{
	if (capacity >= newCapacity)
	{
		throw std::exception("Can not have fewer elements then before!");
	}

	T* tempSt = new T[newCapacity];

	for (int i = 0; i <= topIndex; i++)
	{
		tempSt[i] = data[i];
	}

	erase();
	capacity = newCapacity;
	data = tempSt;
}

template<typename T>
Stack<T>::Stack() :topIndex(-1), capacity(INITIAL_CAPACITY)
{ 
	data = new T[capacity];
}

template<typename T>
Stack<T>::Stack(const Stack& other)
{
	copy(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
	if (this != &other)
	{
		erase();
		copy(other);
	}

	return *this;
}

template<typename T>
Stack<T>::Stack(Stack&& other)
{
	capacity = other.capacity;
	topIndex = other.topIndex;
	data = other.data;

	other.capacity = 0;
	other.topIndex = 0;
	other.data = nullptr;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other)
{
	if (this != &other)
	{
		erase();
		capacity = other.capacity;
		topIndex = other.topIndex;
		data = other.data;

		other.capacity = 0;
		other.topIndex = 0;
		other.data = nullptr;
	}

	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	erase();
}

template<typename T>
void Stack<T>::push(const T& element)
{
	if (full())
	{
		resize(capacity * 2);
	}

	data[++topIndex] = element;
}

template<typename T>
bool Stack<T>::pop()
{
	if (isEmpty())
	{
		return false;
	}

	else
	{
		--topIndex;
		return true;
	}
}

template<typename T>
const T& Stack<T>::top() const
{
	if (isEmpty())
	{
		throw std::runtime_error("The stack is empty!");
	}

	else
	{
		return data[topIndex];
	}
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return topIndex == -1;
}

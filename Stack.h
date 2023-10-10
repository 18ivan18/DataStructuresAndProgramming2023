#ifndef RESSTACK_H_
#define RESSTACK_H_

const unsigned BEGINNING_CAPACITY = 16;

template <typename T>
class Stack
{
private:
	T* st;
	unsigned capacity;
	int topIndex;

	void copy(const Stack& other);   // Copy a stack
	void erase();       // delete alocated memmory
	bool almostFull();  // Shows if the stack is 75% full
	void resize();      
	
public:
	//          Rulе of five        //
	Stack();
	Stack(const Stack& other);
	Stack& operator =(const Stack& other);
	Stack(Stack&& other);
	Stack& operator =(Stack&& other);
	~Stack();

	void push(const T& elem);
	bool pop();
	const T& top() const;
	bool isEmpty() const;

};


#endif 

template<typename T>
void Stack<T>::copy(const Stack& other)
{
	st = new T[other.capacity];

	for (size_t i = 0; i <= other.topIndex; i++)
	{
		st[i] = other.st[i];
	}

	topIndex = other.topIndex;
	capacity = other.capacity;
}

template<typename T>
void Stack<T>::erase()
{
	delete[] st;
	st = nullptr;
}

template<typename T>
bool Stack<T>::almostFull()
{
	int quoter = 3 * capacity / 4;
	return (topIndex > quoter);
}

template<typename T>
void Stack<T>::resize()
{
	T* tempSt = new T[capacity * 2];

	for (size_t i = 0; i <= topIndex; i++)
	{
		tempSt[i] = st[i];
	}

	erase();
	capacity *= 2;
	st = tempSt;
}

template<typename T>
Stack<T>::Stack() :topIndex(-1), capacity(BEGINNING_CAPACITY) /*st(new T[capacity])*/
{ 
	st = new T[capacity]; 
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
	st = other.st;

	other.capacity = 0;
	other.topIndex = 0;
	other.st = nullptr;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other)
{
	if (this != &other)
	{
		capacity = other.capacity;
		topIndex = other.topIndex;
		st = other.st;

		other.capacity = 0;
		other.topIndex = 0;
		other.st = nullptr;
	}

	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	erase();
}

template<typename T>
void Stack<T>::push(const T& elem)
{
	if (almostFull())
		resize();
	st[++topIndex] = elem;
}

template<typename T>
bool Stack<T>::pop()
{
	if (isEmpty())
		return false;
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
		throw std::runtime_error("The stack is empty!");
	else
		return st[topIndex];
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return topIndex == -1;
}

#ifndef LINKED_STAK_H_
#define LINKED_STACK_H_
#include <exception>

template <typename T>
struct StackElement {
	T element;
	StackElement<T>* link;

};


template <typename T>
class LStack
{
private:
	StackElement<T>* topPtr;

	void copy(const LStack& other);
	void erase();

public:
	//     Rule of 5     //
	LStack();
	LStack(const LStack& other);
	LStack& operator = (const LStack& other);
	LStack(LStack&& other);
	LStack& operator = (LStack&& other);
	~LStack();

	void push(const T& elem);
	void pop();
	const T& top() const;
	T& top();
	bool empty() const;

};




#endif 

template<typename T>
void LStack<T>::copy(const LStack& other)
{
	if (other.empty())
	{
		topPtr = nullptr;
		return;
	}
	
	topPtr = new StackElement<T>;
	topPtr->element = other.topPtr->element;
	topPtr->link = nullptr;
	
	StackElement<T>* lastAddedElement = topPtr;
	StackElement<T>* nextElementToAdd = other.topPtr->link;

	while (nextElementToAdd)
	{
		lastAddedElement = new StackElement<T>;
		lastAddedElement->element = nextElementToAdd->element;
		lastAddedElement->link = nullptr;
		nextElementToAdd = nextElementToAdd->link;
	}
}

template<typename T>
void LStack<T>::erase()
{
	while (!empty())
	{
		pop();
	}
}

template<typename T>
LStack<T>::LStack(): topPtr(nullptr)
{
}

template<typename T>
LStack<T>::LStack(const LStack& other)
{
	copy(other);
}

template<typename T>
LStack<T>& LStack<T>::operator=(const LStack& other)
{
	if (this != &other)
	{
		erase();
		copy(other);
	}

	return *this;
}

template<typename T>
LStack<T>::LStack(LStack&& other)
{
	topPtr = other.topPtr;

	other.topPtr = nullptr;
}

template<typename T>
LStack<T>& LStack<T>::operator=(LStack&& other)
{
	if (this != &other)
	{
		erase();
		topPtr = other.topPtr;

		other.topPtr = nullptr;
	}

	return *this;
}

template<typename T>
inline LStack<T>::~LStack()
{
	erase();
}

template<typename T>
void LStack<T>::push(const T& elem)
{
	StackElement<T>* newElement = new StackElement<T>;
	newElement->link = topPtr;
	topPtr = newElement;
	newElement->element = elem;
}

template<typename T>
void LStack<T>::pop()
{
	if (empty())
	{
		throw std::exception("Can not pop elements from an empty stack!");
	}

	StackElement<T>* tempPtr = topPtr;
	topPtr = topPtr->link;
	delete tempPtr;
}

template<typename T>
const T& LStack<T>::top() const
{
	if (empty())
	{
			throw std::exception("Can not see the top elements in an empty stack!");
	}

	return topPtr->element;
}

template<typename T>
T& LStack<T>::top()
{
	if (empty())
	{
		throw std::exception("Can not see the top elements in an empty stack!");
	}

	return topPtr->element;
}

template<typename T>
bool LStack<T>::empty() const
{
	return topPtr == nullptr;
}

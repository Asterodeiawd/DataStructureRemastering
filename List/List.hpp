#pragma once
#include <ostream>
#include <stdexcept>
#define NAMESPACE_START(name) namespace name{
#define NAMESPACE_END }
#define MAX_LIST_COUNT (200)

NAMESPACE_START(myLibrary)

template<typename T>
class ListNode 
{
	typedef T value_type;
private:
	T data;
	ListNode<T>* prev;
	ListNode<T>* next;

public:
	ListNode(T value, ListNode<T>* prev = nullptr, ListNode<T>* next = nullptr) :
		data(value), prev(prev), next(next)
	{}
};

template<typename T>
class List
{
	typedef T value_type;
	typedef ListNode<T> value_cell;

	// operator overrides
	friend std::ostream& operator<< <T> (std::ostream& os, const List<T>& list);

private:
	ListNode<T>* head;
	size_t count;

public:
	List();
	List(T* array, size_t count);
	~List();
	List(const List<T>& rhs);

	size_t size() const;
	bool isFull() const;
	bool isEmpty() const;

	ListNode<T>* find(T value) const;
	List<T>& insert(ListNode<T>* iter, T value);
	List<T>& append(T value);
	List<T>& remove(T value);
	List<T>& clear();
	ListNode<T>* createNode(T value, ListNode<T>* prev = nullptr, ListNode<T>* next = nullptr);
	void _createSentinel();

};

template<typename T>
ListNode<T>* List<T>::createNode(T value, ListNode<T>* prev, ListNode<T>* next)
{
	ListNode<T>* ret = new ListNode<T>(value, prev, next);

	if (ret == nullptr)
		throw std::bad_alloc("out of memory!");

	return ret;
}

template <typename T>
void List<T>::_createSentinel()
{
	ListNode<T>* sentinel = createNode(T());

	// since we have two pointers now, point prev of sentinel to the tail of List<T>.
	// Ahh, I changed my mind, I won't do this!

	// sentinel->prev = sentinel;

	head = sentinel;
}

template <typename T>
List<T>& List<T>::clear()
{
	ListNode<T>* walk = head->next;


}

template<typename T>
size_t List<T>::size() const
{
	return count;
}

template<typename T>
bool List<T>::isEmpty() const
{
	return count == 0;
}

template<typename T>
bool List<T>::isFull() const
{
	return count == MAX_LIST_COUNT;
}

template<typename T>
ListNode<T>* List<T>::find(T value) const
{
	ListNode<T>* walk = head->next;

	while (walk != nullptr && walk->data != value))
		walk = walk->next;

	// this will work both find or not find the target value
	return walk;

}

template <typename T>
List<T>& List<T>::append(T value)
{
	ListNode<T>* tail = head->prev;

	ListNode<T>* newNode = createNode(value);

	head->prev = newNode;
	tail->next = newNode;
	newNode->prev = tail;

	++count;

	return *this;
}

template <typename T>
List<T>& List<T>::remove(T value)
{
	ListNode<T>* pos = find(value);
	if (pos != nullptr)
	{
		pos->prev->next = pos->next;

		if (pos->next != nullptr)
			pos->next->prev = pos->prev;

		delete tmp;
	}
}

template <typename T>
List<T>& List<T>::insert(ListNode<T>* iter, T value)
{
	ListNode<T>* newNode = createNode(value);
	newNode->next = iter;
	newNode->prev = iter->prev;

	iter->prev->next = newNode;
	iter->prev = newNode;

	return *this;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const List<T>& list)
{
	if (list.isEmpty())
		os << "empty list";
	else
	{
		ListNode<T>* walk = list.head->next;

		os << "[ ";
		while (walk != nullptr)
		{
			os << walk->data << ", ";
			walk = walk->next;
		}


		os << "]" << std::endl;
	}

	return os;
}
NAMESPACE_END
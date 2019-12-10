#pragma once
#define MAX_ITEM_COUNT (200)

#include <list>
#include <stdexcept>
#include <ostream>

template<typename T>
class ForwardList;

template<typename T>
std::ostream& operator<< (std::ostream& os, const ForwardList<T>& list);

template<typename T>
class ListNode
{
	typedef T value_type;
	friend class ForwardList<T>;
	friend std::ostream& operator<< <T> (std::ostream& os, const ForwardList<T>& list);
private:
	T data;
	ListNode<T>* next;
public:
	ListNode(T value, ListNode<T>* next = nullptr);
};

template<typename T>
ListNode<T>::ListNode(T value, ListNode<T>* next):
	data(value), next(next)
{}

// no sentinel version
template<typename T>
class ForwardList
{
	typedef T value_type;
	friend std::ostream& operator<< <T> (std::ostream& os, const ForwardList<T>& list);

private:
	ListNode<T>* head;
	// size_t count;
public:


	// insert value *AT* the position, 
	// original value at position will be move backward.
	ForwardList<T>& insert(T value, ListNode<T>* position);
	ForwardList<T>& remove(T value);
	ForwardList<T>& append(T value);
	ListNode<T>* find(T value) const;

	bool isFull() const;
	bool isEmpty() const;
	size_t count() const;

	ForwardList(T* array, size_t count);
	ForwardList();

	~ForwardList();
	
	// todo: copy constructor should be implemented!
};

template<typename T>
ForwardList<T>::~ForwardList()
{
	if (head == nullptr)
		return;

	ListNode<T>* walk = head;
	ListNode<T>* tmp = nullptr;

	while (head != nullptr)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}

}
template<typename T>
bool ForwardList<T>::isFull() const
{
	return count() > MAX_ITEM_COUNT;
}

template<typename T>
bool ForwardList<T>::isEmpty() const
{
	return head == nullptr;
}

template<typename T>
size_t ForwardList<T>::count() const
{
	ListNode<T>* walk = head;
	size_t count = 0;

	while (walk != nullptr)
	{
		++count;
		walk = walk->next;
	}

	return count;
}

// position is 0-based, use this function after using find() which give a pointer to the item 
// you want to insert before.
template<typename T>
ForwardList<T>& ForwardList<T>::insert(T value, ListNode<T>* position)
{
	// don't need to consider the case of an empty list, cause empty list can't use find()
	// only two condition should be taken care: insert before the first item or not.


	ListNode<T>* tmp = new ListNode<T>(value);

	if (position == head)
	{
		tmp->next = head;
		head = tmp;
	}
	else
	{
		ListNode<T>* walk = head;
		// find the previous node
		while (walk->next != position)
			walk = walk->next;

		tmp->next = walk->next;
		walk->next = tmp;
	}

	return *this;
}

// unlike stl list, this function remove ONLY the first value item
template<typename T>
ForwardList<T>& ForwardList<T>::remove(T value)
{
	// no sentinel, have to check head is nullptr or not
	if (isEmpty())
		return *this;

	ListNode<T>* walk = head;
	ListNode<T>* prev = head;

	while (walk != nullptr && walk->data != value)
	{
		prev = walk;
		walk = walk->next;
	}
	
	// no such item
	if (walk == nullptr)
		return *this;

	if (walk == head)
	{
		head = head->next;
		delete prev;
	}
	else
	{
		prev->next = walk->next;
		delete walk;
	}

	return *this;

}

template<typename T>
ForwardList<T>& ForwardList<T>::append(T value)
{
	ListNode<T>* newNode = new ListNode<T>(value);
	ListNode<T>* walk = head;

	if (head == nullptr)
		head = newNode;
	else
	{
		while (walk->next != nullptr)
			walk = walk->next;

		walk->next = newNode;
	}

	return *this;
}


template<typename T>
ListNode<T>* ForwardList<T>::find(T value) const
{
	ListNode<T>* walk = head;

	if (isEmpty())
		return nullptr;

	while (walk != nullptr && walk->data != value)
		walk = walk->next;

	if (walk == nullptr)
		return nullptr;
	else
		return walk;
}

template<typename T>
ForwardList<T>::ForwardList(T* array, size_t n) : head(nullptr)
{
	for (size_t i = 0; i < n; ++i)
	{
		append(array[i]);
	}
}

template<typename T>
ForwardList<T>::ForwardList() : head(nullptr)
{}

template<typename T>
std::ostream& operator<< (std::ostream& os, const ForwardList<T>& list)
{
	if (list.isEmpty())
		os << "empty list";
	else
	{
		ListNode<T>* walk = list.head;

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

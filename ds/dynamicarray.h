#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <common.h>

template <typename T>
struct ArrayNode
{
	T* data;
	size_t size;
	ArrayNode<T>* next;
	ArrayNode(size_t mallocSize)
	{
		data = new T[mallocSize];
		size = mallocSize;
		next = nullptr;
	}
	ArrayNode()
	{
		data = nullptr;
		size = 0;
		next = nullptr;
	}
	~ArrayNode()
	{
		if (data != nullptr) delete[] data; data = nullptr;
	}
};

template <typename T>
class Array
{
	typedef ArrayNode<T> U;
private:
	U* head;
	void releaseListFrom(U* node)
	{
		U* ptr = head;
		if (head == nullptr) return;
		while (ptr != node && ptr != nullptr)
		{
			ptr = ptr->next;
		}
		if (ptr == nullptr) return;
		while (ptr != nullptr)
		{
			U* cur = ptr;
			ptr = ptr->next;
			delete[] cur;
			cur = nullptr;
		}
	}
	U* rear()
	{
		U* ptr = head;
		if (head == nullptr) return nullptr;
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
		}
		return ptr;
	}
	void appendNode(size_t size)
	{
		U* rear = rear();
		U* tmp = new U(size);
		rear->next = tmp;
	}
public:
	Array(size_t initSize)
	{
		head = new U(initSize);
	}
	~Array()
	{
		releaseListFrom(head);
	}
	T& operator[](size_t i) // return reference
	{
		if (head == nullptr) return nullptr;
		size_t high = head->size;
		size_t low = 0;
		U* ptr = head;
		while (i >= high && ptr->next != nullptr)
		{
			low += ptr->size;
			ptr = ptr->next;
			high += ptr->size;
		}
		if (i >= high) return nullptr;
		return ptr->data[i - low];
	}
};

#endif // !DYNAMIC_ARRAY_H
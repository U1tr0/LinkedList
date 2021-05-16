#pragma once
#include <iostream>

using ValueType = double;

class LinkedList
{
	struct Node {
		Node(const ValueType& value, Node* next = nullptr);
		~Node() = default;

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType _value;
		Node* _next;
	};

	struct Iterator {
    public:
        Iterator(Node* ptr, size_t idx = 0);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        ValueType& operator*() const;
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);

        size_t getIndex() const;
        Node* getPtr() const;
    private:
        Node* _ptr;
        size_t _index;
    };

public:

    Iterator begin();
    Iterator end() noexcept;

	LinkedList();
	LinkedList(const LinkedList& copyList);
	LinkedList& operator=(const LinkedList& copyList);

	LinkedList(LinkedList&& moveList) noexcept;
	LinkedList& operator=(LinkedList&& moveList) noexcept;

	~LinkedList();

	const ValueType& operator[](const size_t pos) const;
	ValueType& operator[](const size_t pos);
	LinkedList::Node* getNode(const size_t pos) const;

	void insert(const size_t pos, const ValueType& value);
	void insertAfterNode(Node* node, const ValueType& value);
	void pushBack(const ValueType& value);
	void pushFront(const ValueType& value);

	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	void reverse();
	LinkedList reverse() const;
	LinkedList getReverseList() const;

	size_t size() const;
	void clear();
private:
	Node*	_head;
	size_t	_size;

	void forceNodeDelete(Node* node);
};

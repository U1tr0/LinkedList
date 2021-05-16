#include "List.h"

#include <cassert>

LinkedList::Node::Node(const ValueType& value, Node* next) {
	_value = value;
	_next = next;
}

void LinkedList::Node::insertNext(const ValueType& value) {
	Node* newNode = new Node(value, _next);
	_next = newNode;
}

void LinkedList::Node::removeNext() {
	Node* removeNode = _next;
	Node* newNext = removeNode->_next;
	delete removeNode;
	_next = newNext;
}

LinkedList::LinkedList() {
    _head = nullptr;
    _size = 0;
}

LinkedList::LinkedList(const LinkedList& other) {
	_size = other._size;
	if(_size == 0) {
            _head = nullptr;
	}
	else {
        _head = new Node(other._head->_value);
        Node* cur = _head;
        Node* curCopy = other._head;
        while (curCopy->_next) {
			cur->_next = new Node(curCopy->_next->_value);
			curCopy = curCopy->_next;
			cur = cur->_next;
		}
	}
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
	this->clear();
    _size = other._size;
    _head = nullptr;
    if (_size > 0) {
        Node* temp = other._head;
        Node* tempNew = new Node(temp->_value);
        Node* nextNew = nullptr;
        _head = tempNew;
        temp = temp->_next;
        while (temp != nullptr) {
            nextNew = new Node(temp->_value);
            tempNew->_next = nextNew;
            tempNew = nextNew;
            temp = temp->_next;
        }
    }
    return *this;
}

LinkedList::LinkedList(LinkedList&& other) noexcept {
	this->_size = other._size;
	this->_head = other._head;
	other._size = 0;
	other._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept {
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

LinkedList::~LinkedList() {
	forceNodeDelete(_head);
}

const ValueType& LinkedList::operator[](const size_t pos) const {
	return getNode(pos)->_value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const {
	if (pos < 0) {
		throw std::out_of_range("pos < 0");
	}
	else if (pos >= _size) {
		throw std::out_of_range("pos >= size");
	}
	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->_next;
	}
	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value) {
	if (pos < 0) {
		throw std::out_of_range("pos < 0");
	}
	else if (pos > this->_size) {
		throw std::out_of_range("pos > 0");
	}
	if (pos == 0) {
		pushFront(value);
	}
	else {
        Node* temp = _head;
        for(size_t i = 1; i < pos; i++) {
            temp = temp->_next;
        }
        Node* newNode = new Node(value, temp->_next);
        temp->_next = newNode;
        _size++;
	}
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value) {
	node->insertNext(value);
	_size++;
}

void LinkedList::pushBack(const ValueType& value) {
	if(_size == 0) {
        _head = new Node(value, _head);
	}
	else {
        insert(_size, value);
	}
}

void LinkedList::pushFront(const ValueType& value) {
	_head = new Node(value, _head);
	++_size;
}

void LinkedList::remove(const size_t pos) {
    if(pos > _size) {
        throw std::out_of_range("pos > _size");
    }
    if(pos < 0) {
        throw std::out_of_range("pos < 0");
    }
	if (pos == 0) {
            removeFront();
	}
	else {
		Node* temp = _head;
		for (size_t i = 0; i < pos - 1; i++) {
			temp = temp->_next;
		}
		temp->removeNext();
		_size--;
	}

}

void LinkedList::removeFront() {
	if(_size == 1) {
		delete _head;
		_head = nullptr;
		_size = 0;
	}
	else {
        Node* temp = _head->_next;
        delete _head;
        _head = temp;
        _size--;
	}
}

void LinkedList::removeBack() {
	if (_size > 1) {
        getNode(_size - 2)->removeNext();
        _size--;
    }
	else {
        removeFront();
	}
}


void LinkedList::removeNextNode(Node* node) {
    node->removeNext();
	_size--;
}

long long int LinkedList::findIndex(const ValueType& value) const {
    Node* temp = this-> _head;
	for (size_t i = 0; i < _size; i++) {
		if (temp->_value == value){
          return i;
        }
		temp = temp->_next;
	}
	return -1;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const {
    Node* temp = this->_head;
	for (size_t i = 0; i < _size; i++)
	{
		if (temp->_value == value){
            return temp;
		}
		temp = temp->_next;
	}
	return nullptr;
}

void LinkedList::reverse() {
    Node* prev = nullptr;
	Node* cur = _head;
	Node* next = _head->_next;
	while (next != nullptr) {
		cur->_next = prev;
		prev = cur;
		cur = next;
		next = cur->_next;
	}
	cur->_next = prev;
	_head = cur;
}

LinkedList LinkedList::reverse() const {
    LinkedList* newList = new LinkedList;
	*newList = *this;
	newList->reverse();

	return *newList;
}

LinkedList LinkedList::getReverseList() const {
    LinkedList* newList = new LinkedList;
	*newList = *this;
	newList->reverse();

	return *newList;
}

size_t LinkedList::size() const {
	return _size;
}

void LinkedList::forceNodeDelete(Node* node) {
	if (node == nullptr) {
		return;
	}
	Node* nextDeleteNode = node->_next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}

void LinkedList::clear() {
    while (_head != nullptr) {
        this->removeFront();
    }
    _size = 0;
}

LinkedList::Iterator::Iterator(Node* ptr, size_t idx) {
    _ptr = ptr;
    _index = idx;
}

LinkedList::Iterator::Iterator(const Iterator& other) {
    _ptr = other._ptr;
    _index = other._index;
}

LinkedList::Iterator& LinkedList::Iterator::operator=(const Iterator& other) {
    _ptr = other._ptr;
    _index = other._index;
    return *this;
}

ValueType& LinkedList::Iterator::operator*() const {
    return _ptr->_value;
}

bool LinkedList::Iterator::operator!=(const LinkedList::Iterator& other) const {
    return (this->_ptr != other._ptr);
}

bool LinkedList::Iterator::operator==(const LinkedList::Iterator& other) const {
    return (this->_ptr == other._ptr);
}

LinkedList::Iterator& LinkedList::Iterator::operator++() {
    this->_ptr = this->_ptr->_next;
    this->_index++;
    return *this;
}

LinkedList::Iterator LinkedList::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

size_t LinkedList::Iterator::getIndex() const {
    return this->_index;
}

LinkedList::Iterator LinkedList::begin() {
    return Iterator(_head, 0);
}

LinkedList::Iterator LinkedList::end() noexcept {
    return Iterator(nullptr, -1);
}


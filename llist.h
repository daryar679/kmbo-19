#ifndef LLIST_H
#define LLIST_H

#include <cstddef>

template<typename ValueType> 
class LList
{
	struct Node {
		Node(const ValueType& value, Node* next = nullptr);
		~Node();

		void insertNext(const ValueType& value);

		int value;
		Node* next;
	};

public:

	LList();                         // construct new collection
	LList(const LList& copyList);
	LList& operator=(const LList& copyList);
	LList(LList&& moveList) noexcept;
	LList& operator=(LList&& moveList) noexcept;
	~LList();                        // free resources

	LList::Node* getNode(const size_t idx) const;
	void push_back(ValueType val);         // add new value at the end:  [1 2 3 4] -> [1 2 3 4 5]
	void push_front(ValueType val);        // add new value at the begin [1 2 3 4] -> [5 1 2 3 4]
	void pop_back();          // remove at the end          [1 2 3 4] -> [1 2 3]
	void pop_front();         // remove at the front        [1 2 3 4] -> [2 3 4]
	size_t size() const;             // get actual number of items [1 2 3 4] -> 4
	ValueType& operator[](size_t idx);     // get rw access ot specific item addressing by idx
	ValueType  operator[](size_t idx) const; //get read-only access
	void erase_at(size_t idx);       // remove item at specific position: [1 2 3 4], 2 -> [1 2 4]
	void insert_at(size_t idx, ValueType val); // insert item at specific position: [1 2 3 4], 1, 5 -> [1 5 2 3 4]
	void reverse();                  // reverse item sequense: [1 2 3 4] -> [4 3 2 1]

private:
	Node* _head;
	size_t	_size;

	void forceNodeDelete(Node* node);
};
template<typename ValueType>
LList<ValueType>::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

template<typename ValueType>
LList<ValueType>::Node::~Node()
{
}

template<typename ValueType>
void LList<ValueType>::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

template<typename ValueType>
LList<ValueType>::LList()
	: _head(nullptr), _size(0)
{

}

template<typename ValueType>
LList<ValueType>::LList(const LList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentCopyNode = currentCopyNode->next;
		currentNode->next = new Node(currentCopyNode->value);
		currentNode = currentNode->next;
	}
}

template<typename ValueType>
LList<ValueType>& LList<ValueType>::operator=(const LList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	LList bufList(copyList);
	forceNodeDelete(_head);
	this->_size = bufList._size;
	this->_head = bufList._head;

	return *this;
}

template<typename ValueType>
LList<ValueType>::LList(LList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

template<typename ValueType>
LList<ValueType>& LList<ValueType>::operator=(LList&& moveList) noexcept
{
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

template<typename ValueType>
LList<ValueType>::~LList()
{
	forceNodeDelete(_head);
}

template<typename ValueType>
LList<ValueType>::Node* LList<ValueType>::getNode(const size_t idx) const
{
	if (idx < 0) {
		assert(idx < 0);
	}
	else if (idx >= this->_size) {
		assert(idx >= this->_size);
	}

	Node* bufNode = this->_head;
	for (int i = 0; i < idx; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

template<typename ValueType>
void LList<ValueType>::push_back(ValueType val)
{
	if (_size == 0) {
		push_front(val);
		return;
	}
	insert_at(_size, val);
}

template<typename ValueType>
void LList<ValueType>::push_front(ValueType val)
{
	_head = new Node(val, _head);
	++_size;
}

template<typename ValueType>
void LList<ValueType>::pop_back()
{
	erase_at(_size - 1);
}

template<typename ValueType>
void LList<ValueType>::pop_front()
{
	erase_at(0);
}

template<typename ValueType>
size_t LList<ValueType>::size() const
{
	return _size;
}

template<typename ValueType>
ValueType& LList<ValueType>::operator[](size_t idx)
{
	return getNode(idx)->value;
}

template<typename ValueType>
ValueType LList<ValueType>::operator[](size_t idx) const
{
	return getNode(idx)->value;
}

template<typename ValueType>
void LList<ValueType>::erase_at(size_t idx)
{
	if (idx < 0) {
		assert(idx < 0);
	}
	else if (idx > this->_size) {
		assert(idx > this->_size);
	}

	if (idx == 0)
	{
		Node* bufNode = _head;
		_head = _head->next;
		delete bufNode;
	}
	else
	{
		Node* bufNode = this->_head;
		for (size_t i = 0; i < idx - 1; ++i) {
			bufNode = bufNode->next;
		}
		Node* deleteNode = bufNode->next;
		bufNode->next = deleteNode->next;
		delete deleteNode;
	}
	_size--;
}

template<typename ValueType>
void LList<ValueType>::insert_at(size_t idx, ValueType val)
{
	if (idx < 0) {
		assert(idx < 0);
	}
	else if (idx > this->_size) {
		assert(idx > this->_size);
	}

	if (idx == 0) {
		push_front(val);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < idx - 1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(val);
		++_size;
	}
}

template<typename ValueType>
void LList<ValueType>::reverse()
{
	Node* bufNode = _head;
	Node* next = nullptr;
	Node* prev = nullptr;
	while (bufNode != nullptr)
	{
		next = bufNode->next;
		bufNode->next = prev;
		prev = bufNode;
		bufNode = next;
	}
	_head = prev;
}

template<typename ValueType>
void LList<ValueType>::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}
	Node* deleteNode = node;
	while (deleteNode)
	{
		Node* nextDeleteNode = deleteNode->next;
		delete deleteNode;
		node = deleteNode;
	}
}
#endif 

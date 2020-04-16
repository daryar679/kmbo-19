#include "LList.h"
#include <cassert>

LList::Node::Node(const int& value, Node* next)
{
	this->value = value;
	this->next = next;
}

LList::Node::~Node()
{
}

void LList::Node::insertNext(const int& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

LList::LList()
	: _head(nullptr), _size(0)
{

}

LList::~LList()
{
	forceNodeDelete(_head);
}

LList::Node* LList::getNode(const size_t idx) const
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

void LList::push_back(int val)
{
	if (_size == 0) {
		push_front(val);
		return;
	}
	insert_at(_size, val);
}

void LList::push_front(int val)
{
	_head = new Node(val, _head);
	++_size;
}

void LList::pop_back(int val)
{
	erase_at(_size-1);
}

void LList::pop_front(int val)
{
	erase_at(0);
}

size_t LList::size() const
{
	return _size;
}

int& LList::operator[](size_t idx)
{
	return getNode(idx)->value;
}

int LList::operator[](size_t idx) const
{
	return getNode(idx)->value;
}

void LList::erase_at(size_t idx)
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

void LList::insert_at(size_t idx, int val)
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

void LList::reverse()
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

void LList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}



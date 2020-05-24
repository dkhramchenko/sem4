#include "Node.h"

// конструктор
Node::Node(std::string const& key, std::string const& value)
{
	this->key += key;
	this->value += value;
	parent = nullptr;
	leftChild = nullptr;
	rightChild = nullptr;
	balanceFactor = 0;
}
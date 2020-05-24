#include "Set.h"
#include "Node.h"
#include <algorithm>

// конструктор
Set::Set()
{
	head = nullptr;
}

// деструктор
Set::~Set()
{
	if (head != nullptr)
	{
		deleteRecursion(head);
	}
}

// удаление элемента по ключу
void Set::deleteRecursion(Node* current)
{
	if (current->leftChild != nullptr)
	{
		deleteRecursion(current->leftChild);
	}
	if (current->rightChild != nullptr)
	{
		deleteRecursion(current->rightChild);
	}
	delete current;
}

// добавление значения по ключу
void Set::addValueByKey(std::string const& key, std::string const& value)
{
	if (isEmpty())
	{
		head = new Node(key, value);
		return;
	}
	bool ifKeyExists = keyExists(key);
	if (ifKeyExists)
	{
		addIfKeyExists(key, value, head);
		return;
	}
	auto* added = addRecurson(key, value, head);
	balance(added);
}

// добавление, если такой ключ есть
void Set::addIfKeyExists(std::string const& key, std::string const& value, Node* current)
{
	if (key == current->key)
	{
		current->value = value;
	}
	else if (key < current->key)
	{
		addIfKeyExists(key, value, current->leftChild);
	}
	else
	{
		addIfKeyExists(key, value, current->rightChild);
	}
}

// вспомогательная рекурсия для добавления
Node* Set::addRecurson(std::string const& key, std::string const& value, Node* current)
{
	if (key < current->key)
	{
		if (current->leftChild != nullptr)
		{
			return addRecurson(key, value, current->leftChild);
		}
		else
		{
			current->leftChild = new Node(key, value);
			current->leftChild->parent = current;
			return current->leftChild;
		}
	}
	else
	{
		if (current->rightChild != nullptr)
		{
			return addRecurson(key, value, current->rightChild);
		}
		else
		{
			current->rightChild = new Node(key, value);
			current->rightChild->parent = current;
			return current->rightChild;
		}
	}
}

// балансировка
void Set::balance(Node* added)
{
	if (added->parent == nullptr || added->parent->parent == nullptr)
	{
		return;
	}
	auto* current = added->parent->parent;
	auto* prev = added->parent;
	auto* prevPrev = added;
	while (current != nullptr)
	{
		int lengthL = 0;
		int lengthR = 0;
		if (current->leftChild != nullptr)
		{
			lengthL = lengthOfSubtree(current->leftChild);
		}
		if (current->rightChild != nullptr)
		{
			lengthR = lengthOfSubtree(current->rightChild);
		}
		int balanceFactor = lengthR - lengthL;
		if (abs(balanceFactor) == 2)
		{
			setBalance(current, prev, prevPrev);
			return;
		}
		prevPrev = prev;
		prev = current;
		current = current->parent;
	}
}

// возвращает длину поддерева
int Set::lengthOfSubtree(Node* current) const
{
	if (current == nullptr)
	{
		return 0;
	}
	return 1 + std::max(lengthOfSubtree(current->leftChild), lengthOfSubtree(current->rightChild));
}

// установка баланса
void Set::setBalance(Node* a, Node* b, Node* c)
{
	if (a->leftChild == b && b->leftChild == c)
	{
		rotateSmallLeft(a, b, c);
		a->balanceFactor = lengthOfSubtree(a);
		b->balanceFactor = lengthOfSubtree(b);
	}
	else if (a->rightChild == b && b->rightChild == c)
	{
		rotateSmallRight(a, b, c);
		a->balanceFactor = lengthOfSubtree(a);
		b->balanceFactor = lengthOfSubtree(b);
	}
	else if (a->leftChild == b && b->rightChild == c)
	{
		rotateRight(a, b, c);
		a->balanceFactor = lengthOfSubtree(a);
		b->balanceFactor = lengthOfSubtree(b);
		c->balanceFactor = lengthOfSubtree(c);
	}
	else
	{
		rotateLeft(a, b, c);
		a->balanceFactor = lengthOfSubtree(a);
		b->balanceFactor = lengthOfSubtree(b);
		c->balanceFactor = lengthOfSubtree(c);
	}
}

// малый левый поворот
void Set::rotateSmallLeft(Node* a, Node* b, Node* c)
{
	b->parent = a->parent;
	if (a->parent != nullptr)
	{
		if (a->parent->leftChild == a)
		{
			a->parent->leftChild = b;
		}
		else
		{
			a->parent->rightChild = b;
		}
	}
	a->leftChild = b->rightChild;
	if (b->rightChild != nullptr)
	{
		b->rightChild->parent = a;
	}
	b->rightChild = a;
	a->parent = b;
	if (a == head)
	{
		head = b;
	}
}

// малый правый поворот
void Set::rotateSmallRight(Node* a, Node* b, Node* c)
{
	b->parent = a->parent;
	if (a->parent != nullptr)
	{
		if (a->parent->leftChild == a)
		{
			a->parent->leftChild = b;
		}
		else
		{
			a->parent->rightChild = b;
		}
	}
	a->rightChild = b->leftChild;
	if (b->leftChild != nullptr)
	{
		b->leftChild->parent = a;
	}
	b->leftChild = a;
	a->parent = b;
	if (a == head)
	{
		head = b;
	}
}

// левый поворот
void Set::rotateLeft(Node* a, Node* b, Node* c)
{
	c->parent = a->parent;
	if (a->parent != nullptr)
	{
		if (a->parent->leftChild == a)
		{
			a->parent->leftChild = c;
		}
		else
		{
			a->parent->rightChild = c;
		}
	}
	b->leftChild = c->rightChild;
	if (c->rightChild != nullptr)
	{
		c->rightChild->parent = b;
	}
	c->rightChild = b;
	b->parent = c;
	a->rightChild = c->leftChild;
	if (c->leftChild != nullptr)
	{
		c->leftChild->parent = a;
	}
	c->leftChild = a;
	a->parent = c;
	if (a == head)
	{
		head = c;
	}
}

// правый поворот
void Set::rotateRight(Node* a, Node* b, Node* c)
{
	c->parent = a->parent;
	if (a->parent != nullptr)
	{
		if (a->parent->leftChild == a)
		{
			a->parent->leftChild = c;
		}
		else
		{
			a->parent->rightChild = c;
		}
	}
	b->rightChild = c->leftChild;
	if (c->leftChild != nullptr)
	{
		c->leftChild->parent = b;
	}
	c->leftChild = b;
	b->parent = c;
	a->leftChild = c->rightChild;
	if (c->rightChild != nullptr)
	{
		c->rightChild->parent = a;
	}
	c->rightChild = a;
	a->parent = c;
	if (a == head)
	{
		head = c;
	}
}

// получение значения по ключу
std::string Set::getValueByKey(std::string const& key)
{
	if (isEmpty())
	{
		return "";
	}
	return getValueByKeyRecursion(key, head);
}

// вспомогательная рекурсия для получения значения по ключу
std::string Set::getValueByKeyRecursion(std::string const& key, Node const* const current)
{
	if (current->key == key)
	{
		return current->value;
	}
	else if (current->key > key)
	{
		if (current->leftChild != nullptr)
		{
			return getValueByKeyRecursion(key, current->leftChild);
		}
	}
	else
	{
		if (current->rightChild != nullptr)
		{
			return getValueByKeyRecursion(key, current->rightChild);
		}
	}
	return "";
}

// проверка существует ли такой ключ в дереве
bool Set::keyExists(std::string const& key) const
{
	if (isEmpty())
	{
		return false;
	}
	bool keyWasFound = false;
	keyExistsRecursion(keyWasFound, key, head);
	return keyWasFound;
}

// вспомогательная рекурсия для проверки на наличие ключа
void Set::keyExistsRecursion(bool& keyWasFound, std::string const& key, Node const* const current) const
{
	if (current->key == key)
	{
		keyWasFound = true;
		return;
	}
	if (current->leftChild != nullptr)
	{
		keyExistsRecursion(keyWasFound, key, current->leftChild);
	}
	if (current->rightChild != nullptr)
	{
		keyExistsRecursion(keyWasFound, key, current->rightChild);
	}
}

// проверка на пустоту
bool Set::isEmpty() const
{
	return head == nullptr;
}

// замена местами элементов
void Set::swap(Node* const a, Node* const b)
{
	Node  const temp = *b;
	b->value = a->value;
	b->key = a->key;
	a->value = temp.value;
	a->key = temp.key;
}

// удаление элемента по ключу
void Set::deleteNodeByKey(std::string const& key)
{
	if (keyExists(key))
	{
		auto* elementToDelete = getNodeByKey(key);
		if (elementToDelete->leftChild == nullptr && elementToDelete->rightChild == nullptr)
		{
			if (elementToDelete == head)
			{
				delete head;
				head = nullptr;
			}
			else
			{
				auto* parent = deleteElementThatDoesNotHaveChildren(elementToDelete);
				balance(parent);
			}
		}
		else
		{
			auto* parent = deleteElementThatHasAChild(elementToDelete);
			balance(parent);
		}
	}
}

// удаление элемента без детей
Node* Set::deleteElementThatDoesNotHaveChildren(Node* elementToDelete)
{
	auto* parent = elementToDelete->parent;
	if (parent != nullptr)
	{
		if (parent->leftChild == elementToDelete)
		{
			parent->leftChild = nullptr;
		}
		else
		{
			parent->rightChild = nullptr;
		}
	}
	delete elementToDelete;
	return parent;
}

// удаление элемента с ребёнком
Node* Set::deleteElementThatHasAChild(Node* elementToDelete)
{
	Node* parent = nullptr;
	auto* temp = elementToDelete;
	if (elementToDelete->leftChild != nullptr)
	{
		while (temp->leftChild != nullptr)
		{
			swap(temp, temp->leftChild);
			temp = temp->leftChild;
		}
		parent = temp->parent;
		parent->leftChild = nullptr;
		delete temp;
	}
	else
	{
		while (temp->rightChild != nullptr)
		{
			swap(temp, temp->rightChild);
			temp = temp->rightChild;
		}
		parent = temp->parent;
		parent->rightChild = nullptr;
		delete temp;
	}
	return parent;
}

// возвращает элемент по ключу
Node* Set::getNodeByKey(std::string const& key) const
{
	Node* result = nullptr;
	getNodeByKeyRecursion(key, head, result);
	return result;
}

// вспомагательная рекурсия для возвращаения элемента по ключу
void Set::getNodeByKeyRecursion(std::string const& key, Node* const current, Node*& result) const
{
	if (current->key == key)
	{
		result = current;
	}
	else if (current->key > key)
	{
		if (current->leftChild != nullptr)
		{
			getNodeByKeyRecursion(key, current->leftChild, result);
		}
	}
	else
	{
		if (current->rightChild != nullptr)
		{
			getNodeByKeyRecursion(key, current->rightChild, result);
		}
	}
}

// вовращает минимальный элемент поддерева
Node* Set::getMinInSubtree(Node* const current)
{
	if (current->leftChild != nullptr)
	{
		return getMinInSubtree(current->leftChild);
	}
	else
	{
		return current;
	}
}

// печать
void Set::print() const
{
	if (!isEmpty())
	{
		printRecursion(head);
	}
}

// вспомогательная рекурсия для печати
void Set::printRecursion(Node const* const current) const
{
	if (current->leftChild != nullptr)
	{
		printRecursion(current->leftChild);
	}
	if (current->rightChild != nullptr)
	{
		printRecursion(current->rightChild);
	}
	std::cout << current->key << std::endl;
}
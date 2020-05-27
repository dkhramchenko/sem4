#pragma once

#pragma once
#include <string>
#include <iostream>

struct Node;

// класс дерева
struct Set
{
	// конструктор
	Set();

	// деструктор
	~Set();

	// добавление значения по ключу
	void addValueByKey(std::string const& key, std::string const& value);

	// получение значения по ключу
	std::string getValueByKey(std::string const& key);

	// проверка существует ли такой ключ в дереве
	bool keyExists(std::string const& key) const;

	// удаление элемента по ключу
	void deleteNodeByKey(std::string const& key);

	// определяет высоту элемента по ключу
	int getElementHeightByKey(std::string const& key);

	// печать
	void print() const;

	// проверка на пустоту
	bool isEmpty() const;

private:

	// удаление элемента без детей
	Node* deleteElementThatDoesNotHaveChildren(Node* elementToDelete);

	// удаление элемента с ребёнком
	Node* deleteElementThatHasAChild(Node* elementToDelete);

	// замена местами элементов
	void swap(Node* const a, Node* const b);

	// вовращает минимальный элемент поддерева
	Node* getMinInSubtree(Node* const current);

	// возвращает элемент по ключу
	Node* getNodeByKey(std::string const& key) const;

	// вспомагательная рекурсия для возвращаения элемента по ключу
	void getNodeByKeyRecursion(std::string const& key, Node* const current, Node*& result) const;

	// вспомогательная рекурсия для печати
	void printRecursion(Node const* const current) const;

	// удаление
	void deleteRecursion(Node* current);

	// добавление, если такой ключ есть
	void addIfKeyExists(std::string const& key, std::string const& value, Node* current);

	// вспомогательная рекурсия для добавления
	Node* addRecurson(std::string const& key, std::string const& value, Node* current);

	// балансировка
	void balance(Node* added);

	// возвращает длину поддерева
	int lengthOfSubtree(Node* current) const;

	// установка баланса
	void setBalance(Node* a, Node* b, Node* c);

	// малый левый поворот
	void rotateSmallLeft(Node* a, Node* b, Node* c);

	// малый правый поворот
	void rotateSmallRight(Node* a, Node* b, Node* c);

	// левый поворот
	void rotateLeft(Node* a, Node* b, Node* c);

	// правый поворот
	void rotateRight(Node* a, Node* b, Node* c);

	// вспомогательная рекурсия для получения значения по ключу
	std::string getValueByKeyRecursion(std::string const& key,
		Node const* const current);

	// вспомогательная рекурсия для проверки на наличие ключа
	void keyExistsRecursion(bool& keyWasFound, std::string const& key,
		Node const* const current) const;

	// поле хранит корень
	Node* head;
};
#pragma once

#pragma once
#include <string>

// класс узла
struct Node
{
	// конструктор
	Node(std::string const& key, std::string const& value);

	// поле для ключа
	std::string key;

	// поле для значения
	std::string value;

	// фактор баланса
	int balanceFactor;

	// родитель
	Node* parent;

	// левый ребенок
	Node* leftChild;

	// правый ребенок
	Node* rightChild;
};
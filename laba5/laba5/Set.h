#pragma once

#pragma once
#include <string>
#include <iostream>

struct Node;

struct Set
{
	Set();

	~Set();

	void addValueByKey(std::string const& key, std::string const& value);

	std::string getValueByKey(std::string const& key);

	bool keyExists(std::string const& key) const;

	void deleteNodeByKey(std::string const& key);

	void print() const;

	bool isEmpty() const;

private:

	Node* deleteElementThatDoesNotHaveChildren(Node* elementToDelete);

	Node* deleteElementThatHasAChild(Node* elementToDelete);

	void swap(Node* const a, Node* const b);

	Node* getMinInSubtree(Node* const current);

	Node* getNodeByKey(std::string const& key) const;

	void getNodeByKeyRecursion(std::string const& key, Node* const current, Node*& result) const;

	void printRecursion(Node const* const current) const;

	void deleteRecursion(Node* current);

	void addIfKeyExists(std::string const& key, std::string const& value, Node* current);

	Node* addRecurson(std::string const& key, std::string const& value, Node* current);

	void balance(Node* added);

	int lengthOfSubtree(Node* current) const;

	void setBalance(Node* a, Node* b, Node* c);

	void rotateSmallLeft(Node* a, Node* b, Node* c);

	void rotateSmallRight(Node* a, Node* b, Node* c);

	void rotateLeft(Node* a, Node* b, Node* c);

	void rotateRight(Node* a, Node* b, Node* c);

	std::string getValueByKeyRecursion(std::string const& key,
		Node const* const current);

	void keyExistsRecursion(bool& keyWasFound, std::string const& key,
		Node const* const current) const;

	Node* head;
};
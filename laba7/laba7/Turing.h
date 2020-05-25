#pragma once
#include <map>
#include <string>

struct Turing
{
	std::map<int, std::string> tape;
	int state;
	int head;
	int step;

	Turing();

	void print();

	void run();
};


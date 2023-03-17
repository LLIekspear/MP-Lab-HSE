#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Element.h"

class HashTable {
public:
	struct HashItem {
		std::vector<std::string> values;
	};

	std::vector<HashItem> table;

	HashTable();
	~HashTable() = default;
	void insertItem(Element item);
	std::vector<std::string> findItem(unsigned int hash);
	unsigned int countCollisions();
};

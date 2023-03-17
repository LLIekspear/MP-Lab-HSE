#include "HashTable.h"

/**
@details Конструктор класса HashTable, который представляет из себя хэш-таблицу.
*/
HashTable::HashTable() {
	this->table.resize(1000000);
}

/**
@details Метод, позволяющий добавить элемент в хэш-таблицу.
*/
void HashTable::insertItem(Element item) {
	HashItem& curItem = this->table[item.getHash()];
	std::string fio = item.getFam() + " " + item.getIm() + " " + item.getOt();
	//убираем дубликаты
	for (auto i : curItem.values) {
		if (i == fio)
			return;
	}
	curItem.values.push_back(fio);
}

/**
@details Метод, позволяющий отыскать элемент в хэш-таблице (реализация через списки).
*/
std::vector<std::string> HashTable::findItem(unsigned int hash) {
	HashItem& curItem = this->table[hash];
	return curItem.values;
}

/**
@details Подсчет кол-ва коллизий в хэш-таблице.
*/
unsigned int HashTable::countCollisions() {
	unsigned int res = 0;
	for (auto i : this->table) {
		if (i.values.size() > 1)
			res += i.values.size() - 1;
	}
	return res;
}
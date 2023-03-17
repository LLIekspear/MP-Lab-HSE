#include "HashTable.h"

/**
@details ����������� ������ HashTable, ������� ������������ �� ���� ���-�������.
*/
HashTable::HashTable() {
	this->table.resize(1000000);
}

/**
@details �����, ����������� �������� ������� � ���-�������.
*/
void HashTable::insertItem(Element item) {
	HashItem& curItem = this->table[item.getHash()];
	std::string fio = item.getFam() + " " + item.getIm() + " " + item.getOt();
	//������� ���������
	for (auto i : curItem.values) {
		if (i == fio)
			return;
	}
	curItem.values.push_back(fio);
}

/**
@details �����, ����������� �������� ������� � ���-������� (���������� ����� ������).
*/
std::vector<std::string> HashTable::findItem(unsigned int hash) {
	HashItem& curItem = this->table[hash];
	return curItem.values;
}

/**
@details ������� ���-�� �������� � ���-�������.
*/
unsigned int HashTable::countCollisions() {
	unsigned int res = 0;
	for (auto i : this->table) {
		if (i.values.size() > 1)
			res += i.values.size() - 1;
	}
	return res;
}
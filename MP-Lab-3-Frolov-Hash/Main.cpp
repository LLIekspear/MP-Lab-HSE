#include <iostream>
#include <fstream>
#include "Element.h"
#include <vector>
#include <chrono>
#include <cstdlib>
#include <map>
#include <sstream>
#include "HashTable.h"

/*! @mainpage Методы программирования. Лабораторная работа №2. Алгоритмы поиска.

@section Вариант_26
Массив данных генеологического фонда: ФИО, год рождения,
год смерти, число детей (сравнение по полям - год рождения, ФИО, число детей). \n

@section Выполнил
Фролов Олег, СКБ201
*/

/**
@details Простая хэш-функция.
*/
unsigned int simpleHash(std::string key) {
	unsigned int res = 1;
	int p = 67;
	for (int i = 0; i < key.length(); ++i) {
		res = (res * ((key[i] - 'a' + 1)*p)) % 100000;
	}
	return res;
}

/**
@details Сложная хэш-функция.
*/
unsigned int complexHash(std::string key) {
	unsigned int res = 0;
	int p = 67;
	for (int i = 0; i < key.length(); ++i) {
		res = (res + ((key[i] - 'a' + 1) * i));
	}
	return res%100000;
}

/**
@details Функция для прямого поиска заданного элемента в контейнере объектов класса Element.
*/
Element linearSearch(std::vector<Element> spisok, std::string elem) {
	Element res;
	for (int i = 0; i < spisok.size(); ++i) {
		std::string fio = "";
		fio.append(spisok[i].getFam());
		fio.append(" ");
		fio.append(spisok[i].getIm());
		fio.append(" ");
		fio.append(spisok[i].getOt());
		if (fio == elem) {
			res=spisok[i];
			res.setHash(spisok[i].getHash());
			break;
		}
	}
	return res;
}
/**
@details Функция для поиска заданного элемента в хэш-таблице.
*/
void findHashTable(std::string searchQuery,/* HashTable simpleHashTable, int mode*/std::vector<Element>spisok, HashTable simpleHashTable) {
	auto begin = std::chrono::steady_clock::now();
	Element elem = linearSearch(spisok, searchQuery);
	//std::cout << "\nHASH: " << elem.getHash() << "\n";
	std::vector<std::string> resSpisok = simpleHashTable.findItem(elem.getHash());
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	if (resSpisok.size() != 0) {
		std::cout << "\nFound " << resSpisok.size() << "\n";
		std::cout << "\nThere was found " << simpleHashTable.countCollisions() << " collisions!\n";
	} else {
		std::cout << "\nNot found!\n";
	}
	std::cout<<"\nTime "<<elapsed_ms.count()<<"\n";
}

/**
@details Функция для проверки равенства ФИО двух объектов класса Element.
*/
int checkFIO(Element elem1, Element elem2, int flag) {
	std::string alph = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	std::string fio = "";
	std::string fio2 = "";
	fio = elem1.getFam();
	fio2 = elem2.getFam();
	int first = alph.find(std::tolower(fio[0]));
	int second = alph.find(std::tolower(fio2[0]));
	if (first == second) {
		for (int i = 0; i < fio.length() && i < fio2.length() && first == second; ++i) {
			first = alph.find(std::tolower(fio[i]));
			second = alph.find(std::tolower(fio2[i]));
		}
	}
	if (first == second) {
		fio = elem1.getIm();
		fio2 = elem2.getIm();
		for (int i = 0; i < fio.length() && i < fio2.length() && first == second; ++i) {
			first = alph.find(std::tolower(fio[i]));
			second = alph.find(std::tolower(fio2[i]));
		}
	}
	if (first == second) {
		fio = elem1.getOt();
		fio2 = elem2.getOt();
		for (int i = 0; i < fio.length() && i < fio2.length() && first == second; ++i) {
			first = alph.find(std::tolower(fio[i]));
			second = alph.find(std::tolower(fio2[i]));
		}
	}
	if (first > second)
		return 1;
	else if (flag == 2 && first == second)
		return 2;
	else
		return 0;
}

int main() {

	std::system("chcp 1251");
	int file_number = 0;
	std::vector<Element> spisok;
	HashTable simpleTable;
	HashTable complexTable;
	std::multimap<std::string, int> map;
	int choosedAlg = 0;
	std::cout << "\nChoose search algorithm (0 - simple hash, 1 - complex hash): \n";
	std::cin >> choosedAlg;
	while (choosedAlg < 0 || choosedAlg >= 2 || std::cin.fail()) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Your input is not a number!" << '\n';
			choosedAlg = -1;
		}
		else {
			std::cout << "Your input must be in interval 0-1!" << '\n';
			choosedAlg = 0;
		}
		std::cout << "Input again!" << '\n';
		std::cin >> choosedAlg;
	}
	std::cout << "Choose file(0-7)" << '\n';
	std::cin >> file_number;
	while (file_number < 0 || file_number >= 8 || std::cin.fail()) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Your input is not a number!" << '\n';
			file_number = -1;
		}
		else {
			std::cout << "Your input must be in interval 0-7!" << '\n';
			file_number = 0;
		}
		std::cout << "Input again!" << '\n';
		std::cin >> file_number;
	}
	setlocale(LC_ALL, "rus");
	std::string line = "";
	std::string filename = "C:\\Users\\fov-2\\source\\repos\\data_";
	filename.append(std::to_string(file_number));
	filename.append(".txt");
	std::ifstream in(filename);
	if (in.is_open()) {
		while (getline(in, line)) {
			std::string word = "";
			int flag = 0;
			int amount = 0;
			Element human;
			for (int i = 0; i < line.size(); ++i) {
				if (line[i] == '(')
					flag = 2;
				else if (line[i] == ')')
					flag = 0;
				else if (line[i] == ' ' || line[i] == '\n') {
					if (amount == 0) {
						human.setFam(word);
					}
					else if (amount == 1)
						human.setIm(word);
					else if (amount == 2)
						human.setOt(word);
					else if (amount == 3)
						human.setYear(std::stoi(word));
					else if (amount == 4)
						human.setYearD(std::stoi(word));
					word = "";
					++amount;
				}
				else if (flag == 0) {
					char symbol = line[i];
					if (symbol != ' ') {
						word.push_back(symbol);
					}
				}

				if (amount == 5) {
					amount = 0;
					human.setChildAmount(line[line.size() - 1] - '0');
					spisok.push_back(human);
				}
			}
		}
	}
	in.close();
	std::cout << spisok.size() << std::endl;
	std::cout << "\nParsing done!\n" << std::endl;

	while (choosedAlg != -2) {
		std::string searchQuery;
		Element& item();
		std::cin.get();
		std::cout << "\n\nInput your search query, please!\n";
		getline(std::cin, searchQuery);
		std::cout << "\n" << searchQuery << "\n";
		if (choosedAlg == 1) {
			for (int i = 0; i < spisok.size(); ++i) {
				std::string fio = spisok[i].getFam() + " " + spisok[i].getIm() + " " + spisok[i].getOt();
				unsigned int hash = complexHash(fio);
				spisok[i].setHash(hash);
				complexTable.insertItem(spisok[i]);
			}
			findHashTable(searchQuery, spisok, complexTable);
		}
		else if (choosedAlg == 0) {
			for (int i = 0; i < spisok.size(); ++i) {
				std::string fio = spisok[i].getFam() + " " + spisok[i].getIm() + " " + spisok[i].getOt();
				unsigned int hash = simpleHash(fio);
				spisok[i].setHash(hash);
				simpleTable.insertItem(spisok[i]);
			}
			findHashTable(searchQuery, spisok, simpleTable);
		}
		std::cout << "\n\nEnd!\n\n";
		std::cout << "Would you like to search again (0 - simple hash, 1 - complex hash,  -2 - end)?\n";
		std::cin >> choosedAlg;
		std::cout << "\nAgain.\n";
	}
	return 0;
}
#include <iostream>
#include <fstream>
#include "Element.h"
#include <vector>
#include <chrono>
#include <cstdlib>
#include <map>
#include <sstream>

/*! @mainpage Методы программирования. Лабораторная работа №2. Алгоритмы поиска.

@section Вариант_26
Массив данных генеологического фонда: ФИО, год рождения,
год смерти, число детей (сравнение по полям - год рождения, ФИО, число детей). \n
Сортировка: пирамидальная. \n
Алгоритмы поиска: линейный, бинарный и встроенный в multimap

@section Выполнил
Фролов Олег, СКБ201
*/

/**
@details Функция для поиска заданного элемента в multimap, который содержит объекты класса Element.
*/
void findMultimap(std::multimap<std::string, int>map, std::string searchQuery) {
	auto search = map.find(searchQuery);
	if (search != map.end()) {
		std::cout << "\nFound " << search->first << " at " << search->second << "\n";
	}
	else {
		std::cout << "\nNot Found\n";
	}
}

/**
@details Функция для прямого поиска заданного элемента в контейнере объектов класса Element.
*/
void linearSearch(std::vector<Element> spisok, std::string elem) {
	for (int i = 0; i < spisok.size(); ++i) {
		std::string fio = "";
		fio.append(spisok[i].getFam());
		fio.append(" ");
		fio.append(spisok[i].getIm());
		fio.append(" ");
		fio.append(spisok[i].getOt());
		if (fio == elem) {
			std::cout << elem << " was found at index " << i << "\n";
			break;
		}
		else if (i + 1 == spisok.size()) {
			std::cout << elem << " is not in this array!\n";
		}
	}
}

/**
@details Функция для сравнения двух строк по кириллице. Если в ходе цикла, пробегающегося по всем буквам двух строк, \n
в одном из двух слов встречаются разные буквы, то та строка, чья буква встречается в алфавите раньше, считается большей.
*/
int checkTwoStrings(std::string firstS, std::string secondS) {
	std::string alph = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	//if true return 1, if false return 0
	int first = alph.find(std::tolower(firstS[0]));
	int second = alph.find(std::tolower(secondS[0]));
	if (first == second) {
		int count = 0;
		
		while (first == second) {
			first = alph.find(std::tolower(firstS[count]));
			second = alph.find(std::tolower(secondS[count]));
			firstS.insert(count, " ");
			++count;
		}
		if (first < second) {
			return 0;
		} else
			return 1;
	} else if (first < second)
		return 0;
	else
		return 1;
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

/**
@details Функция для бинарного поиска заданного элемента в контейнере объектов класса Element.
*/
void binarySearch1(std::vector<Element> spisok, std::string query) {
	int low = 0;
	int high = spisok.size() - 1;
	int mid;

	std::stringstream ss(query);
	std::vector<std::string> words;
	std::string word;
	Element elem;
	while (ss >> word) {
		words.push_back(word);
	}
	elem.setFam(words[0]);
	elem.setIm(words[1]);
	elem.setOt(words[2]);
	while (low <= high) {
		mid = (high + low) / 2;
		if (checkFIO(spisok[mid], elem, 2)==2) {
			std::cout << query << " was found at index " << mid << "\n";
			break;
		}
		else if (checkFIO(spisok[mid], elem, 0)) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	if (low > high)
		std::cout << query << " is not in this array!\n";
}

/**
@details Функция для построения кучи, требуемой для корректной работы пирамидальной сортировки.
*/
void heapify1(std::vector<Element>& spisok, int N, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left<N && /*spisok[left]>spisok[largest]*/checkFIO(spisok[left], spisok[largest], 0)==1)
		largest = left;
	if (right<N && /*spisok[right]>spisok[largest]*/checkFIO(spisok[right], spisok[largest], 0)==1)
		largest = right;
	if (largest != i) {
		Element temp;
		temp = spisok[i];
		spisok[i] = spisok[largest];
		spisok[largest] = temp;
		heapify1(spisok, N, largest);
	}
}

/**
@details Функция для пирамидальной сортировки контейнера из объектов класса Element.
*/
void heapSort1(std::vector<Element>& spisok, int N) {
	for (int i = N / 2 - 1; i >= 0; --i) {
		heapify1(spisok, N, i);
	}
	for (int i = N - 1; i >= 0; --i) {
		Element temp;
		temp = spisok[0];
		spisok[0] = spisok[i];
		spisok[i] = temp;
		heapify1(spisok, i, 0);
	}
}

int main() {

	std::system("chcp 1251");
	int file_number = 0;
	std::vector<Element> spisok;
	std::multimap<std::string, int> map;
	int choosedAlg = 0;
	std::cout << "\nChoose search algorithm (0 - linear (already sorted), 1 - binar (already sorted), 2 - sort and binar, 3 - multimap (search by key)): \n";
	std::cin >> choosedAlg;
	while (choosedAlg < 0 || choosedAlg >= 4 || std::cin.fail()) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Your input is not a number!" << '\n';
			choosedAlg = -1;
		}
		else {
			std::cout << "Your input must be in interval 0-3!" << '\n';
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
	//----
	for (int i = 0; i < spisok.size(); ++i) {
		std::string fio = "";
		fio.append(spisok[i].getFam());
		fio.append(" ");
		fio.append(spisok[i].getIm());
		fio.append(" ");
		fio.append(spisok[i].getOt());
		map.insert(std::make_pair(fio, i));
	}
	//----
	std::cout << spisok.size() << std::endl;
	std::cout << "\nParsing done!\n" << std::endl;

	while (choosedAlg != -2) {
		std::string searchQuery;
		std::cin.get();
		std::cout << "\n\nInput your search query, please!\n";
		getline(std::cin, searchQuery);
		std::cout << "\n" << searchQuery << "\n";
		if (choosedAlg == 0) {
			//check time of linear search!
			std::cout << "\n\nLinear searching started!\n";
			auto begin = std::chrono::steady_clock::now();
			linearSearch(spisok, searchQuery);
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms";
			std::cout << "\nLinear searching ended!\n\n";
		}
		else if (choosedAlg == 1) {
			//sort and check time of binary search!
			std::vector<Element> res = spisok;
			heapSort1(res, res.size());
			std::cout << "\n\nBinary searching started!\n";
			auto begin = std::chrono::steady_clock::now();
			binarySearch1(res, searchQuery);
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms";
			std::cout << "\nBinary searching ended!\n\n";
		}
		else if (choosedAlg == 2) {
			//check time of sort and binary search both!
			std::cout << "\nHeap started!\n";
			auto begin = std::chrono::steady_clock::now();
			std::vector<Element> res = spisok;
			heapSort1(res, res.size());
			std::cout << "\Heap ended!\n";
			std::cout << "\nBinary searching started!\n";
			binarySearch1(res, searchQuery);
			std::cout << "\nBinary searching ended!\n";
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms\n\n";
		}
		else if (choosedAlg == 3) {
			//find in multimap by key
			auto begin = std::chrono::steady_clock::now();
			findMultimap(map, searchQuery);
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms";
		}
		std::cout << "\n\nEnd!\n\n";
		std::cout << "Would you like to search again (0 - linear (already sorted), 1 - binary (already sorted), 2 - sort and binary, 3 - multimap and search by key,  -2 - end)?\n";
		std::cin >> choosedAlg;
		std::cout << "\nAgain.\n";
	}
	return 0;
}
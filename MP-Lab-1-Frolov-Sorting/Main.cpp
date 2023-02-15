#include <iostream>
#include <fstream>
#include "Element.h"
#include <vector>
#include <chrono>

/*! @mainpage Методы программирования. Лабораторная работа №1. Алгоритмы сортировки.

@section Вариант_26
Массив данных генеологического фонда: ФИО, год рождения, 
год смерти, число детей (сравнение по полям - год рождения, ФИО, число детей). \n
Сортировки: пузырьком, шейкер-сортировка, пирамидальная сортировка.

@section Выполнил
Фролов Олег, СКБ201
*/


/**
@details Функция для сохранения контейнера, который содержит объекты класса Element, в текстовый файл.
*/
void saveToFile(std::vector<Element> spisok, std::string filename) {
	std::ofstream out;
	out.open(filename);
	if (out.is_open()) {
		for (int i = 0; i < spisok.size(); ++i) {
			out << spisok[i].getFam() << " " << spisok[i].getIm() << " " << spisok[i].getOt() << " " << spisok[i].getYear() << " " << spisok[i].getYearD() << " " << spisok[i].getChildAmount() << '\n';
		}
	}
	out.close();
}

//шейкерная ----------------
/**
@details Функция для шейкерной сортировки контейнера, который состоит из объектов класса Element.
*/
void shakerSort(std::vector<Element> &spisok) {
	int j, k = spisok.size() - 1;
	int lb = 1, ub = spisok.size() - 1;
	Element temp;
	while (lb < ub) {
		for (j = ub; j > 0; --j) {
			if (spisok[j - 1] > spisok[j]) {
				temp = spisok[j - 1];
				spisok[j - 1] = spisok[j];
				spisok[j] = temp;
				k = j;
			}
		}
		lb = k + 1;
		for (j = 1; j <= ub; ++j) {
			if (spisok[j - 1] > spisok[j]) {
				temp = spisok[j - 1];
				spisok[j - 1] = spisok[j];
				spisok[j] = temp;
				k = j;
			}
		}
		ub = k - 1;
	}
}
//--------

//пирамидальная, сначала строим кучу (дерево), потом сортируем
/**
@details Функция для построения кучи, требуемой для корректной работы пирамидальной сортировки.
*/
void heapify1(std::vector<Element> &spisok, int N, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left<N && spisok[left]>spisok[largest])
		largest = left;
	if (right<N && spisok[right]>spisok[largest])
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
void heapSort1(std::vector<Element> &spisok, int N) {
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

/**
@details Функция для пузырьковой сортировки контейнера из объектов класса Element.
*/
void bubbleSort(std::vector<Element>& spisok) {

	//сортировка по году рождения, потом по ФИО, потом по кол-ву детей
	for (int i = 0; i < spisok.size(); ++i) {
		for (int j = spisok.size() - 1; j > i; --j) {
			if (spisok[j - 1] > spisok[j]) {
				Element temp = spisok[j - 1];
				spisok[j - 1] = spisok[j];
				spisok[j] = temp;
			}
		}
	}
}
//--------------

/**
@details Функция main для основной работы программы.
*/
int main() {

	int file_number = 0;
	std::vector<Element> spisok;
	int choosedAlg = 0;
	std::cout << "\nChoose sorting algorithm (0 - puzir, 1 - shaker, 2 - heap): \n";
	std::cin >> choosedAlg;
	while (choosedAlg < 0 || choosedAlg >= 3 || std::cin.fail()) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Your input is not a number!" << '\n';
			choosedAlg = -1;
		}
		else {
			std::cout << "Your input must be in interval 0-7!" << '\n';
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
				else if (line[i] == ' '||line[i]=='\n') {
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
					human.setChildAmount(line[line.size()-1]-'0');
					spisok.push_back(human);
				}
			}
		}
	}
	in.close();
	std::cout << spisok.size() << std::endl;
	std::cout << "\nParsing done!\n" << std::endl;
	while (choosedAlg != -2) {
		if (choosedAlg == 0) {
			std::cout << "\n\nPuzir started!\n";
			auto begin = std::chrono::steady_clock::now();
			std::vector<Element> res = spisok;
			bubbleSort(res);
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms";
			saveToFile(res, "C:\\Users\\fov-2\\source\\repos\\out1.txt");
			std::cout << "\nPuzir ended!\n\n";
		}
		else if (choosedAlg == 1) {
			std::cout << "\n\nShaker started!\n";
			auto begin = std::chrono::steady_clock::now();
			std::vector<Element> res = spisok;
			shakerSort(res);
			
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms";
			saveToFile(res, "C:\\Users\\fov-2\\source\\repos\\out11.txt");
			std::cout << "\nShaker ended!\n\n";
		}
		else if (choosedAlg == 2) {
			std::cout << "\n\nHeap started!\n";
			auto begin = std::chrono::steady_clock::now();
			std::vector<Element> res = spisok;
			heapSort1(res, res.size());
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << "The time: " << elapsed_ms.count() << " ms";
			saveToFile(res, "C:\\Users\\fov-2\\source\\repos\\out111.txt");
			std::cout << "\nHeap ended!\n\n";
		}
		std::cout << "\n\nEnd!\n\n";
		std::cout << "Would you like to sort again (0 - puzir, 1 - shaker, 2 - heap, -2 - end)?\n";
		std::cin >> choosedAlg;
	}
	return 0;
}
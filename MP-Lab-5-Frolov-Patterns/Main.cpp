#include <iostream>
#include <fstream>
#include "Element.h"
#include <vector>
#include <chrono>
#include <cstdlib>
#include <map>
#include <sstream>

/*! @mainpage Методы программирования. Лабораторная работа №5. Паттерн Factory Method.

@section Вариант_26(6)
Массив данных генеологического фонда: ФИО, год рождения,
год смерти, число детей (сравнение по полям - год рождения, ФИО, число детей). \n

@section Выполнил
Фролов Олег, СКБ201
*/

/**
@details Функция для проверки равенства ФИО двух объектов класса Element.
*/
std::string outputFilename = "C:\\Users\\fov-2\\source\\repos\\report";

class Report {
private:
	std::vector<Element> data;
public:
	void setData(std::vector<Element> newdata) {
		this->data = newdata;
	}
	std::vector<Element> getData() {
		return this->data;
	}
	Report& operator= (Report& elem) {
		this->setData(elem.getData());
		return *this;
	}
};

Report report;

struct Writer {
	virtual void writeReport() const = 0;
};

class WriterCreator {
public:
	virtual Writer* createWriter() const = 0;
};

class TxtWriter : public Writer {
public:
	void writeReport() const override {
		std::ofstream fileOut(outputFilename + ".txt");
		std::vector<Element> data = report.getData();
		for (int i = 0; i < data.size(); ++i) {
			fileOut << "Гражданин(-ка) " << data[i].getFam() << " " << data[i].getIm() << " " << data[i].getOt() << " " << data[i].getYear() << " года рождения и " << data[i].getYearD() << " года смерти вырастил(-а) и воспитал(-а) " << data[i].getChildAmount() << " детей.\n";
		}
	}
};

class TxtWriterCreator : public WriterCreator {
public:
	Writer* createWriter() const override {
		return new TxtWriter();
	}
};

class CsvWriter : public Writer {
public:
	void writeReport() const override {
		std::ofstream fileOut(outputFilename + ".csv");
		fileOut << "ФИО гражданина(-ки);Год рождения;Год смерти;Кол-во детей\n";
		std::vector<Element> data = report.getData();
		for (int i = 0; i < data.size(); ++i) {
			std::string name = data[i].getFam() + " " + data[i].getIm() + " " + data[i].getOt();
			std::string res = name + ";" + std::to_string(data[i].getYear()) + ";" + std::to_string(data[i].getYearD()) + ";" + std::to_string(data[i].getChildAmount()) + "\n";
			fileOut << res;
		}
	}
};

class CsvWriterCreator : public WriterCreator {
public:
	Writer* createWriter() const override {
		return new CsvWriter();
	}
};

class XmlWriter : public Writer {
public:
	void writeReport() const override {
		std::ofstream fileOut(outputFilename + ".xml");
		fileOut << "<?xml version=\"1.0\" encoding=\"ansi\"?>\n";
		fileOut << "<report>\n";
		std::vector<Element> data = report.getData();
		for (int i = 0; i < data.size(); ++i) {
			fileOut << "\t<citizen>\n";
			std::string name = data[i].getFam() + " " + data[i].getIm() + " " + data[i].getOt();
			fileOut << "\t\t<name>" << name << "</name>\n";
			fileOut << "\t\t<birthYear>" << data[i].getYear() << "</birthYear>\n";
			fileOut << "\t\t<deathYear>" << data[i].getYearD() << "</deathYear>\n";
			fileOut << "\t\t<childAmount>" << data[i].getChildAmount() << "</childAmount>\n";
			fileOut << "\t</citizen>\n";
		}
		fileOut << "</report>\n";
	}
};

class XmlWriterCreator : public WriterCreator {
public:
	Writer* createWriter() const override {
		return new XmlWriter;
	}
};

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
	WriterCreator* creator;
	Writer* writer;
	int choosedAlg = 0;
	std::cout << "\nChoose output type (0 - txt, 1 - csv, 2 - xml): \n";
	std::cin >> choosedAlg;
	while (choosedAlg < 0 || choosedAlg >= 3 || std::cin.fail()) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Your input is not a number!" << '\n';
			choosedAlg = -1;
		}
		else {
			std::cout << "Your input must be in interval 0-2!" << '\n';
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
	outputFilename.append(std::to_string(file_number));
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
	report.setData(spisok);

	while (choosedAlg != -2) {
		std::cin.get();
		if (choosedAlg == 1) {
			creator = new CsvWriterCreator();
			writer = creator->createWriter();
			writer->writeReport();
		}
		else if (choosedAlg == 0) {
			creator = new TxtWriterCreator();
			writer = creator->createWriter();
			writer->writeReport();
		}
		else if (choosedAlg == 2) {
			creator = new XmlWriterCreator();
			writer = creator->createWriter();
			writer->writeReport();
		}
		std::cout << "\n\nEnd!\n\n";
		std::cout << "Would you like to repeat again (0 - txt, 1 - csv, 2 - xml,  -2 - end)?\n";
		std::cin >> choosedAlg;
		std::cout << "\nAgain.\n";
	}
	return 0;
}
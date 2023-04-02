#include "Element.h"
#include <string>

/**
@details Кириллица для сравнения ФИО.
*/
std::string alph = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

/**
@details Стандартный конструктор.
*/
Element::Element() {
	this->familiya = "Fam";
	this->imya = "Im";
	this->otchestvo = "Ot";
}

/**
@details Конструктор, которому передаются значения для всех полей класса.
*/
Element::Element(std::string fam, std::string im, std::string ot, int y, int yd, int ca, unsigned int hashValue) {
	this->familiya = fam;
	this->imya = im;
	this->otchestvo = ot;
	this->year = y;
	this->year_death = yd;
	this->child_amount = ca;
	this->hashValue = hashValue;
}

/**
@details Функция получения фамилии.
*/
std::string Element::getFam() {
	return this->familiya;
}

/**
@details Функция установки фамилии.
*/
void Element::setFam(std::string newFam) {
	this->familiya = newFam;
}

/**
@details Функция получения имени.
*/
std::string Element::getIm() {
	return this->imya;
}

/**
@details Функция установки имени.
*/
void Element::setIm(std::string newIm) {
	this->imya= newIm;
}

/**
@details Функция получения отчества.
*/
std::string Element::getOt() {
	return this->otchestvo;
}

/**
@details Функция установки отчества.
*/
void Element::setOt(std::string newOt) {
	this->otchestvo = newOt;
}

/**
@details Функция получения года рождения.
*/
int Element::getYear() {
	return this->year;
}

/**
@details Функция установки года рождения.
*/
void Element::setYear(int newYear) {
	this->year = newYear;
}

/**
@details Функция получения года смерти.
*/
int Element::getYearD() {
	return this->year_death;
}

/**
@details Функция установки года смерти.
*/
void Element::setYearD(int newYearD) {
	this->year_death = newYearD;
}

/**
@details Функция получения количества детей.
*/
int Element::getChildAmount() {
	return this->child_amount;
}

/**
@details Функция установки количества детей.
*/
void Element::setChildAmount(int newAmount) {
	this->child_amount = newAmount;
}

/**
@details Перегрузка оператора > для сравнения двух объектов класса Element.
*/
bool Element::operator> (const Element& elem) const {
	if (year > elem.year) {
		return 1;
	}
	else if (year == elem.year) {
		//цикл для проверки первенства алфавита, если равные ФИО, то далее проверка по кол-ву детей
		if (familiya[0] == elem.familiya[0]) {
			if (imya[0] == elem.imya[0]) {
				if (otchestvo[0] == elem.otchestvo[0]) {
					if (child_amount > elem.child_amount)
						return 1;
					else
						return 0;
				}
				else {
					int first = alph.find(std::tolower(otchestvo[0]));
					int second = alph.find(std::tolower(elem.otchestvo[0]));
					if (first < second)
						return 1;
					else
						return 0;
				}
			}
			else {
				int first = alph.find(std::tolower(imya[0]));
				int second = alph.find(std::tolower(elem.imya[0]));
				if (first < second)
					return 1;
				else
					return 0;
			}
		}
		else {
			int first = alph.find(std::tolower(familiya[0]));
			int second = alph.find(std::tolower(elem.familiya[0]));
			if (first < second)
				return 1;
			else
				return 0;
		}
	} else {
		return 0;
	}
}

/**
@details Перегрузка оператора < для сравнения двух объектов класса Element.
*/
bool Element::operator< (const Element& elem) const {
	if (year < elem.year) {
		return 1;
	}
	else if (year > elem.year) {
		//цикл для проверки первенства алфавита, если равные ФИО, то далее проверка по кол-ву детей
		if (familiya[0] == elem.familiya[0]) {
			if (imya[0] == elem.imya[0]) {
				if (otchestvo[0] == elem.otchestvo[0]) {
					if (child_amount < elem.child_amount)
						return 1;
					else
						return 0;
				}
				else {
					int first = alph.find(std::tolower(otchestvo[0]));
					int second = alph.find(std::tolower(elem.otchestvo[0]));
					if (first > second)
						return 1;
					else
						return 0;
				}
			}
			else {
				int first = alph.find(std::tolower(imya[0]));
				int second = alph.find(std::tolower(elem.imya[0]));
				if (first > second)
					return 1;
				else
					return 0;
			}
		}
		else {
			int first = alph.find(std::tolower(familiya[0]));
			int second = alph.find(std::tolower(elem.familiya[0]));
			if (first > second)
				return 1;
			else
				return 0;
		}
	}
	else {
		return 0;
	}
}

/**
@details Перегрузка оператора >= для сравнения двух объектов класса Element.
*/
bool Element::operator>= (const Element& elem) const {
	if (year >= elem.year) {
		return 1;
	}
	else if (year < elem.year) {
		//цикл для проверки первенства алфавита, если равные ФИО, то далее проверка по кол-ву детей
		if (familiya[0] == elem.familiya[0]) {
			if (imya[0] == elem.imya[0]) {
				if (otchestvo[0] == elem.otchestvo[0]) {
					if (child_amount >= elem.child_amount)
						return 1;
					else
						return 0;
				}
				else {
					int first = alph.find(std::tolower(otchestvo[0]));
					int second = alph.find(std::tolower(elem.otchestvo[0]));
					if (first <= second)
						return 1;
					else
						return 0;
				}
			}
			else {
				int first = alph.find(std::tolower(imya[0]));
				int second = alph.find(std::tolower(elem.imya[0]));
				if (first <= second)
					return 1;
				else
					return 0;
			}
		}
		else {
			int first = alph.find(std::tolower(familiya[0]));
			int second = alph.find(std::tolower(elem.familiya[0]));
			if (first <= second)
				return 1;
			else
				return 0;
		}
	}
	else {
		return 0;
	}
}

/**
@details Перегрузка оператора <= для сравнения двух объектов класса Element.
*/
bool Element::operator<= (const Element& elem) const {
	if (year <= elem.year) {
		return 1;
	}
	else if (year > elem.year) {
		//цикл для проверки первенства алфавита, если равные ФИО, то далее проверка по кол-ву детей
		if (familiya[0] == elem.familiya[0]) {
			if (imya[0] == elem.imya[0]) {
				if (otchestvo[0] == elem.otchestvo[0]) {
					if (child_amount <= elem.child_amount)
						return 1;
					else
						return 0;
				}
				else {
					int first = alph.find(std::tolower(otchestvo[0]));
					int second = alph.find(std::tolower(elem.otchestvo[0]));
					if (first >= second)
						return 1;
					else
						return 0;
				}
			}
			else {
				int first = alph.find(std::tolower(imya[0]));
				int second = alph.find(std::tolower(elem.imya[0]));
				if (first >= second)
					return 1;
				else
					return 0;
			}
		}
		else {
			int first = alph.find(std::tolower(familiya[0]));
			int second = alph.find(std::tolower(elem.familiya[0]));
			if (first >= second)
				return 1;
			else
				return 0;
		}
	}
	else {
		return 0;
	}
}

/**
@details Перегрузка оператора = для сравнения двух объектов класса Element.
*/
Element& Element::operator= (Element& elem) {
	this->setFam(elem.getFam());
	this->setIm(elem.getIm());
	this->setOt(elem.getOt());
	this->setYear(elem.getYear());
	this->setYearD(elem.getYearD());
	this->setChildAmount(elem.getChildAmount());
	return *this;
}
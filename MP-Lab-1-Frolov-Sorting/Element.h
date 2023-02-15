#pragma once
#include <iostream>
#include <string>

class Element {
private:
	std::string familiya = "";
	std::string imya = "";
	std::string otchestvo = "";
	int year = 1900;
	int year_death = 1920;
	int child_amount = 0;
	int sex = 0;
public:
	Element();
	Element(std::string fam, std::string im, std::string ot, int y, int yd, int ca);
	std::string getFam();
	void setFam(std::string newFam);
	std::string getIm();
	void setIm(std::string newIm);
	std::string getOt();
	void setOt(std::string newOt);
	int getYear();
	void setYear(int newYear);
	int getYearD();
	void setYearD(int newYearD);
	int getChildAmount();
	void setChildAmount(int newAmount);
	bool operator> (const Element& elem) const;
	bool operator< (const Element& elem) const;
	bool operator>= (const Element& elem) const;
	bool operator<= (const Element& elem) const;
	Element& operator= (Element& elem);
};
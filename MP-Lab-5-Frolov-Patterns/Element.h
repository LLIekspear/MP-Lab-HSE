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
	unsigned int hashValue=0;
public:
	Element();
	~Element() = default;
	Element(std::string fam, std::string im, std::string ot, int y, int yd, int ca, unsigned int hashValue);
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
	friend std::ostream& operator<<(std::ostream& os, const Element& elem) {
		os << elem.familiya << " " << elem.imya << " " << elem.otchestvo << " " << elem.year << " " << elem.year_death << " " << elem.child_amount;
		return os;
	}
};
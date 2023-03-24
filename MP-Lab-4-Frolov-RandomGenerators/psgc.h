#pragma once
#include <vector>

class psgc {
private:
	unsigned long long seed = 0; //0<=seed<mod
	unsigned long long mod = 1 << 31 - 1; //2^31 -1, должно быть натуральным и >=2! 
	unsigned long long p = 0; //получаем смешанный когруэнтный метод, по сравнению с мультипликативным период генерируемых чисел больше, 0<=c<mod
	unsigned long long mul = 16807;//0<=mul<mod
public:
	psgc();
	~psgc() = default;
	void setSeed(unsigned long long seed);
	unsigned long long getNumber();
	std::vector<unsigned long long> getNumbers(int size);

};

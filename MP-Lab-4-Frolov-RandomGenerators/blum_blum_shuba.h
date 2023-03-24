#pragma once
#include <vector>

class blum_blum_shub {
private:
	unsigned long long seed = 0;
	unsigned long long M = 0; //M=p*q
	unsigned long long p = 0; // большое простое  1 << 20
	unsigned long long q = 0; //большое простое  1 << 31
	//p и q должны быть сравнимы с 3 по модулю 4, т.е. px=3(mod 4) и qx=3(mod 4) должны иметь корни
	//так же НОД(p-1, q-1) должен быть минимален для увеличения длины цикла у p-1=1048575 и q-1=2147483647
	//НОД равен 1.
public:
	blum_blum_shub(unsigned long long p, unsigned long long q);
	~blum_blum_shub() = default;
	void setSeed(unsigned long long seed);
	unsigned long long getNumber();
	std::vector<unsigned long long> getNumbers(int size);
};
#include "psgc.h"


psgc::psgc() {
	//
}

void psgc::setSeed(unsigned long long seed) {
	this->seed = seed;
}

unsigned long long psgc::getNumber() {
	this->seed = (this->seed * this->mul + this->p) % this->mod;
	return this->seed;
}

std::vector<unsigned long long> psgc::getNumbers(int size) {
	std::vector<unsigned long long> res;
	res.resize(size);
	for (int i = 0; i < size; ++i) {
		res[i] = this->getNumber();
	}
	return res;
}
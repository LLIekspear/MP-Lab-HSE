#include "blum_blum_shuba.h"

blum_blum_shub::blum_blum_shub(unsigned long long p, unsigned long long q) {
	this->p = p;
	this->q = q;
	this->M = p * q;
}

void blum_blum_shub::setSeed(unsigned long long newSeed) {
	this->seed = newSeed;
}

unsigned long long blum_blum_shub::getNumber() {
	this->seed = (this->seed * this->seed) % this->M;
	return this->seed;
}

std::vector<unsigned long long> blum_blum_shub::getNumbers(int size) {
	std::vector<unsigned long long> res;
	res.resize(size);
	for (int i = 0; i < size; ++i) {
		res[i] = this->getNumber();
	}
	return res;
}
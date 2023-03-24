#pragma once
#include <vector>

class psgc {
private:
	unsigned long long seed = 0; //0<=seed<mod
	unsigned long long mod = 1 << 31 - 1; //2^31 -1, ������ ���� ����������� � >=2! 
	unsigned long long p = 0; //�������� ��������� ����������� �����, �� ��������� � ����������������� ������ ������������ ����� ������, 0<=c<mod
	unsigned long long mul = 16807;//0<=mul<mod
public:
	psgc();
	~psgc() = default;
	void setSeed(unsigned long long seed);
	unsigned long long getNumber();
	std::vector<unsigned long long> getNumbers(int size);

};

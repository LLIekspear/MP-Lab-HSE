#pragma once
#include <vector>

class blum_blum_shub {
private:
	unsigned long long seed = 0;
	unsigned long long M = 0; //M=p*q
	unsigned long long p = 0; // ������� �������  1 << 20
	unsigned long long q = 0; //������� �������  1 << 31
	//p � q ������ ���� �������� � 3 �� ������ 4, �.�. px=3(mod 4) � qx=3(mod 4) ������ ����� �����
	//��� �� ���(p-1, q-1) ������ ���� ��������� ��� ���������� ����� ����� � p-1=1048575 � q-1=2147483647
	//��� ����� 1.
public:
	blum_blum_shub(unsigned long long p, unsigned long long q);
	~blum_blum_shub() = default;
	void setSeed(unsigned long long seed);
	unsigned long long getNumber();
	std::vector<unsigned long long> getNumbers(int size);
};
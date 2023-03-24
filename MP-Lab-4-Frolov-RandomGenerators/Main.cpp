#include <iostream>
#include "psgc.h"
#include <ctime>
#include <chrono>
#include <random>
#include "blum_blum_shuba.h"

double mean(std::vector<unsigned long long>& numbers) {
	unsigned long long sum = 0;
	for (int i = 0; i < numbers.size(); ++i) {
		sum += numbers[i];
	}
	return sum / static_cast<double>(numbers.size());
}

double deviation(double mean, std::vector<unsigned long long>& numbers) {
	double sum = 0;
	for (int i = 0; i < numbers.size(); ++i) {
		sum += (numbers[i] - mean) * (numbers[i] - mean);
	}
	return std::sqrt(sum/numbers.size());
}

double variationCoefficient(double deviation, double mean) {
	return deviation / mean;
}

double chiSquare(std::vector<unsigned long long>& numbers) {
	//нормируем числа, т.к. лежат целые
	std::vector<double> norm_numbers;
	for (int i=0; i < numbers.size(); ++i) {
		norm_numbers.push_back(numbers[i]/static_cast<double>(1<<31 -1));
	}
	unsigned int n = norm_numbers.size();
	unsigned int k = 1 + 3.222 * std::log(n); //число интервалов по правилу Стерджесса
	double p = 1 / static_cast<double>(k);
	std::vector<unsigned int> n_i(k, 0);
	for (int i = 0; i < norm_numbers.size(); ++i) {
		for (int j = 0; j < k; ++j) {
			if (p * j <= norm_numbers[i] && p * (j + 1) > norm_numbers[i]) {
				n_i[j] += 1;
			}
		}
	}
	double chi = 0;
	for (int i = 0; i < n_i.size(); ++i) {
		chi += ((static_cast<double>(n_i[i]) - p * n) * (static_cast<double>(n_i[i]) - p * n)) / (p * n);
	}
	return chi;
}

int main() {
	std::system("chcp 1251");
	int choosed = 0;
	int flag = 0;
	//std::vector<unsigned long long> res;
	while (flag == 0) {
		std::cout << "\nВыберите ПГСЧ: 0 - смешанный конгруэнтный метод, 1 - алгоритм Блюм-Блюма-Шуба, 2 - mt19937(вихрь Мерсенна)\n";
		std::cin >> choosed;
		int size = 0;
		std::cout << "\nВведите кол-во генерируемых элементов: \n";
		std::cin >> size;
		if (choosed == 0) {
			std::vector<unsigned long long> res(size, 0);
			psgc rand1;
			rand1.setSeed(std::time(NULL));
			auto begin = std::chrono::steady_clock::now();
			res = rand1.getNumbers(size);
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			double meanV = mean(res);
			double deviationV = deviation(meanV, res);
			double varCoeff=variationCoefficient(deviationV, meanV);
			double chi2 = chiSquare(res);
			std::cout << "\nСреднее выборки: " << meanV<<" Отклонение выборки: "<<deviationV<<" Коэффициент вариации: "<<varCoeff<<" Критерий Хи-квадрат: "<<chi2<<"\n";
			std::cout << "\nОбщее кол-во сгенерированных элементов: " << res.size()<<". Понадобилось времени на генерацию: "<<elapsed_ms.count()<<"ms\n";
			for (int i = 0; i < 10; ++i) {
				std::cout << " " << res[i];
			}
		}
		else if (choosed == 1) {
			//blum_blum_shub bbs(1 << 20, 1 << 31);
			std::vector<unsigned long long> newRes(size, 0);
			blum_blum_shub bbs(1<<10, 1<<20);
			bbs.setSeed(std::time(NULL));
			auto begin = std::chrono::steady_clock::now();
			newRes = bbs.getNumbers(size);
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			double meanV = mean(newRes);
			double deviationV = deviation(meanV, newRes);
			double varCoeff = variationCoefficient(deviationV, meanV);
			double chi2 = chiSquare(newRes);
			std::cout << "\nСреднее выборки: " << meanV << " Отклонение выборки: " << deviationV << " Коэффициент вариации: " << varCoeff << " Критерий Хи-квадрат: " << chi2 << "\n";
			std::cout << "\nОбщее кол-во сгенерированных элементов: " <<newRes.size() << ". Понадобилось времени на генерацию: " << elapsed_ms.count() << "ms\n";
			for (int i = 0; i < 10; ++i) {
				std::cout << " " << newRes[i];
			}
		}
		else if (choosed == 2) {
			std::mt19937 mt_rand(std::time(NULL));
			std::vector<unsigned long long> newRes(size, 0);
			auto begin = std::chrono::steady_clock::now();
			for (int i = 0; i < size; ++i) {
				newRes[i] = mt_rand() % (1 << 31 - 1);
			}
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			double meanV = mean(newRes);
			double deviationV = deviation(meanV, newRes);
			double varCoeff = variationCoefficient(deviationV, meanV);
			double chi2 = chiSquare(newRes);
			std::cout << "\nСреднее выборки: " << meanV << " Отклонение выборки: " << deviationV << " Коэффициент вариации: " << varCoeff << " Критерий Хи-квадрат: " << chi2 << "\n";
			std::cout << "\nОбщее кол-во сгенерированных элементов: " << newRes.size() << ". Понадобилось времени на генерацию: " << elapsed_ms.count() << "ms\n";
			for (int i = 0; i < 10; ++i) {
				std::cout << " " << newRes[i];
			}
		}
		else {
			std::cout << "\nНеверный выбор, повторите попытку снова.\n";
		}
		std::cout << "\nВыберите опцию: 0 - воспользоваться функционалом программы снова, 1 - завершить работу программы\n";
		std::cin >> flag;
	}
	exit(0);
}
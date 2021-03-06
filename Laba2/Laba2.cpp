#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <complex>
#include "omp.h"

const int shiftInt = 31;

/* --------------- Task 1 --------------- */

int arrCountPositive(int* arr, int size)
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < size; ++i)
	{
		if (arr[i] > 0)
		{
			++count;
		}
	}
	return count;
}
int arrCountPositiveOptim(int* arr, int size)
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < size; ++i)
	{
		count -= (-arr[i]) >> shiftInt;
	}
	return count;
}

void Task1()
{
	int arr[] = { 0, -1, 2, -3, 4, -5, -6, -7, 8, -9, 10 };
	std::cout << arrCountPositive(arr, sizeof(arr) / sizeof(int)) << std::endl;
	std::cout << arrCountPositiveOptim(arr, sizeof(arr) / sizeof(int)) << std::endl;
}

/* --------------- Task 2 --------------- */

void bubleSort(int* arr, int size)
{
	const int shift = 31;
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[j] > arr[i])
			{
				int temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
		}
	}
}

int maxForBubleSortOptim(int x, int y)
{
	return x - ((x - y) & ((x - y) >> shiftInt));
}
int minForBubleSortOptim(int x, int y)
{
	return y + ((x - y) & ((x - y) >> shiftInt));
}

// n + 1 stop
void bubleSortOptim(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			int temp = maxForBubleSortOptim(arr[i], arr[j]);
			arr[j] = minForBubleSortOptim(arr[i], arr[j]);
			arr[i] = temp;
		}
	}
}

void Task2()
{
	int arr[] = { 0, -1, 2, -3, 4, -5, -6, -7, 8, -9, 10 };

	//bubleSort(arr, sizeof(arr) / sizeof(int));
	bubleSortOptim(arr, sizeof(arr) / sizeof(int));

	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
	{
		std::cout << arr[i];
	}
}

/* --------------- Task 3 --------------- */

int defenitionSize(int size1, int size2)
{
	return size1 + size2 - 1;
}

void multiplyPolinom(int* arr1, int size1, int* arr2, int size2, int* arrResult, int sizeResult)
{
	// fill array zero
	for (int i = 0; i < sizeResult; ++i)
	{
		arrResult[i] = 0;
	}

	for (int i = 0; i < size1; ++i)
	{
		for (int j = 0; j < size2; ++j)
		{
			arrResult[i + j] += arr1[i] * arr2[j];
		}
	}
}

void Task3()
{
	int arr1[] = { 1, 2, 3, 4, 5, 6 };
	int arr2[] = { 1, 2, 3 };

	int size1 = sizeof(arr1) / sizeof(int);
	int size2 = sizeof(arr2) / sizeof(int);

	int sizeResult = defenitionSize(size1, size2);
	int* arrResult = new int[sizeResult];

	multiplyPolinom(arr1, size1, arr2, size2, arrResult, sizeResult);

	for (int i = 0; i < sizeResult; ++i)
	{
		std::cout << arrResult[i] << std::endl;
	}

	delete arrResult;
}

/* --------------- Task 4 --------------- */

int roundNumber(double x)
{
	int castX = static_cast<int>(x);
	if (x - castX >= 0.5)
	{
		return castX + 1;
	}
	else
	{
		return castX;
	}
}
int roundNumber(float x)
{
	int castX = static_cast<int>(x);
	if (x - castX >= 0.5)
	{
		return castX + 1;
	}
	else
	{
		return castX;
	}
}

void roundArray(double* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = roundNumber(arr[i]);
	}
}
void roundArray(float* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = roundNumber(arr[i]);
	}
}

int roundNumberOptim(double x)
{
	return static_cast<int>(x + 0.5 + (static_cast<int>(x * 10) >> shiftInt));
}
int roundNumberOptim(float x)
{
	return static_cast<int>(x + 0.5 + (static_cast<int>(x * 10) >> shiftInt));
}

void roundArrayOptim(double* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = roundNumberOptim(arr[i]);
	}
}
void roundArrayOptim(float* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = roundNumberOptim(arr[i]);
	}
}

void Task4()
{
	double arrDouble[] = { -0.3, -0.5, -0.8, 0.3, 0.5, 0.8, 1.5, 2.5, 3.5, 1.1, 2.2, 3.6, 3.7, 4.8, 5.9, -1.5, -2.5, -3.5, -1.1, -2.2, -3.6, -3.7, -4.8, -5.9 };
	roundArrayOptim(arrDouble, sizeof(arrDouble) / sizeof(double));

	for (int i = 0; i < sizeof(arrDouble) / sizeof(double); ++i)
	{
		std::cout << arrDouble[i] << std::endl;
	}
}

/* --------------- Task 5 --------------- */

void setOnFailPrediction(char* tablePrediction, char state, char value)
{
	tablePrediction[state] = value;
}
char prediction(char* tablePrediction, char state)
{
	return tablePrediction[state];
}
int adaptPrediction(char* arrInput, unsigned int size)
{
	//                        00 01 10 11
	char tablePrediction[] = {0, 0, 0, 0};

	int countFails = 0;

	char previous = 0;
	for (int i = 0; i < size - 2; ++i)
	{
		if (prediction(tablePrediction, previous * 2 + arrInput[i]) != arrInput[i + 1])
		{
			setOnFailPrediction(tablePrediction, previous * 2 + arrInput[i], arrInput[i + 1]);
			++countFails;
		}
		previous = arrInput[i];
	}

	return countFails;
}

void random_arr(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % 2 == 0 ? rand() : -rand();
	}
}

void timeCountPositive()
{
	const int test_count = 1000;
	const int size = 10000;
	int arr[size];

	for (int i = 0; i < test_count; ++i)
	{
		arrCountPositive(arr, size);
	}
	double startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		arrCountPositive(arr, size);
	}
	double finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;

	for (int i = 0; i < test_count; ++i)
	{
		arrCountPositiveOptim(arr, size);
	}
	startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		arrCountPositiveOptim(arr, size);
	}
	finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;
}

void timeBubleSort()
{
	const int test_count = 1000;
	const int size = 1000;
	int arr[size];

	for (int i = 0; i < test_count; ++i)
	{
		bubleSort(arr, size);
	}
	double startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		bubleSort(arr, size);
	}
	double finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;

	for (int i = 0; i < test_count; ++i)
	{
		bubleSortOptim(arr, size);
	}
	startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		bubleSortOptim(arr, size);
	}
	finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;
}



//const double pi = std::atan(1) * 4;
//
//int my_max(int x, int y)
//{
//	return x - ((x - y) & ((x - y) >> shiftInt));
//}
//
//int my_round(double x)
//{
//	return static_cast<int>(x + 0.5 + (static_cast<int>(x * 10) >> shiftInt));
//}
//
//void fft(std::vector<std::complex<double>> & arr, int sign)
//{
//	// n - 1 ����������
//	if (arr.size() == 1)
//	{
//		return;
//	}
//	// �������� 2n - 2 ����������, �� ��� �� �����, �� ��� ��� ������
//	std::vector<std::complex<double>> even(arr.size() / 2), odd(arr.size() / 2);
//
//	// n - 1 ����������
//	for (int i = 0, j = 0; i < arr.size(); i += 2, ++j)
//	{
//		even[j] = arr[i];
//		odd[j] = arr[i + 1];
//	}
//	fft(even, sign);
//	fft(odd, sign);
//
//	double angular = sign * 2 * pi / arr.size();
//	std::complex<double> cur_root(1), main_root(std::cos(angular), std::sin(angular));
//
//	// n - 1 ����������
//	for (int i = 0; i < arr.size() / 2; ++i)
//	{
//		arr[i] = even[i] + cur_root * odd[i];
//		arr[i + arr.size() / 2] = even[i] - cur_root * odd[i];
//
//		arr[i] /= 2 - my_max(0, sign);
//		arr[i + arr.size() / 2] /= 2 - my_max(0, sign);
//
//		cur_root *= main_root;
//	}
//}
//
//// 9(n - 1) + 8 ����������
//std::vector<int> multiply(const std::vector<int> & a, const std::vector<int> & b)
//{
//	int res_size = 1;
//	int max_size = my_max(a.size(), b.size());
//
//	while (res_size < max_size)
//	{
//		res_size *= 2;
//	}
//	res_size *= 2;
//
//	std::vector<std::complex<double>> comp_a(a.begin(), a.end());
//	std::vector<std::complex<double>> comp_b(b.begin(), b.end());
//
//	comp_a.resize(res_size, 0);
//	comp_b.resize(res_size, 0);
//
//	fft(comp_a, 1);
//	fft(comp_b, 1);
//
//	for (int i = 0; i < res_size; ++i)
//	{
//		comp_a[i] *= comp_b[i];
//	}
//	fft(comp_a, -1);
//
//	std::vector<int> res(res_size);
//	for (int i = 0; i < res_size; ++i)
//	{
//		res[i] = my_round(comp_a[i].real());
//	}
//	return res;
//}
//
//std::vector<int> random_arr(int size)
//{
//	std::vector<int> arr(size);
//	for (int i = 0; i < size; ++i)
//	{
//		arr[i] = rand() % 2 == 0 ? rand() : -rand();
//	}
//	return arr;
//}



void timeMultiplyPolinom()
{
	const int test_count = 10000;
	const int size1 = 1000;
	const int size2 = 500;

	int arr1[size1];
	int arr2[size2];

	int sizeResult = defenitionSize(size1, size2);
	int* arrResult = new int[sizeResult];

	for (int i = 0; i < test_count; ++i)
	{
		multiplyPolinom(arr1, size1, arr2, size2, arrResult, sizeResult);
	}
	double startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		multiplyPolinom(arr1, size1, arr2, size2, arrResult, sizeResult);
	}
	double finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;

	delete arrResult;

	/*std::vector<int> data_a = random_arr(size1);
	std::vector<int> data_b = random_arr(size2);
	std::vector<int> res;

	for (int i = 0; i < test_count; ++i)
	{
		res = multiply(data_a, data_b);
	}
	startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		res = multiply(data_a, data_b);
	}
	finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;*/
}

void random_double_arr(double* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		double val = static_cast<double>(rand()) / rand();
		arr[i] = rand() % 2 == 0 ? val : -val;
	}
}

void random_float_arr(float* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		float val = static_cast<float>(rand()) / rand();
		arr[i] = rand() % 2 == 0 ? val : -val;
	}
}

void timeRoundArray()
{
	const int test_count = 10000;
	const int size = 1000;

	// Double
	double arrDouble[size];

	for (int i = 0; i < test_count; ++i)
	{
		roundArray(arrDouble, size);
	}
	double startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		roundArray(arrDouble, size);
	}
	double finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;

	for (int i = 0; i < test_count; ++i)
	{
		roundArrayOptim(arrDouble, size);
	}
	startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		roundArrayOptim(arrDouble, size);
	}
	finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;

	// Float
	float arrFloat[size];

	for (int i = 0; i < test_count; ++i)
	{
		roundArrayOptim(arrFloat, size);
	}
	startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		roundArray(arrFloat, size);
	}
	finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;

	for (int i = 0; i < test_count; ++i)
	{
		roundArrayOptim(arrFloat, size);
	}
	startTime = omp_get_wtime();
	for (int i = 0; i < test_count; ++i)
	{
		roundArrayOptim(arrFloat, size);
	}
	finishTime = omp_get_wtime();

	std::cout << finishTime - startTime << std::endl;
}


void Task5()
{
	//               0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
	//char arr[] = { 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0 };
	//std::cout << adaptPrediction(arr, sizeof(arr) / sizeof(char)) << std::endl;

	//timeCountPositive();
	//timeBubleSort();
	//timeMultiplyPolinom();
	//timeRoundArray();
}

/* --------------- Main --------------- */

int main()
{
	//Task1();
	//Task2();
	//Task3();
	//Task4();
	Task5();

	//int wait;
	//std::cin >> wait;
	return 0;
}



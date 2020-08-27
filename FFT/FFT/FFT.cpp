#define _USE_MATH_DEFINES
#include <iostream>
#include <complex>
#include <math.h>
#include "timeCnt.h"

using namespace std;

complex<double> * DFT(complex<double> input[],int size)
{
	complex<double>* result = new complex<double>[size];
	complex<double> coeff = complex<double>(0,(2*M_PI)/size);
	for (int iter = 0; iter < size; iter++)
	{
		double k = (double)iter;
		result[iter] = complex<double>(0,0);
		for (int j = 0; j < size; j++)
		{
			double n = (double)j;
			result[iter] += input[j] * exp(coeff * k * n);
		}
	}
	return result;
}

complex<double> * FFT(complex<double> input[], int size)
{
	if (size == 1)
	{
		return &input[0];
	}
	int temp_size = size / 2;
	complex<double> coeff = complex<double>(0.0, (2 * M_PI) / size);
	complex<double>* result = new complex<double>[size];
	complex<double>* even = new complex<double>[temp_size];
	complex<double>* odd = new complex<double>[temp_size];
	int even_iterator = 0;
	int odd_iterator = 0;
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			even[even_iterator] = input[i];
			even_iterator++;
		}
		else
		{
			odd[odd_iterator] = input[i];
			odd_iterator++;
		}
	}
	even = FFT(even, temp_size);
	odd = FFT(odd, temp_size);
	for (int i = 0; i < temp_size; i++)
	{
		complex<double> ci = (complex<double>) i;
		complex<double> t = exp(coeff * ci) * odd[i];
		result[i] = even[i] + t;
		result[i + temp_size] = even[i] - t;
	}
	delete[] even;
	delete[] odd;
	return result;
}


int main()
{
	bool flag = false;
	timeCnt timer;
	int size = 1;
	for (int i = 0; i < 13; i++)
	{
		size *= 2;
		complex<double>* test = new complex<double>[size];
		for (int j = 0; j < size; j++)
		{
			test[j] = j / (double) size;
		}
		timer.Tic();
		cout << "DFT for " << size << " elements"<<endl;
		complex<double>* DFT_result = DFT(test, size);
		timer.Toc();
		timer.Tic();
		cout << "FFT for " << size << " elements" <<endl;
		complex<double>* FFT_result = FFT(test, size);
		timer.Toc();
		if (i == 2)
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
		if (flag == true)
		{
			for (int k = 0; k < size; k++)
			{
				cout << FFT_result[k] << endl;
			}
		}
		delete[] test;
	}
	complex<double> test[8] = {0.0 / 8.0, 1.0/8.0,2.0 / 8.0,3.0 / 8.0,4.0 / 8.0,5.0 / 8.0,6.0 / 8.0,7.0 / 8.0};
	complex<double>* DFT_result = DFT(test, 8);
	complex<double>* FFT_result = FFT(test, 8);
	for (int i = 0; i < 8; i++)
	{
		cout << DFT_result[i] << endl;
		cout << FFT_result[i] << endl;
	}
	return 0;
}

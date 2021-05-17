#include "Generator.h"
#include <iostream>
#include <vector>
#include <ctime>

Generator::Generator() {};
string Generator::generate()
{
	srand(time(0));
	int length,temp;
	char input;
	string ret;
	cout << "Length of password: ";
	cin >> length;

	for (int i = 0; i < length; i++)
	{
		temp = 0 + (rand() % 126);
		itoa(temp, &input,1);
		ret.push_back(input);
	}
	return ret;
}
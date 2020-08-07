#include "Save.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"Encoder.h"

using namespace std;

Save::Save() {};
void Save::save_to_file(string input)
{
	fstream file;
	file.open("base.txt", ios::out | ios::app);
	if (!file.good())
	{
		exit(0);
	}
	file << input;
	file.close();
}

vector<string> Save::read_from_file()
{
	vector<string> result;
	string temp;
	fstream file;
	file.open("base.txt");
	while (getline(file,temp))
	{
		result.push_back(temp);
	}
	file.close();
	Encoder en = Encoder::Encoder();
	for (int i = 0; i < result.size();i++)
	{
		result[i] = en.Decode(result[i]);
	}
	return result;
}
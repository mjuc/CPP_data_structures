#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Encoder
{
private:
	int key;
public:	
	Encoder();
	vector<int> Encode(std::string input);
	string Decode(vector<int> input);
};


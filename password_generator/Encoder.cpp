#include "Encoder.h"

using namespace std;


	Encoder::Encoder()
	{
		Encoder::key = 999331;
	}
	vector<int> Encoder::Encode(std::string input)
	{
		vector<int> result;
		for (unsigned int i = 0; i < input.length(); i++)
		{		
			result.push_back(atoi(&input[i]) / key);
		}
		return result;
	}
	string Encoder::Decode(vector<int> input)
	{
		string result;
		for (unsigned int i = 0; i < input.size(); i++)
		{
			char temp;
			itoa((input[i] * key),&temp,1);
			result.push_back(temp);
		}		
		return result;
	}
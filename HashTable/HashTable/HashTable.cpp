#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class HashTable
{
public:
	int added,size;
	double level;
	struct Node
	{
		string value;
		int key;
	};
	vector<vector<Node*>> HashArray;
	HashTable()
	{
		HashArray = vector<vector<Node*>>(256);
		level = 0;
		added = 0;
		size = 256;
	}
	void Add(string input)
	{
		if (level < 0.75)
		{
			Node* TempNode = new Node;
			TempNode->value = input;
			TempNode->key = HashFunction(input);
			HashArray[TempNode->key].push_back(TempNode);
			added++;
			level = added / size;
		}
		else
		{
			Node* TempNode = new Node;
			TempNode->value = input;
			TempNode->key = HashFunction(input);
			HashArray[TempNode->key].push_back(TempNode);
		}
	}

	int HashFunction(string input)
	{
		int res = 0;
		for (int i = 0; i < input.length(); i++)
		{
			int ch = input[i];
			res += ch * pow(31, input.length() - i - 1);
		}
		res = (this->size + res % this->size) % this->size;
		return res;
	}
	Node* Find(int key)
	{
		bool found = false;
		for (int i = 0; i < HashArray.size(); i++)
		{
			if (i == key && HashArray[i].size() != 0)
			{
				found = true;
				return HashArray[i][0];
			}
		}
		if (found == false)
		{
			return NULL;
		}
	}
	void Remove(int key)
	{
		for (int j = 0; j < HashArray[key].size(); j++)
			{
				delete HashArray[key][j];
			}
			
	}
	void Clear()
	{
		for (int i = HashArray.size(); i > -1; i--)
		{
			for (int j = 0; j < HashArray[i].size(); j++)
			{
				HashArray[i].pop_back();
			}
			HashArray.pop_back();
		}
	}
	void Rehash()
	{
		int temp_size = this->size;
		this->size = 2 * this->size;
		vector<vector<Node*>> temp = vector<vector<Node*>>(this->size);
		for (int i = 0; i < temp_size; i++)
		{
			for (int j = 0; j < HashArray[i].size(); j++)
			{
				Node* TempNode = HashArray[i][j];
				TempNode->key = HashFunction(TempNode->value);
				temp[TempNode->key].push_back(TempNode);
			}
		}
		Clear();
		for (int i = 0; i < temp.size(); i++)
		{
			for (int j = 0; j < temp[i].size(); j++)
			{
				HashArray[temp[i][j]->key].push_back(temp[i][j]);
			}
		}
		delete &temp;
	}
	void Print()
	{
		for (int j = 0; j < HashArray.size(); j++)
		{
			for (int i = 0; i < HashArray[j].size(); i++)
			{
				cout << HashArray[j][i]->key << endl;
				cout << HashArray[j][i]->value << endl;
			}
		}
	}
};

int HashFunction2(string input)
{
	int res = 0;
	for (int i = 0; i < input.length(); i++)
	{
		int ch = input.at(i);
		res += ch * pow(31, input.length()-i-1);
	}
	res = (256 + res % 256) % 256;
	return res;
}

int main()
{
	srand(time(NULL));
	HashTable test;
	int it = 1;
	for (int t = 0; t < 2; t++)
	{
		it *= 10;
		clock_t t1 = clock();
		for (int i = 0; i < it; i++)
		{
			string input;
			for (int j = 0; j < 6; j++)
			{
				string input_element;
				input_element = ((rand() % ('z' - 'a')) + 'a');
				input += input_element;
			}
			test.Add(input);
		}
		clock_t t2 = clock();
		double time = (t2 - t1)/(double)CLOCKS_PER_SEC;
		cout << "Adding time for :" << it << " elements: " << time << endl;
		clock_t t3 = clock();
		for (int i = 0; i < 10000; i++)
		{
			int pattern = rand();
			test.Find(pattern);
		}
		clock_t t4 = clock();
		double search_time = (t4 - t3) / (double)CLOCKS_PER_SEC;
		cout << "Search time for 10000 searches in " << it << " elements: " << search_time << endl;
	}
	test.Print();
	cout <<"hc: " << HashFunction2("tukiss") << endl;
	cout << "hc: " << HashFunction2("swfira") << endl;
}

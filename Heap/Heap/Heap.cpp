#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

template<class T>

class Heap
{
public:
	int root;
	int length;
	vector<T> heap;
	Heap()
	{
		this->root = 0;
		this->length = 0;
	}
	Heap(T *input,int cond)
	{
		this->root = 0;
		int i = 0;
		while (i < cond)
		{
			heap.push_back(input[i]);
			i++;
			this->length++;
		}
		int j = 1;
		while (j < cond)
		{
			//if (Compare(heap[j], heap[(j - 1) / 2]) == 1)
			if (heap[j] >  heap[(j - 1) / 2]) 
			{
				HeapUp(j);
			}
			j++;
		}
	}
	~Heap() 
	{
	}
	void Add(T input)
	{
		
		if (this->length == 0)
		{
			heap.push_back(input);
			this->length++;
		}
		else
		{
			heap.push_back(input);
			this->length++;
			Fix(heap,this->length - 1);
		}
	}
	int Compare(T input1, T input2)
	{
		int check = input1 - input2;
		if (check < 0)
		{
			return -1;
		}
		else
		{
			if (check > 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	
	void HeapDown(int index)
	{
		int newindex = (2 * index) + 1;
		if (newindex+1 < this->length)
		{
			if (heap[index] < heap[newindex])
			{
				T temp = heap[index];
				heap[index] = heap[newindex];
				heap[newindex] = temp;
				HeapDown(newindex);
			}
			else
			{
				newindex = (2 * index) + 2;
				if (heap[index] < heap[newindex])
				{
					T temp = heap[index];
					heap[index] = heap[newindex];
					heap[newindex] = temp;
					HeapDown(newindex);
				}
			}
		}		
	}
	void HeapUp(int index)
	{	
		int i = index;
		while (i > 0)
		{
			int parent = (i - 1) / 2;
			if (heap[i] > heap[parent])
			{
				T temp = heap[i];
				heap[i] = heap[parent];
				heap[parent] = temp;
				i = parent;
			}
			else
			{
				break;
			}
		}
	}
	T Pop()
	{
		T result = heap[this->root];
		for (int i = 0; i < heap.size()-2; i++)
		{
			heap[i] = heap[i + 1];
		}
		heap.pop_back();
		this->length=heap.size();
		for (int j = heap.size() - 1; j > -1; j--)
		{
			Fix(heap, j);
		}
		return result;
	}
	void Fix(vector<T> heap,int index)
	{
		if ((index - 1) / 2 >= 0)
		{
			if (heap[index] < heap[index + 1])
			{
				T temp = heap[index];
				heap[index] = heap[index + 1];
				heap[index + 1] = temp;
			}
			if (heap[index] > heap[(index - 1) / 2])
			{
				HeapUp(heap, index);
				int newindex = (index - 1) / 2;
				Fix(heap, newindex);
			}
			else
			{
				int cond = (2 * index) + 2;
				if (cond < heap.size() - 1)
				{
					if (heap[index] < heap[(2 * index) + 1])
					{
						int newindex = (2 * index) + 1;
						HeapDown(heap, index, newindex);
					}
					else
					{
						if (heap[index] < heap[(2 * index) + 2])
						{
							int newindex = (2 * index) + 2;
							HeapDown(heap, index, newindex);
						}
					}
				}
			}
		}
		
	}
	void Print()
	{
		int index = this->root;
		while (index < this->length)
		{
			T temp = heap[index];
			cout << temp<<endl;
			index++;
		}
	}
	T* Sort()
	{
		int size = heap.size();
		T* result = new T[size];
		Heap<T> *temp = this;
		int i = 1;
		while (temp->length > 0)
		{
			result[size - i]=temp->heap[0];
			int last = temp->length - 1;
			swap(temp->heap[0], temp->heap[last]);
			temp->length--;
			temp->HeapDown(0);
			temp->HeapUp(1);
			temp->HeapUp(2);
		}
		return result;
	}
};

void CountSort(int *arr,int length)
{
	int result[5000];
	
	for (int j = 0; j < 5000; j++)
	{
		result[j] = 0;
	}

	for (int i = 0; i < length; i++)
	{	
		result[arr[i]]++;
	}

	int cnt = 0;
	for (int j = 0; j < 5000; j++)
	{
		if (result[j] > 0)
		{
			for (int i = 0; i < result[j]; i++)
			{
				arr[cnt] = j;
				cnt++;
			}
		}
	}
}
void BucketSort(int *arr, int length)
{
	vector<vector<int>> bucket(5000);
	for (int j = 0; j < 5000; j++)
	{
		for (int i = 0; i < length; i++)
		{
			if (arr[i] == j)
			{
				bucket[j].push_back(arr[i]);
			}
		}
	}
	int cnt = 0;
	for (int j = 0; j < 5000; j++)
	{
		if (bucket[j].empty() != true)
		{
			for (int i = 0; i < bucket[j].size(); i++)
			{
				arr[cnt] = bucket[j][i];
				cnt++;
			}
		}
	}
}

int main()
{
	int it = 1;
	for (int i = 0; i < 7; i++)
	{
		it *= 10;
		int* tab = new int[it];
		for (int j = 0; j < it; j++)
		{
			tab[j] = rand() % 4999 + 0;
		}
		int* tab2 = new int[it];
		memcpy(tab2, tab, it);
		Heap<int>* test = new Heap<int>(tab, it);
		clock_t t1 = clock();
		CountSort(tab, it);
		clock_t t2 = clock();
		double tim = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "Counting sort time of " << it << " elements: " << tim << endl;
		clock_t t3 = clock();
		BucketSort(tab, it);
		clock_t t4 = clock();
		double tim2 = (t4 - t3) / (double)CLOCKS_PER_SEC;
		cout << "Bucket sort time of " << it << " elements: " << tim2 << endl;
		clock_t t5 = clock();
		test->Sort();
		clock_t t6 = clock();
		double tim3 = (t6 - t5) / (double)CLOCKS_PER_SEC;
		cout << "Heap sort time of " << it << " elements: " << tim3 << endl;
	}
	return 0;

}

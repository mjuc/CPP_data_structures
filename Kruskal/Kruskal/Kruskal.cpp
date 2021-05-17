#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

class TimeCnt
{
public:
	TimeCnt() {}
	~TimeCnt(){}
	void Tic()
	{
		prevtim = clock();
	}
	void Toc()
	{
		clock_t posttim = clock();
		double elapsed_time = (posttim - prevtim) / (double)CLOCKS_PER_SEC;
		cout << "Elapsed time: " << elapsed_time << endl;
	}
private:
	clock_t prevtim;
};
struct Edge 
{
	int parent_node;
	int child_node;
	float value;
};


void quickSort(vector<Edge *> input, int begin, int end)
{
	int i = begin;
	int j = end;
	Edge * x = input[(begin + end) / 2];
	do {
		while (input[i]->value < x->value) i++;
		while (input[j]->value > x->value) j--;

		if (i <= j) {
			swap(input[i]->parent_node, input[j]->parent_node);
			swap(input[i]->child_node, input[j]->child_node);
			swap(input[i]->value, input[j]->value);
			
			i++;
			j--;
		}
	} while (i <= j);
	if (begin < j) quickSort(input, begin, j);
	if (end > i) quickSort(input, i, end);
}

vector<Edge*> Create_input(string filename)
{
	TimeCnt timer;
	vector<Edge*> Edges;
	fstream file;
	int lines = 1;
	int limit = 0;
	int n,m;
	string str;
	file.open(filename, fstream::in);
	if (!file.good())
	{
		exit(0);
	}
	do
	{
		if (lines == 1)
		{
			getline(file, str);
			n = atoi(str.c_str());
			limit += n + 2;
		}
		else if (lines > n + 2)
		{
			Edge* edg = new Edge;
			for (int i = 0; i < 3; i++)
			{
				switch (i)
				{
				case 0:
				{
					file >> str;
					edg->parent_node = atoi(str.c_str());
					break;
				}
				case 1:
				{
					file >> str;
					edg->child_node = atoi(str.c_str());
					break;
				}
				case 2:
				{
					file >> str;
					edg->value = atof(str.c_str());
					break;
				}
				}
			}
			Edges.push_back(edg);
		}
		else if(lines == n+2)
		{
			getline(file, str);
			m = atoi(str.c_str());
			limit += m;
		}
		else
		{
			getline(file, str);
		}
		lines++;
	} while (lines <= limit);
	file.close();
	cout << endl;
	cout << "Sorting edges." << endl;
	timer.Tic();
	quickSort(Edges,0,Edges.size()-1);
	timer.Toc();
	return Edges;
}
class UnionFind
{
private:
	TimeCnt timer;
	vector<int> parents,size;
	vector<Edge*> Graph_edges;
	int GetNodeNumber(string filename)
	{
		int n;
		string str;
		fstream file;
		file.open(filename, fstream::in);
		if (!file.good())
		{
			return -1;
		}
		getline(file, str);
		n = atoi(str.c_str());
		file.close();
		return n;
	}
public:
	UnionFind(vector<Edge*> input,string filename)
	{
		int n = GetNodeNumber(filename);
		this->parents = vector<int>(n);
		this->size = vector<int>(n);
		this->Graph_edges = input;
		for (int i = 0; i < n; i++)
		{
			parents[i] = i;
			size[i] = 1;
		}
	}
	~UnionFind()
	{
		for (int i = 0; i < this->parents.size(); i++)
		{
			parents.pop_back();
			size.pop_back();
		}
		for (int i = 0; i < Graph_edges.size(); i++)
		{
			Graph_edges.pop_back();
		}
	}
	bool Cycle(int node1, int node2)
	{
		return Find(node1) == Find(node2);
	}
	int Find(int node)
	{
		if (node == parents[node])
		{
			return node;
		}
		else
		{
			return Find(parents[node]);
		}
	}
	void Unify(int node1, int node2)
	{
		int root1 = Find(node1);
		int root2 = Find(node2);
		parents[root2] = root1;
		size[root1] += size[root2];
	}
	void UnifyByRank(int node1, int node2)
	{
		int root1 = Find(node1);
		int root2 = Find(node2);
		if (root1 == root2)
		{
			return;
		}
		if (size[root1] > size[root2])
		{
			size[root1] += size[root2];
			parents[root2] = parents[root1];
		}
		else
		{
			size[root2] += size[root1];
			parents[root1] = parents[root2];
		}
	}
	void Kruskal_spanning_tree(int use_UnionByRank)
	{
		int edg_num=0;
		int find_it = 0;
		float val_sum = 0;
		switch (use_UnionByRank)
		{
			case 0:
			{
				int i = 0;
				int prevnode = 0;
				cout << "Without union by rank" << endl;
				timer.Tic();
				cout << "Creating MST using Kruskal algorithm" << endl;
				while (edg_num<parents.size()-1)
				{
					if (!Cycle(Graph_edges[i]->parent_node, Graph_edges[i]->child_node))
					{

						Unify(Graph_edges[i]->parent_node, Graph_edges[i]->child_node);
						find_it += 2;
						val_sum += Graph_edges[i]->value;
						edg_num++;
						
					}
					find_it += 2;
					i++;
				}
				timer.Toc();
				cout << "Number of edges in MST: " << edg_num << endl;
				cout << "Number of Find method iterations: " << find_it << endl;
				cout << "Sum of edges values: " << val_sum << endl;
				break;
			}
			case 1:
			{
				int i = 0;
				int prevnode = 0;
				cout << "With union by rank" << endl;
				timer.Tic();
				cout << "Creating MST using Kruskal algorithm" << endl;
				while (edg_num < parents.size() - 1)
				{
					if (!Cycle(Graph_edges[i]->parent_node, Graph_edges[i]->child_node))
					{
						UnifyByRank(Graph_edges[i]->parent_node, Graph_edges[i]->child_node);
						find_it += 2;
						val_sum += Graph_edges[i]->value;
						edg_num++;
					}
					find_it += 2;
					i++;
				}
				timer.Toc();
				cout << "Number of edges in MST: " << edg_num << endl;
				cout << "Number of Find method iterations: " << find_it << endl;
				cout << "Sum of edges values: " << val_sum << endl;
				break;
			}
			default:
				cout << "Wrong specificator." << endl;
				break;
		}
	}
	void Reset()
	{
		int n = parents.size();
		for (int i = 0; i < n; i++)
		{
			parents[i] = i;
			size[i] = 1;
		}
		cout << endl;
	}
};

int main()
{
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
			case 0:
			{
				cout << "g1:" << endl;
				vector<Edge*> test = Create_input("g1.txt");
				UnionFind* teststr = new UnionFind(test, "g1.txt");
				for (int j = 0; j < 2; j++)
				{
					teststr->Kruskal_spanning_tree(j);
					teststr->Reset();
				}
			}
			case 1:
			{
				cout << "g2:" << endl;
				vector<Edge*> test = Create_input("g2.txt");
				UnionFind* teststr = new UnionFind(test, "g2.txt");
				for (int j = 0; j < 2; j++)
				{
					teststr->Kruskal_spanning_tree(j);
					teststr->Reset();
				}
			}
			case 2:
			{
				cout << "g3:" << endl;
				vector<Edge*> test = Create_input("g3.txt");
				UnionFind* teststr = new UnionFind(test, "g3.txt");
				for (int j = 0; j < 2; j++)
				{
					teststr->Kruskal_spanning_tree(j);
					teststr->Reset();
				}
			}
		}
	}
}
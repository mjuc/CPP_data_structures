#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class TimeCnt
{
public:
	TimeCnt() {}
	~TimeCnt() {}
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
struct Point
{
	float x;
	float y;
	int index;
};

class Points
{
public:

	Points(string name)
	{
		fstream file;
		int lines = 1;
		int n = 2;
		string str;
		file.open(name, fstream::in);
		while (lines<n+1)
		{
			if (lines == 1)
			{
				getline(file, str);
				n = atoi(str.c_str());
				n++;
			}
			else
			{
				Point* temp = new Point;
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
					{
						file >> str;
						temp->x = atof(str.c_str());
					}
					else
					{
						file >> str;
						temp->y = atof(str.c_str());
					}
				}
				temp->index = lines-1;
				this->points.push_back(temp);
			}
			lines++;
		}
		file.close();
		timer.Tic();		
		FindStartingPoint(this->points);
		MergeSort(points,1,points.size()-1);
		timer.Toc();
	}
	~Points();
	vector<Point*> Convex_Hull()
	{
		timer.Tic();
		vector<Point*> result;
		result.push_back(this->points[0]);
		result.push_back(this->points[1]);
		result.push_back(this->points[2]);
		if (Compare(this->points[1], this->points[2]) > 0)
		{
			swap(result[1]->x, result[2]->x);
			swap(result[1]->y, result[2]->y);
			swap(result[1]->index, result[2]->index);
			result.pop_back();
		}
		for (int i = 3; i < points.size()-1; i++)
		{
			result.push_back(points[i]);
			if (Compare(result[result.size() - 2], result[result.size() - 1]) > 0)
			{
				swap(result[result.size() - 2]->x, result[result.size() - 1]->x);
				swap(result[result.size() - 2]->y, result[result.size() - 1]->y);
				swap(result[result.size() - 2]->index, result[result.size() - 1]->index);
				result.pop_back();
			}
		}
		timer.Toc();
		return result;
	}
	void Print()
	{
		for (int i = 0; i < points.size(); i++)
		{
			cout << "idx: " << points[i]->index << endl;
			cout << "x: " << points[i]->x << endl;
			cout << "y: " << points[i]->y << endl;
		}
	}
	vector<Point*> points;
	TimeCnt timer;

	void Merge(vector<Point*> input, int begin, int mid, int end)
	{
		int i, j, k;
		int n1 = mid - begin + 1;
		int n2 = end - mid;

		vector<Point*> LeftHalf = vector<Point*>(n1);
		vector<Point*> RightHalf = vector<Point*>(n2);

		for (i = 0; i < n1; i++)
		{
			LeftHalf[i]=input[begin+i];
		}

		for (j = 0; j < n2; j++)
		{
			RightHalf[j]=input[mid+1+j];
		}

		i = 0;
		j = 0;
		k = begin;
		while (i < n1 && j < n2)
		{
			if (pointComparator(LeftHalf[i], RightHalf[j], input[0]) < 0)
			{
				input[k] = LeftHalf[i];
				i++;
			}
			else
			{
				input[k] = RightHalf[j];
				j++;
			}
			k++;
		}

		while (i < n1)
		{
			input[k] = LeftHalf[i];
			i++;
			k++;
		}


		while (j < n2)
		{
			input[k] = RightHalf[j];
			j++;
			k++;
		}
	}

	void MergeSort(vector<Point*> input, int l, int r)
	{
		if (l < r)
		{
			int m = l + (r - l) / 2;

			MergeSort(input, l, m);
			MergeSort(input, m + 1, r);

			Merge(input, l, m, r);
		}
	}
	double Compare(Point* X, Point* Y)
	{
		double result = (X->y * Y->x) - (X->x * Y->y);
		return result;
	}
	int pointComparator(Point* point1, Point* point2, Point* point3) {
		double cross_prod = (point1->y - point3->y) * (point1->x - point3->x) - (point2->y - point3->y) * (point2->x - point3->x);
		if (cross_prod < 0.0)
		{
			return -1;
		}
		else
		{
			return 1;
		}
		
	}

	void FindStartingPoint(vector<Point*> input)
	{
		int index = 0;
		for (int i = 1; i < input.size(); i++)
		{
			if (input[i]->y < input[0]->y)
			{
				swap(input[i]->x, input[0]->x);
				swap(input[i]->y, input[0]->y);
				swap(input[i]->index, input[0]->index);
			}
			else {
				if (input[i]->y == input[0]->y)
				{
					if (input[i]->x < input[0]->x)
					{
						swap(input[i]->x, input[0]->x);
						swap(input[i]->y, input[0]->y);
						swap(input[i]->index, input[0]->index);
					}
				}
			}
		}
		for (int i = 0; i < input.size(); i++)
		{
			input[i]->x = input[i]->x - input[0]->x;
			input[i]->y = input[i]->y - input[0]->y;
		}
	}
	
};

int main()
{
	/*for (int i = 1; i < 6; i++)
	{
		if (i == 1)
		{*/
			Points* temp = new Points("points2.txt");
			vector<Point*> result = temp->Convex_Hull();
			cout << "Amount of points in covex hull: " << result.size() << endl;
			for (int j = 0; j < result.size(); j++)
			{
				cout << result[j]->index << endl;
			}
		/*}
		if (i == 2)
		{
			Points* temp = new Points("points2.txt");
			vector<Point*> result = temp->Convex_Hull();
			cout << "Amount of points in covex hull: " << result.size() << endl;
			for (int j = 0; j < result.size(); j++)
			{
				cout << result[j]->index << endl;
			}
		}
		if (i == 3)
		{
			Points* temp = new Points("points3.txt");
			vector<Point*> result = temp->Convex_Hull();
			cout << "Amount of points in covex hull: " << result.size() << endl;
			for (int j = 0; j < result.size(); j++)
			{
				cout << result[j]->index << endl;
			}
		}
		if (i == 4)
		{
			Points* temp = new Points("points4.txt");
			vector<Point*> result = temp->Convex_Hull();
			cout << "Amount of points in covex hull: " << result.size() << endl;
			for (int j = 0; j < result.size(); j++)
			{
				cout << result[j]->index << endl;
			}
		}
		if (i == 5)
		{
			Points* temp = new Points("points5.txt");
			vector<Point*> result = temp->Convex_Hull();
			cout << "Amount of points in covex hull: " << result.size() << endl;
			for (int j = 0; j < result.size(); j++)
			{
				cout << result[j]->index << endl;
			}
		}
	}*/
	return 0;
}


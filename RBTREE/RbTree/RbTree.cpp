#include <iostream>
#include <ctime>
#include <list>

using namespace std;

template<class T>

class Node
{
public:
	T data;
	bool IsRed;
	Node* parent;
	Node* LeftChild;
	Node* RightChild;
	Node(){}
	Node(T input)
	{
		this->data = input;
		this->IsRed = true;
	}
	Node(T input, Node* node)
	{
		this->IsRed = true;
		this->data = input;
		this->parent = node;
	}
	~Node(){}


};

template<class T>

class Tree
{
private:
public:
	Node<T>* root;
	int depth;
	Tree(){}
	~Tree(){}

void Add(T input)
	{
		bool added = false;
		if (this->root == NULL)
		{
			this->root = new Node<T>(input);
			this->root->IsRed = false;
		}
		else
		{
			Node<T>* TempNode = this->root;
			while (added == false)
			{
				if (input < TempNode->data)
				{
					if (TempNode->LeftChild == NULL)
					{
						TempNode->LeftChild = new Node<T>(input, TempNode);
						FixConfilct(TempNode->LeftChild);
						added = true;
					}
					else
					{
						TempNode = TempNode->LeftChild;
					}
				}
				else
				{
					if (TempNode->RightChild == NULL)
					{
						TempNode->RightChild = new Node<T>(input, TempNode);						
						FixConfilct(TempNode->RightChild);
						added = true;
					}
					else
					{
						TempNode = TempNode->RightChild;
					}
				}
			}
		}
	}

void RotateLeft(Node<T>*& pt)
	{
		Node<T>* pt_right = pt->RightChild;

		pt->RightChild = pt_right->LeftChild;

		if (pt->RightChild != NULL)
		{
			pt->RightChild->parent = pt;
		}
		pt_right->parent = pt->parent;

		if (pt->parent == NULL)
		{
			this->root = pt_right;
		}
		else
		{
			if (pt == pt->parent->LeftChild)
			{
				pt->parent->LeftChild = pt_right;
			}				
			else
			{
				pt->parent->RightChild = pt_right;
			}
		}
		pt_right->LeftChild = pt;
		pt->parent = pt_right;
	}

void RotateRight(Node<T>* pt)
	{
		Node<T>* pt_left = pt->LeftChild;

		pt->LeftChild = pt_left->RightChild;

		if (pt->LeftChild != NULL)
			pt->LeftChild->parent = pt;

		pt_left->parent = pt->parent;

		if (pt->parent == NULL)
		{
			this->root = pt_left;
		}
		else
		{
			if (pt == pt->parent->LeftChild)
			{
				pt->parent->LeftChild = pt_left;
			}
			else
			{
				pt->parent->RightChild = pt_left;
			}
		}
		pt_left->RightChild = pt;
		pt->parent = pt_left;
	}

void FixConfilct( Node<T>* pt)
	{
		Node<T>* parent_pt = NULL;
		Node<T>* grand_parent_pt = NULL;
		while ((pt != this->root) && (pt->IsRed == true) && (pt->parent->IsRed == true))
		{
			parent_pt = pt->parent;
			grand_parent_pt = pt->parent->parent;
			if (parent_pt == grand_parent_pt->LeftChild)
			{

				Node<T>* uncle_pt = grand_parent_pt->RightChild;

				if (uncle_pt != NULL && uncle_pt->IsRed == true)
				{
					grand_parent_pt->IsRed = true;
					parent_pt->IsRed = false;
					uncle_pt->IsRed = false;
					pt = grand_parent_pt;
				}

				else
				{
					if (pt == parent_pt->RightChild)
					{
						RotateLeft(parent_pt);
						pt = parent_pt;
						parent_pt = pt->parent;
					}
					RotateRight(grand_parent_pt);
					swap(parent_pt->IsRed, grand_parent_pt->IsRed);
					pt = parent_pt;
				}
			}
			else
			{
				Node<T>* uncle_pt = grand_parent_pt->LeftChild;

				if ((uncle_pt != NULL) && (uncle_pt->IsRed == true))
				{
					grand_parent_pt->IsRed = true;
					parent_pt->IsRed = false;
					uncle_pt->IsRed = false;
					pt = grand_parent_pt;
				}
				else
				{
					if (pt == parent_pt->LeftChild)
					{
						RotateRight(parent_pt);
						pt = parent_pt;
						parent_pt = pt->parent;
					}
					RotateLeft(grand_parent_pt);
					bool temp;
					temp = parent_pt->IsRed;
					parent_pt->IsRed = grand_parent_pt->IsRed;
					grand_parent_pt->IsRed = temp;
					pt = parent_pt;
				}
			}
		}

		this->root->IsRed = false;
	}

void preorder(Node<T>* v)
{
	if (v != NULL)
	{
		if (v != this->root)
		{
			cout << "Data: " << v->data << " Parent data: " << v->parent->data << " Red: " << v->IsRed << endl;
		}
		else
		{
			cout << v->data << " Red: " << v->IsRed << endl;
		}
		preorder(v->LeftChild);     
		preorder(v->RightChild);    
	}
	
}

void inorder(Node<T>* v)
{
	if (v != NULL)
	{
		inorder(v->LeftChild);
		cout << v->data << endl;
		inorder(v->RightChild);     
	}
}

Node<T>* Find(T pattern)
{
	Node<T>* TempNode = this->root;
	bool found = false;
	while (TempNode != NULL)
	{
		if (TempNode->data == pattern)
		{
			found = true;
			break;
		}
		else
		{
			if (TempNode->data < pattern)
			{
				TempNode = TempNode->LeftChild;
			}
			else
			{
				TempNode = TempNode->RightChild;
			}
		}
	}
	if (found == true)
	{
		return TempNode;
	}
	else
	{
		return NULL;
	}
}
int Depth(Node<T>* node)
{
	int dpt=0;
	if (node == NULL)
	{
		dpt = 0;
	}
	else
	{
		int ld = Depth(node->LeftChild);
		int rd = Depth(node->RightChild);
		dpt = (ld < rd) ? rd + 1 : ld + 1;
	}
	return dpt;
}
};

int main()
{
	Tree<int> test;
	srand(time(NULL));
	for (int i = 0; i < 15; i++)
	{
		test.Add(rand());
	}
	test.preorder(test.root);
	int d = test.Depth(test.root);
	cout << d;
	//int it = 1;
	//for (int i = 0; i < 7; i++)
	//{
	//	it *= 10;
	//	clock_t t1 = clock();
	//	for (int j = 0; j < it; j++)
	//	{
	//		test.Add(rand());
	//	}
	//	clock_t t2 = clock();
	//	double t = (double)((t2 - t1)/CLOCKS_PER_SEC);
	//	cout << "Adding time for " << it << " elements: " << t << endl;
	//	int d = test.Depth(test.root);
	//	cout << "Tree depth: " << d << endl;
	//	clock_t t3 = clock();
	//	for (int i = 0; i < 10000; i++)
	//	{
	//		Node<int>* res = test.Find(rand());		
	//	}
	//	clock_t t4 = clock();
	//	double tt = (double)((t4 - t3)/CLOCKS_PER_SEC);
	//	cout << "Search time: " << tt << endl;
	//	//test.preorder(test.root);
	//	test.Depth(test.root);
	//}
	
}

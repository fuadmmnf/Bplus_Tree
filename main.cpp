#include<bits/stdc++.h>

using namespace std;


struct node
{
	int *key;
	node **child;
	bool isLeaf;
	int keyCount;
}

node *root;


node* createNode()
{
	node *tempNode = new node[1];
	tempNode[0].isLeaf = true;
	tempNode[0].keyCount = 0;

	return tempNode;
}




void BTreeSplitChild(node *x, int iter, node *y)
{
	node *tempNode = new node[1];
	tempNode[0].isLeaf = y[0].isLeaf;
	tempNode[0].keyCount = t-1; // Don't know what T is -_-
	tempNode[0].key = new int[t-1];
	tempNode[0].child = new node*[t];

	for(int i=0; i<t-1; i++)
	{
		tempNode[0].key[i] = y[0].key[i+t];
	}

	if(!y[0].isLeaf)
	{
		for(int i=0; i<t; i++)
		{
			tempNode[0].child[i] = y[0].child[i+t];
		}
	}

	y[0].keyCount = t-1;

	for(int i= x[0].keyCount+1 ; i > iter+1; i--)
		x[0].child[i+1] = x[0].child[i];
	x[0].child[iter+1] = tempNode;

	for(int i = x[0].keyCount; i > iter; i--)
		x[0].key[i+1] = x[0].key[i];
	x[0].key[i] = y[0].key[t];

	x[0].keyCount ++;

}







int main()
{

	root = createNode();
}

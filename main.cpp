#include<bits/stdc++.h>

using namespace std;


struct node
{
	int *key;
	node **child;
	bool isLeaf;
	int keyCount;
};

int t;
node *root;


node* createNode()
{
	node *tempNode = new node[1];
	tempNode[0].isLeaf = true;
	tempNode[0].keyCount = 0;
	tempNode[0].key = new int[2*t-1];
	tempNode[0].child = new node*[2*t];
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
	x[0].key[iter] = y[0].key[t];

	x[0].keyCount ++;

}









void BTreeInsertNonFull(node *x, int key)
{
	int n = x[0].keyCount;

	if(x[0].isLeaf)
	{
		while(n>=0  &&  key < x[0].key[n])
		{
			x[0].key[n+1] = x[0].key[n];
			n--;
		}
		x[0].key[n+1] = key;
		x[0].keyCount++;
	}
	else
	{
		while(n>=0  &&  x[0].key[n] > key)
			n--;
		n++;

		if((x[0].child[n])[0].keyCount == 2*t-1)
		{
			BTreeSplitChild(x, n, x[0].child[n]);
			if(key > x[0].key[n])
				n++;
		}
		BTreeInsertNonFull(x[0].child[n], key);
	} 
}






void BTreeInsert(int key)
{
	node *tempRoot = root;

	if(tempRoot[0].keyCount == 2*t-1)
	{
		node *tempNode = createNode();
		root = tempNode;
		tempNode[0].isLeaf = false;
		tempNode[0].child[0] = tempRoot;

		BTreeSplitChild(tempNode, 0, tempRoot);
		BTreeInsertNonFull(tempNode, key);
	}
	else
		BTreeInsertNonFull(tempRoot, key);
}



pair<node*, int> searchKey(node* x, int key)
{
	int i=0;

	while(i < x[0].keyCount  &&  key > x[0].key[i])
		i++;

	if(i < x[0].keyCount  &&  key == x[0].key[i]) 
		return make_pair(x,i);

	if(!x[0].isLeaf)
		searchKey(x[0].child[i],key);

	return make_pair(new node[1],-1);
}



void printTree()
{

}




int main()
{
	int n;
	int temp;

	cout<<"Please enter the value of t: ";
	cin>>t;

	root = createNode();

	cout<<"Enter number of input: ";
	cin>>n;
	printf("\n\n\n\n");
	for(int i=0; i<n; i++)
	{
		cin>>temp;
		BTreeInsert(temp);
		printTree();
		printf("\n\n\n\n");
	}

	return 0;
}

#include<bits/stdc++.h>

using namespace std;


struct node
{
    int pID=-1;
    int nodeID;
	int *key;
	node **child;
	bool isLeaf;
	int keyCount;
};

int t; //Degree
int nodeNumber=0;
stack<node*> nodeQue;
node *root;
pair<node*, int > searchVal;

node* createNode()
{
	node *tempNode = new node[1];
	//nodeQue.push(tempNode);
	tempNode[0].nodeID = nodeNumber++;
	tempNode[0].isLeaf = true;
	tempNode[0].keyCount = 0;
	tempNode[0].key = new int[2*t-1];
	tempNode[0].child = new node*[2*t];
	for(int i=0; i<2*t; i++)
    {
        tempNode[0].child[i] = new node[1];
        (tempNode[0].child[i])[0].keyCount=0;
        (tempNode[0].child[i])[0].nodeID = nodeNumber++;
    }

	return tempNode;
}



void printTree(node *currNode)
{
    cout<<"Node ID: "<<currNode[0].nodeID<<endl<<"Parent ID: "<<currNode[0].pID<<endl;
	for(int i=0; i<currNode[0].keyCount; i++)
		cout<<currNode[0].key[i]<<" ";
    cout<<endl<<endl;
	for(int i=0; i<2*t; i++)
		if((currNode[0].child[i])[0].keyCount)
			printTree(currNode[0].child[i]);
}



void BTreeSplitChild(node *x, int iter, node *y)
{
	node *tempNode = createNode();
	tempNode[0].isLeaf = y[0].isLeaf;
	tempNode[0].keyCount = t-1;

	for(int i=0; i<t-1; i++)
	{
		tempNode[0].key[i] = y[0].key[i+t];
	}

	if(!y[0].isLeaf)
	{


		for(int i=0; i<t; i++)
		{
			tempNode[0].child[i] = y[0].child[i+t];
			(y[0].child[i+t])[0].pID = tempNode[0].nodeID;
			y[0].child[i+t] = createNode();
        }
        y[0].keyCount = t-1;
        for(int i= x[0].keyCount+1 ; i > iter+1; i--)
		{
			x[0].child[i+1] = x[0].child[i];
		}
		x[0].child[iter+1] = tempNode;
	    tempNode[0].pID = x[0].nodeID;

		for(int i = x[0].keyCount+1; i > iter; i--)
			x[0].key[i+1] = x[0].key[i];
		x[0].key[iter] = y[0].key[t-1];

		x[0].keyCount ++;


	}
	else
	{
        y[0].keyCount = t;


        //ekhan porjonto dekhlam

		for(int i= x[0].keyCount+1 ; i > iter+1; i--)
		{
			x[0].child[i+1] = x[0].child[i];
		}
		x[0].child[iter+1] = tempNode;
	    tempNode[0].pID = x[0].nodeID;

		for(int i = x[0].keyCount+1; i > iter; i--)
			x[0].key[i+1] = x[0].key[i];
		x[0].key[iter] = y[0].key[t];

		x[0].keyCount ++;
	}

}









void BTreeInsertNonFull(node *x, int key)
{
	int n = x[0].keyCount-1;

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
			(x[0].child[n])[0].isLeaf = false;
			if(key > x[0].key[n])
				n++;
		}
		BTreeInsertNonFull(x[0].child[n], key);
	}
}






void BTreeInsert(node* currNode, int key)
{
	node *tempRoot = currNode;

		if(tempRoot[0].keyCount == 2*t-1)
		{

                /* if((tempRoot[0].child[2*t-1])[0].keyCount==0)
                {
                */
                    node *tempNode = createNode();
                    //nodeQue.push(tempNode);
                    root = tempNode;
                    tempNode[0].isLeaf = false;
                    tempNode[0].child[0] = tempRoot;
                    tempRoot[0].pID = tempNode[0].nodeID;
                    BTreeSplitChild(tempNode, 0, tempRoot);

                    BTreeInsertNonFull(tempNode, key);
                //}
               /* else if((tempRoot[0].child[2*t-1])[0].keyCount==2*t-1)
                {
                }
                else
                    BTreeInsertNonFull(tempRoot, key);*/
		}
		else
			BTreeInsertNonFull(tempRoot, key);


}



void searchKey(node* x, int key)
{
	int i=0;


	while(i < x[0].keyCount  &&  key > x[0].key[i])
		i++;

	if(!x[0].isLeaf)
		searchKey(x[0].child[i],key);
	else
	{
		if(i < x[0].keyCount  &&  key == x[0].key[i])
		{
			searchVal = make_pair(x,i);
			return;
		}
	}



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
		BTreeInsert(root, temp);

		cout<<endl<<endl;
        printTree(root);
		//searchVal = make_pair(new , -1);
		//searchKey(root, temp);
		//cout<<searchVal.second<<endl;

		//printf("\n\n\n\n");
		cout<<endl<<endl<<endl;
	}

	return 0;
}

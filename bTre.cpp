#include<bits/stdc++.h>
using namespace std;

#define STR_MAX "৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻৻"
#define MAX 50

int numberOfPointers;

struct Block{
    int tNodes;
    Block *parentBlock;
    string value[MAX];
    Block *childBlock[MAX];
    bool isLeaf=true;
    int leafNum;
    Block(){
        tNodes = 0;
        parentBlock = NULL;
        for(int i=0; i<MAX; i++){
            value[i] = STR_MAX;
            childBlock[i] = NULL;
        }
    }
};

Block *rootBlock = new Block();


void splitLeaf(Block *curBlock){
    int x, i, j;

    if(numberOfPointers%2)
        x = (numberOfPointers+1)/2;
    else x = numberOfPointers/2;

    Block *rightBlock = new Block();


    curBlock[0].tNodes = x;

    rightBlock[0].tNodes = numberOfPointers-x;

    rightBlock[0].parentBlock = curBlock->parentBlock;

    for(i=x, j=0; i<numberOfPointers; i++, j++){

        rightBlock[0].value[j] = curBlock[0].value[i];

        curBlock[0].value[i] = STR_MAX;
    }

    string val = rightBlock[0].value[0];


    if(curBlock[0].parentBlock==NULL){

        Block *parentBlock = new Block();

        parentBlock[0].parentBlock = NULL;

        parentBlock[0].tNodes=1;

        parentBlock[0].value[0] = val;

        parentBlock[0].childBlock[0] = curBlock;
        parentBlock[0].childBlock[1] = rightBlock;

        curBlock[0].parentBlock = rightBlock->parentBlock = parentBlock;

        rootBlock = parentBlock;
        return;
    }
    else{

        curBlock = curBlock[0].parentBlock;

        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;

        for(i=0; i<=curBlock[0].tNodes; i++){
            if(val < curBlock[0].value[i]){
                swap(curBlock[0].value[i], val);
            }
        }

        curBlock[0].tNodes++;

        for(i=0; i<curBlock[0].tNodes; i++){
            if(newChildBlock[0].value[0] < curBlock[0].childBlock[i][0].value[0]){
                swap(curBlock[0].childBlock[i], newChildBlock);
            }
        }
        curBlock[0].childBlock[i] = newChildBlock;

        for(i=0;curBlock[0].childBlock[i]!=NULL;i++){
            curBlock[0].childBlock[i][0].parentBlock = curBlock;
        }
    }

}

void splitNonLeaf(Block *curBlock){
    int x, i, j;

    x = numberOfPointers/2;

    Block *rightBlock = new Block();

    curBlock[0].tNodes = x;

    rightBlock[0].tNodes = numberOfPointers-x-1;

    rightBlock[0].parentBlock = curBlock[0].parentBlock;


    for(i=x, j=0; i<=numberOfPointers; i++, j++){

        rightBlock[0].value[j] = curBlock[0].value[i];

        rightBlock[0].childBlock[j] = curBlock[0].childBlock[i];

        curBlock[0].value[i] = STR_MAX;

        if(i!=x)curBlock[0].childBlock[i] = NULL;
    }


    string val = rightBlock[0].value[0];

    for(int k=0; k<(rightBlock[0].tNodes+1); k++)
        rightBlock[0].value[k] = rightBlock[0].value[k+1];
    memcpy(&rightBlock[0].childBlock, &rightBlock[0].childBlock[1], sizeof(rootBlock)*(rightBlock[0].tNodes+1));


    for(i=0;curBlock[0].childBlock[i]!=NULL;i++){
        curBlock[0].childBlock[i][0].parentBlock = curBlock;
    }
    for(i=0;rightBlock[0].childBlock[i]!=NULL;i++){
        rightBlock[0].childBlock[i][0].parentBlock = rightBlock;
    }


    if(curBlock[0].parentBlock==NULL){

        Block *parentBlock = new Block();

        parentBlock[0].parentBlock = NULL;

        parentBlock[0].tNodes=1;

        parentBlock[0].value[0] = val;

        parentBlock[0].childBlock[0] = curBlock;
        parentBlock[0].childBlock[1] = rightBlock;


        curBlock[0].parentBlock = rightBlock[0].parentBlock = parentBlock;


        rootBlock = parentBlock;
        return;
    }
    else{
        curBlock = curBlock[0].parentBlock;



        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;




        for(i=0; i<=curBlock[0].tNodes; i++){
            if(val < curBlock[0].value[i]){
                swap(curBlock[0].value[i], val);
            }
        }

        curBlock[0].tNodes++;


        for(i=0; i<curBlock[0].tNodes; i++){
            if(newChildBlock[0].value[0] < curBlock[0].childBlock[i][0].value[0]){
                swap(curBlock[0].childBlock[i], newChildBlock);
            }
        }
        curBlock[0].childBlock[i] = newChildBlock;

         for(i=0;curBlock[0].childBlock[i]!=NULL;i++){
            curBlock[0].childBlock[i][0].parentBlock = curBlock;
        }
    }

}

void insertNode(Block *curBlock, string val){


    for(int i=0; i<=curBlock[0].tNodes; i++){
        if(val < curBlock[0].value[i] && curBlock[0].childBlock[i]!=NULL){
            insertNode(curBlock[0].childBlock[i], val);
            if(curBlock[0].tNodes==numberOfPointers)
                splitNonLeaf(curBlock);
            return;
        }
        else if(val < curBlock[0].value[i] && curBlock[0].childBlock[i]==NULL){
            swap(curBlock[0].value[i], val);
            if(i==curBlock[0].tNodes){
                    curBlock[0].tNodes++;
                    break;
            }
        }
    }

    if(curBlock[0].tNodes==numberOfPointers){

            splitLeaf(curBlock);
    }
}


void print(vector < Block* > Blocks){
    vector < Block* > newBlocks;
    for(int i=0; i<Blocks.size(); i++){ //for every block
        Block *curBlock = Blocks[i];

        cout <<"[|  ";
        int j;
        for(j=0; j<curBlock->tNodes; j++){  //traverse the childBlocks, print values and save all the childBlocks
            cout << curBlock->value[j] << "  |  ";
            if(curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);
        }
        if(curBlock->value[j]==STR_MAX && curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);

        cout << "  ]  ";
    }

    if(newBlocks.size()==0){ //if there is no childBlock block left to send out then just the end of the recursion

        puts("");
        puts("");
        Blocks.clear();
        //exit(0);
    }
    else {                    //else send the childBlocks to the recursion to continue to the more depth
        puts("");
        puts("");
        Blocks.clear();
        print(newBlocks);
    }
}

bool keyfound ;
int leafCount; 


void numLeaf(Block *x){


	for(int i=0;i<=x[0].tNodes;i++){
	
    	if(x[0].childBlock[i]!=NULL)
    		x[0].isLeaf=false;
    }
    	
    
    if(x[0].isLeaf)
    	x[0].leafNum=++leafCount;
    
    else{
    	for(int i=0; i<=x[0].tNodes; i++){
            
            if( x[0].childBlock[i]!=NULL)
            {
            
               	 numLeaf(x[0].childBlock[i]);
               	 
            }
	
	
	 	}
    }
    
     

}


int lIn;

void searchKey(Block *x, string key)
{
    if(x==rootBlock ) keyfound = false;

    if(!keyfound)
    {
    	
        for(int i=0; i<=x->tNodes; i++)
        {
            if(x[0].isLeaf && x[0].value[i] == key)
            {
                keyfound = true;
                lIn=x[0].leafNum;
                return;
            }
            if(key < x[0].value[i] && x[0].childBlock[i]!=NULL)
            {
                searchKey(x[0].childBlock[i], key);

                return;
            }
        }
    }
    return;
}



int main(){

    //freopen("output.txt","w",stdout);

    const char* fileName = "input.txt";

    vector<string> input;

    vector<Block*> Blocks;
    ifstream myfile(fileName, ios::binary);

    fprintf(stderr,"Pointers: ");
    cin>>numberOfPointers;

    int ch;
    int i = 0;
    int totalValues = 0;
    //input from file
    string str;

    if(myfile.is_open())
    {
        while(myfile >> str)
        {
            insertNode(rootBlock, str);

            totalValues++;
        }

       // Blocks.clear();
       // Blocks.push_back(rootBlock);
       // print(Blocks);
       // puts("");
       // myfile.close();
    }
	
	leafCount=0;
	numLeaf(rootBlock);
	
	
    cout<<"Enter the word you want to search :"<<endl;
	
    string key;
    
    while(cin>>key){
    	
    	lIn=-1;
    	
    	searchKey(rootBlock,key);

    	if(keyfound){
    	
    		cout<<"Found and Leaf No :"<< lIn <<endl;
    	}
       		 	
   		else
        	cout<<"Not Found"<<endl;
    
    }
    

    

    return 0;
}

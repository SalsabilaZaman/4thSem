#include<iostream>
#include<fstream>
#include <cmath>
#include <cctype>
using namespace std;

int numOfpointers,numOfkeys;

struct node {
	int totalKeys;
	string *words,*meanings;
	node *parent,*next,**child;
	bool isLeaf;
};
node *root;

node* createNewNode(){
	node *newNode= new node;
	newNode->totalKeys=0;
	newNode->parent=NULL;
	newNode->next=NULL;
	newNode->child = new node *[numOfpointers+1];
    	
    	for (int i=0; i<=numOfpointers; i++)
        	newNode->child[i] = nullptr;
    	
    	newNode->isLeaf = true;
    	newNode->words = new string[numOfkeys+1];
    	newNode->meanings = new string[numOfkeys+1];
	return newNode;
}
void createNewRoot(node *newRoot,string value, node *left,node *right){
	newRoot=createNewNode();
	
	newRoot->totalKeys=1;
	newRoot->parent=NULL;
	newRoot->words[0]=value;
	newRoot->child[0]=left;
	newRoot->child[1]=right;
	newRoot->isLeaf=false;
	left->parent=newRoot;
	right->parent=newRoot;
	root=newRoot;
	//return newRoot;
}


node *search(node *node, string word){
    while(!node->isLeaf){
        int i;
        for(i=0; i<node->totalKeys; i++){
            if(word < node->words[i]){
                break;
            }
        }
        node = node->child[i];
    }
    //cout <<"found smtg"<<endl;
    return node;
}
void addToParent(node *parentN,node *right,string value){
	int i,j;
	for(i=0;i<parentN->totalKeys;i++)
		if(value<(parentN->words[i]))
			break;
	for(j=parentN->totalKeys;j>i;j--){
		parentN->words[j]=parentN->words[j-1];
		parentN->child[j+1]=parentN->child[j];
	}
	parentN->words[i]=value;
	parentN->child[i+1]=right;
	parentN->totalKeys++;
}
void shiftUp(node *parentN,node *left,node *right,string value){
	if(!parentN){
		createNewRoot(parentN,value,left,right);
		return;
	}
	int i;
	right->parent=parentN;
	addToParent(parentN,right,value);
	if((parentN->totalKeys) > numOfkeys){
		node *newNode=createNewNode();
		newNode->isLeaf=false;		
		
		int splitIndex=ceil((parentN->totalKeys)/2);
		newNode->totalKeys=(parentN->totalKeys)-splitIndex-1;		
		parentN->totalKeys=splitIndex;
		
		for(i=0;i<newNode->totalKeys;i++){
			newNode->words[i]=parentN->words[splitIndex+i+1];
			if(i==0){
				newNode->child[i]=parentN->child[splitIndex+1];
				newNode->child[i]->parent=newNode;
				newNode->child[i+1]=parentN->child[splitIndex+2];
				newNode->child[i+1]->parent=newNode;
			}
			else{
				newNode->child[i+1]=parentN->child[splitIndex+1+i+1];
				newNode->child[i+1]->parent=newNode;
			}		
		
		}
		shiftUp(parentN->parent,parentN,newNode,parentN->words[splitIndex]);
	}

}
void insert(string word,string meaning){
	int i,j;
    	node *leaf = search(root, word);
	i=leaf->totalKeys;
	if(leaf->totalKeys >0){
		for(i=0;i<leaf->totalKeys;i++)
			if(word<(leaf->words[i]))
				break;
		for(j=(leaf->totalKeys);j>i;j--){
			leaf->words[j]=leaf->words[j-1];
			leaf->meanings[j]=leaf->meanings[j-1];
		}
		
	}
	leaf->words[i]=word;
	leaf->meanings[i]=meaning;
	leaf->totalKeys++;
	if((leaf->totalKeys)>numOfkeys){
		int splitIndex=ceil((leaf->totalKeys)/2);
		node *newNode=createNewNode();
		newNode->totalKeys=(leaf->totalKeys)-splitIndex;		
		leaf->totalKeys=splitIndex;
		for(i=0;i<newNode->totalKeys;i++){
			newNode->words[i]=leaf->words[splitIndex+i];
			newNode->meanings[i]=leaf->meanings[splitIndex+i];
		}
		newNode->next = leaf->next;
        	leaf->next = newNode;
		shiftUp(leaf->parent,leaf,newNode,newNode->words[0]);
	}

}
void createTree(){
	string word, meaning;
	root = createNewNode();

    	ifstream file;
    	file.open("dictionary.txt");
	while(file >> word){
            getline(file, meaning);
            insert(word, meaning);
            //cout << "yesyes";
        }
        file.close();
}
void searchMeaning(){

    while(true){
        int i;
        cout << "Enter a word: " ;
        string word;
        cin >> word;
        for(int j=0; j<word.size(); j++)
            word[j] = tolower(word[j]);
      
        node *leaf = search(root, word);
        for(i=0; i<leaf->totalKeys; i++){
            //cout <<leaf->words[i]<<endl;
            if(leaf->words[i] == word) 
            	break;
        }
       
        if(i == leaf->totalKeys) 
        	cout << "No word found" ;
        else
            cout <<  word << "=" << leaf->meanings[i];
        
    	cout <<endl<<endl;
    }
}
int main(){

	cout <<"Enter number of pointers:";
	cin >>numOfpointers;
	numOfkeys=numOfpointers+1;
	createTree();
	searchMeaning();
	return 0;
}

	

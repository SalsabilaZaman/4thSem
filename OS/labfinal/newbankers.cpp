#include<iostream>
using namespace std;

bool allFinished(bool finished[],int p){
	for(int i=0;i<p;i++)
		if(finished[i]==false)
			return false;
	return true;
}
int main(){
	int p,r,idx=0,first;
	cout <<"How many process:";
	cin  >> p;
	cout <<"How many resource:";
	cin  >> r;
	int allocation[p][r],max[p][r],need[p][r],work[r];
	bool finished[p],Safe=true;;
	int safeSequence[p];
	
	for(int i=0;i<p;i++)
		finished[i]=false;
	cout <<"Allocation Matrix="<<endl;	
	for(int i=0;i<p;i++)
	    for(int j=0;j<r;j++)
	    	cin >> allocation[i][j];
	cout <<"Max Matrix="<<endl;    	
	for(int i=0;i<p;i++)
	    for(int j=0;j<r;j++)
	    	cin >> max[i][j];
	cout <<"Available Resouces="<<endl;    	
	for(int i=0;i<r;i++)
		cin >> work[i];   	
	
	cout << "Which process first-";
	cin >> first;
	
	for(int i=0;i<p;i++)
	    for(int j=0;j<r;j++)
	    	need[i][j]=max[i][j]-allocation[i][j];    
	bool flag=true;
	for(int j=0;j<r;j++)
	   if(need[first][j]>work[j]){
		  flag=false;
		  Safe=false;
		  break;
 	   }
	if(flag){
		safeSequence[idx++]=first;
		finished[first]=true;
		for(int j=0;j<r;j++)
		    work[j]+=allocation[first][j];    		    	
	}
	int loop=0;
	while(!allFinished(finished,p)){
		if(loop>p){
		   Safe=false;
		   break;
		}   
		for(int i=0;i<p;i++)
		   if(finished[i]==false){
		   	flag=true;
		   	for(int j=0;j<r;j++)
		   	   if(need[i][j]>work[j]){
		   		flag=false;
		   		break;
		   	   }
		   	if(flag){
		   	   safeSequence[idx++]=i;
		   	   finished[i]=true;
		   	   for(int j=0;j<r;j++)
		   	   	work[j]+=allocation[i][j];
		   	}   	
		   		
		   }
		loop++;  	
	}
	if(Safe){
		cout <<"Safe sequence= ";
		for(int i=0;i<p;i++){
		   cout << "P"<<safeSequence[i];
			if(i!=p-1)
				cout <<"-->";
		}
	}
	else
		cout <<"No safe sequence is found!"<<endl;
	return 0;
}

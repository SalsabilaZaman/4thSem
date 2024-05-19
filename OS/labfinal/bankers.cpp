#include<iostream>
using namespace std;

bool allFinished(bool finished[],int p){
	for(int i=0;i<p;i++)
		if(finished[i]==false)
			return false;
	return true;
}
/*5 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
3 3 2*/
int main(){
	int p,r,idx=0;
	cout <<"How many process:";
	cin  >> p;
	cout <<"How many resource:";
	cin  >> r;
	int allocation[p][r],max[p][r],need[p][r],work[r];
	bool finished[p],Safe=true;;
	int safeSequence[p];
	
	for(int i=0;i<p;i++)
		finished[i]=false;
		
	for(int i=0;i<p;i++)
	    for(int j=0;j<r;j++)
	    	cin >> allocation[i][j];
	    	
	for(int i=0;i<p;i++)
	    for(int j=0;j<r;j++)
	    	cin >> max[i][j];
	    	
	for(int i=0;i<r;i++)
		cin >> work[i];   	
	
	for(int i=0;i<p;i++)
	    for(int j=0;j<r;j++)
	    	need[i][j]=max[i][j]-allocation[i][j];    	    	
	int loop=0;
	while(!allFinished(finished,p)){
		if(loop>p){
		   Safe=false;
		   break;
		}   
		for(int i=0;i<p;i++)
		   if(finished[i]==false){
		   	bool flag=true;
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
	return 0;
}

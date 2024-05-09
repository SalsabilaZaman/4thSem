#include <bits/stdc++.h>
using namespace std;

int num;

struct process{
	string name;
	double arrival_time;
	double burst_time;
	double remaining_time;
	double waiting_time;
	double turnaround_time;
	int priority;
	bool isCompleted;
};

int main(){
	freopen("data.txt","r",stdin);
	cin >> num;
	struct process P[num],temp;	
	for(int i=0;i<num;i++){
		cin >>P[i].name>> P[i].burst_time >>P[i].priority >>P[i].arrival_time;
		P[i].remaining_time=P[i].burst_time;
		P[i].isCompleted=false;
	}
	for(int i=0;i<num;i++)					//sort according arrival time
	    for(int j=0;j<num-i-1;j++)
		if(P[j].arrival_time > P[j+1].arrival_time){
			temp=P[j];
			P[j]=P[j+1];
			P[j+1]=temp;
		}
	
	int complete=0,max=INT_MIN;
	int time=0,running=0,prev=-1;
	bool flag=false;
	cout << "Gantt Chart for Preemptive Priority:"<<endl;
	while(complete!=num){
		for(int i=0;i<num;i++)
		   if(!P[i].isCompleted)
		      if(P[i].arrival_time <= time && P[i].priority >max){
		    	max=P[i].priority;
		    	running=i;
		    	flag=true;  
		      }
		if (flag == false) {
			time++;
			continue;
		}
		
		if(prev!=running){
		    if(P[prev].isCompleted==false)
		       cout << time << " | ";
		   
		    cout << P[running].name << " "<<time <<"-"; 
		    prev=running;
		}
		
		time++;
		P[running].remaining_time--;
	
		
		   
		
		if(P[running].remaining_time==0){
			complete++;
			P[running].isCompleted=true;
			flag=false;
			P[running].turnaround_time=time-P[running].arrival_time;
			P[running].waiting_time=P[running].turnaround_time-P[running].burst_time;
			cout << time << " | ";
			max=INT_MIN;
		}   	  	
	}
	double totalWaiting=0,totalTurnAround=0;
	cout <<endl;
	for(int i=0;i<num;i++){
		cout << P[i].name << " "<< P[i].turnaround_time <<" "<<P[i].waiting_time <<endl;
		totalWaiting+=P[i].waiting_time;
		totalTurnAround+=P[i].turnaround_time;
	}
	cout << "Average Turnaround Time="<<(double)totalTurnAround/num<<endl;
	cout << "Average Waiting Time="<<(double)totalWaiting/num<<endl;
			
}	

#include<iostream>
#include<vector>
using namespace std;
int num;

struct process{
	string name;
	double arrival_time;
	double burst_time;
	double remaining_time;
	double waiting_time;
	double turnaround_time;
	bool is_completed;
	int priority;
};

int main(){
	freopen("data.txt","r",stdin);
	cin >> num;
	struct process P[num],temp;	
	for(int i=0;i<num;i++){
		cin >>P[i].name>> P[i].burst_time >>P[i].priority >>P[i].arrival_time;
		P[i].is_completed=false;
	}
	for(int i=0;i<num;i++)
	    for(int j=0;j<num-i-1;j++)
		if(P[j].arrival_time > P[j+1].arrival_time){
			temp=P[j];
			P[j]=P[j+1];
			P[j+1]=temp;
		}
	vector<process> ready;
	int time,running;
	for(int i=0;i<num;i++){
		if(P[i].is_completed==false){
		   ready.push_back(P[i]);
		   time=P[i].arrival_time;
		   running=i;
			while(!ready.empty()){
				for(int j=i+1;j<num;j++){
					//for(auto k=0;k<ready.size();k++)
					//	cout<< ready[k].name<<" ";
					//cout <<endl;	
					if(P[j].arrival_time < P[running].burst_time+time && P[j].is_completed==false){
						if(P[j].burst_time<(P[running].burst_time-(P[j].arrival_time-time))){
							P[running].remaining_time=P[running].burst_time-(P[j].arrival_time-time);
							running=j;
						}
						ready.push_back(P[j]);
							
					}
					else{
						time+=P[running].burst_time;
						P[running].is_completed=true;
						cout << P[running].name <<" "<< ready[0].name<<endl;
						ready.erase(ready.begin());
					}
				}	
					
			}
		
		}
	
	}
	
	
	
	
	for(int i=0;i<num;i++)
		cout <<P[i].name<<" "<<P[i].burst_time <<" "<<P[i].priority <<" "<<P[i].arrival_time<<endl;	 

	return 0;
}

	/*for(int i=0;i<num;i++)
		ready.push_back(P[i]);
	
	int running=0;
	int start,end,time=ready[0].arrival_time;
	start=time;
				
	while(!ready.empty()){
		bool flag=true;
		
		for(int i=1;i<ready.size();i++){
			time=ready[i].arrival_time;
			ready[running].remaining_time=ready[running].burst_time-(time-start);
			if(ready[i].burst_time < ready[running].remaining_time){
				running=i;
				flag=false;
				break;
			}
		}
		if(flag){
			ready[running].remaining_time=0;
			ready.erase(running)
		}
			
	}*/


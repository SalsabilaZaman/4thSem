#include<iostream>
#include<cstring>
#include <vector>
using namespace std;
#define MAX 100
int n;
string name[MAX];
double timetable[MAX][5];


void input(){
	freopen("data.txt","r",stdin);
	cin >> n;
	for(int i=0;i<n;i++)
		cin >> name[i]>> timetable[i][0]>> timetable[i][1]>> timetable[i][2];
	
	/*cout <<"Enter how many process-";
	  cin >> n;
	for(int i=0;i<n;i++){
		cout << "Enter process name-";
		cin >> name[i];
		cout << "Burst time for "<<name[i]<<"-";
		cin >> timetable[i][0];
		cout << "Priority for "<<name[i]<<"-";
		cin >> timetable[i][1];
		cout << "Arrival time for "<<name[i]<<"-";
		cin >> timetable[i][2];
	}*/
}

void show(){
	for(int i=0;i<n;i++)
		cout << name[i]<<" "<<timetable[i][0]<<" "<<timetable[i][1]<<" "<<timetable[i][2]<<endl;

}
void swap(int i,int j){
	string temp=name[i];
	name[i]=name[j];
	name[j]=temp;
	
	int temp1=timetable[i][0];
	timetable[i][0]=timetable[j][0];
	timetable[j][0]=temp1;
	
	temp1=timetable[i][1];
	timetable[i][1]=timetable[j][1];
	timetable[j][1]=temp1;
	
	temp1=timetable[i][2];
	timetable[i][2]=timetable[j][2];
	timetable[j][2]=temp1;
}

void sort(string condition){
	if(condition[0]=='A'){
		for(int i=0;i<n;i++)
		  for(int j=0;j<n-i-1;j++)
		  	if(timetable[j][2]>timetable[j+1][2])
		  		swap(j,j+1);
	}
	else if(condition[0]=='B'){
		for(int i=0;i<n;i++)
		  for(int j=0;j<n-i-1;j++)
		  	if(timetable[j][0]>timetable[j+1][0])
		  		swap(j,j+1);	  	
	
	}
	else if(condition[0]=='P'){
		for(int i=0;i<n;i++)
		  for(int j=0;j<n-i-1;j++)
		  	if(timetable[j][1]<timetable[j+1][1] && timetable[j][2]==timetable[j+1][2])
		  		swap(j,j+1);	  	
	
	}
	
} 
void fcfs(){
		int time=0;
		sort("ArrivalTime");
		cout <<"Gantt Chart for FCFS Algorithm="<<endl;
		
		for(int i=0;i<n;i++){
			cout << name[i] <<"	";
			cout << time <<"-";
			time+=timetable[i][0];
			timetable[i][3]=time-timetable[i][2];
			cout <<time <<endl;	
		}
		
		cout <<endl;	
		cout <<"Turnaround Time-"<<endl;
		for(int i=0;i<n;i++)
			cout << name[i]<<"     "<<timetable[i][3]<<endl;
		cout <<"Waiting Time-"<<endl;
		for(int i=0;i<n;i++){
			timetable[i][4]=timetable[i][3]-timetable[i][0];
			cout << name[i]<<"     "<<timetable[i][4]<<endl;	
		}
		int avgT=0,avgW=0;
		for(int i=0;i<n;i++){
			avgT+=timetable[i][3];
			avgW+=timetable[i][4];
		}
		
		
		cout <<"Average Turnaround Time-"<<(double)avgT/n<<endl;
		cout <<"Average Waiting Time-"<<(double)avgW/n<<endl;	

}

void sjf(){
	/*
	int completed = 0;
	int time=0;
	sort("ArrivalTime");
	timetable[0][3]=timetable[0][0]-timetable[0][2];
	time+=timetable[0][3];
	
	bool is_completed[n];
	is_completed[0]=true;
	for(int i = 1; i < n; i++)
	    is_completed[i]=false;	
       
       while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        for(int i = 1; i < n; i++) {
            if(timetable[i][2] <= time && is_completed[i] == false) {
                if(timetable[i][0] < mn) {
                    mn = timetable[i][0];
                    idx = i;
                }
                if(timetable[i][0] == mn) {
                    if(timetable[i][2] < timetable[idx][2]) {
                        mn = timetable[i][0];
                        idx = i;
                    }
                }
            }
        }
	if(idx != -1) {
            p[idx].start_time =time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else 
           time++;
     }

		for(int i=1;i<n;i++)
		    if(timetable[i][2]<time)
		    	sortedWork.push_back(i);
		    	
		  for(int j=0;j<n-i-1;j++)
		  	if(timetable[j][0]> (timetable[j+1][2]-timetable[j][2]))
		  		swap(j,j+1);	  	
	
	*/	int time=0;
		sort("BurstTime");
		
		cout <<"Gantt Chart for SJF Algorithm="<<endl;
		for(int i=0;i<n;i++){
			cout << name[i] <<"	";
			cout << time <<"-";
			time+=timetable[i][0];
			timetable[i][3]=time-timetable[i][2];
			cout <<time <<endl;	
		}
		
		cout <<endl;	
		cout <<"Turnaround Time-"<<endl;
		for(int i=0;i<n;i++)
			cout << name[i]<<"     "<<timetable[i][3]<<endl;
		cout <<"Waiting Time-"<<endl;
		for(int i=0;i<n;i++){
			timetable[i][4]=timetable[i][3]-timetable[i][0];
			cout << name[i]<<"     "<<timetable[i][4]<<endl;	
		}
		int avgT=0,avgW=0;
		for(int i=0;i<n;i++){
			avgT+=timetable[i][3];
			avgW+=timetable[i][4];
		}
		
		
		cout <<"Average Turnaround Time-"<<(double)avgT/n<<endl;
		cout <<"Average Waiting Time-"<<(double)avgW/n<<endl;	

}
void priority(){
		int time=0;
		sort("Priority");
		cout <<"Gantt Chart for Non-preemptive priority Algorithm="<<endl;
		
		for(int i=0;i<n;i++){
			cout << name[i] <<"	";
			cout << time <<"-";
			time+=timetable[i][0];
			timetable[i][3]=time-timetable[i][2];
			cout <<time <<endl;	
		}
		
		cout <<endl;	
		cout <<"Turnaround Time-"<<endl;
		for(int i=0;i<n;i++)
			cout << name[i]<<"     "<<timetable[i][3]<<endl;
		cout <<"Waiting Time-"<<endl;
		for(int i=0;i<n;i++){
			timetable[i][4]=timetable[i][3]-timetable[i][0];
			cout << name[i]<<"     "<<timetable[i][4]<<endl;	
		}
		int avgT=0,avgW=0;
		for(int i=0;i<n;i++){
			avgT+=timetable[i][3];
			avgW+=timetable[i][4];
		}
		
		
		cout <<"Average Turnaround Time-"<<(double)avgT/n<<endl;
		cout <<"Average Waiting Time-"<<(double)avgW/n<<endl;	

}
void roundRobin(){
		
		sort("ArrivalTime");
		int time=timetable[0][2];
		cout <<"Gantt Chart for Round Robin Algorithm="<<endl;
		int quantum=2;
		int completed = 0;
	
	bool is_completed[n];
	for(int i = 0; i < n; i++)
	    is_completed[i]=false;	
       
       while(completed != n) {
        for(int i = 0; i < n; i++)
           if(is_completed[i] == false){
            if(timetable[i][0]<=quantum){
           		is_completed[i] = true;
           		time+=timetable[i][0];
           		timetable[i][3]=time-timetable[i][2];			
	    		completed++;
	    }
	    else{
	    	time+=quantum;
	    	timetable[i][0]-=quantum;
	    }	           
           } 
      }     
		cout <<"Turnaround Time-"<<endl;
		for(int i=0;i<n;i++)
			cout << name[i]<<"     "<<timetable[i][3]<<endl;
		cout <<"Waiting Time-"<<endl;
		for(int i=0;i<n;i++){
			timetable[i][4]=timetable[i][3]-timetable[i][0];
			cout << name[i]<<"     "<<timetable[i][4]<<endl;	
		}
		int avgT=0,avgW=0;
		for(int i=0;i<n;i++){
			avgT+=timetable[i][3];
			avgW+=timetable[i][4];
		}
		
		
		cout <<"Average Turnaround Time-"<<(double)avgT/n<<endl;
		cout <<"Average Waiting Time-"<<(double)avgW/n<<endl;	

}
int main(){
	input();
	fcfs();
	sjf();
	priority();
	roundRobin();
	//show();
	return 0;
}

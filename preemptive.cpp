#include<stdio.h>
 // structure representing a structure
struct priority_scheduling {

  // name of the process
  char process_name;

  // time required for execution
  int burst_time;

  // waiting time of a process
  int waiting_time;

  // total time of execution
  int turn_around_time;

  // priority of the process
  int priority;
};

int main() {

  // total number of processes
  int number_of_process;

  // total waiting and turnaround time
  int total = 0;

  // temporary structure for swapping
  struct priority_scheduling temp_process;

  // ASCII numbers are used to represent the name of the process
  int ASCII_number = 65;

  // swapping position
  int position;

  // average waiting time of the process
  float average_waiting_time;

  // average turnaround time of the process
  float average_turnaround_time;

  printf("Enter the total number of Processes: ");
  // get the total number of the process as input
  scanf("%d", & number_of_process);

  // initializing the structure array
  struct priority_scheduling process[number_of_process];

  printf("\nPlease Enter the  Burst Time and Priority of each process:\n");

  // get burst time and priority of all process
  for (int i = 0; i < number_of_process; i++) {

    // assign names consecutively using ASCII number
    process[i].process_name = (char) ASCII_number;

    printf("\nEnter the details of the process %c \n", process[i].process_name);
    printf("Enter the burst time: ");
    scanf("%d", & process[i].burst_time);

    printf("Enter the priority: ");
    scanf("%d", & process[i].priority);

    // increment the ASCII number to get the next alphabet
    ASCII_number++;

  }

  // swap process according to high priority
  for (int i = 0; i < number_of_process; i++) {

    position = i;

    for (int j = i + 1; j < number_of_process; j++) {

      // check if priority is higher for swapping
      if (process[j].priority > process[position].priority)
        position = j;
    }
    // swapping of lower priority process with the higher priority process 
    temp_process = process[i];
    process[i] = process[position];
    process[position] = temp_process;
  }
  // First process will not have to wait and hence has a waiting time of 0
  process[0].waiting_time = 0;

  for (int i = 1; i < number_of_process; i++) {
    process[i].waiting_time = 0;
    for (int j = 0; j < i; j++) {
      // calculate waiting time
      process[i].waiting_time += process[j].burst_time;
    }

    // calculate total waiting time             
    total += process[i].waiting_time;
  }

  // calculate average waiting time
  average_waiting_time = (float) total / (float) number_of_process;

  // assigning total as 0 for next calculations
  total = 0;

  printf("\n\nProcess_name \t Burst Time \t Waiting Time \t  Turnaround Time\n");
  printf("------------------------------------------------------------\n");

  for (int i = 0; i < number_of_process; i++) {

    // calculating the turnaround time of the processes
    process[i].turn_around_time = process[i].burst_time + process[i].waiting_time;

    // calculating the total turnaround time.
    total += process[i].turn_around_time;

    // printing all the values
    printf("\t  %c \t\t  %d \t\t %d \t\t %d", process[i].process_name, process[i].burst_time, process[i].waiting_time, process[i].turn_around_time);
    printf("\n-----------------------------------------------------------\n");
  }

  // calculating the average turn_around time 
  average_turnaround_time = (float) total / (float) number_of_process;

  // average waiting time
  printf("\n\n Average Waiting Time : %f", average_waiting_time);

  // average turnaround time
  printf("\n Average Turnaround Time: %f\n", average_turnaround_time);

  return 0;
}











#include<stdio.h>
#define MIN -9999;
struct proc
{
    int no,at,bt,rt,ct,wt,tat,pri,temp;
};
struct proc read(int i)
{
    struct proc p;
    printf("\nProcess No: %d\n",i);
    p.no=i;
    printf("Enter Arrival Time: ");
    scanf("%d",&p.at);
    printf("Enter Burst Time: ");
    scanf("%d",&p.bt);
    p.rt=p.bt;
    printf("Enter Priority: ");
    scanf("%d",&p.pri);
    p.temp=p.pri;
    return p;
}
void main()
{
    int i,n,c,remaining,max_val,max_index;
    struct proc p[10],temp;
    float avgtat=0,avgwt=0;
    printf("<--Highest Priority First Scheduling Algorithm (Preemptive)-->\n");
    printf("Enter Number of Processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        p[i]=read(i+1);
    remaining=n;
	for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)    
            if(p[j].at>p[j+1].at)
            {
            temp=p[j];
            p[j]=p[j+1];
            p[j+1]=temp;
            }
    max_val=p[0].temp,max_index=0;
	for(int j=0;j<n&&p[j].at<=p[0].at;j++)
		if(p[j].temp>max_val)
			max_val=p[j].temp,max_index=j;
	i=max_index;
	c=p[i].ct=p[i].at+1;
	p[i].rt--;
	if(p[i].rt==0)
	{
		p[i].temp=MIN;
		remaining--;
	}
	while(remaining>0)
	{
		max_val=p[0].temp,max_index=0;
    	for(int j=0;j<n&&p[j].at<=c;j++)
    		if(p[j].temp>max_val)
    			max_val=p[j].temp,max_index=j;
    	i=max_index;
		p[i].ct=c=c+1;
		p[i].rt--;
		if(p[i].rt==0)
		{
		    p[i].temp=MIN;
		    remaining--;
		}
	}
	printf("\nProcessNo\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        avgtat+=p[i].tat;
        p[i].wt=p[i].tat-p[i].bt;
        avgwt+=p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].no,p[i].at,p[i].bt,p[i].pri,p[i].ct,p[i].tat,p[i].wt);
    }
    avgtat/=n,avgwt/=n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f",avgtat,avgwt);
}










#include<stdio.h>
struct process
{
    int WT,AT,BT,TAT,PT;
};

struct process a[10];

int main()
{
    int n,temp[10],t,count=0,short_p;
    float total_WT=0,total_TAT=0,Avg_WT,Avg_TAT;
    printf("Enter the number of the process\n");
    scanf("%d",&n);
    printf("Enter the arrival time , burst time and priority of the process\n");
    printf("AT BT PT\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d",&a[i].AT,&a[i].BT,&a[i].PT);
        
        // copying the burst time in
        // a temp array fot futher use
        temp[i]=a[i].BT;
    }
    
    // we initialize the burst time
    // of a process with maximum 
    a[9].PT=10000;
    
    for(t=0;count!=n;t++)
    {
        short_p=9;
        for(int i=0;i<n;i++)
        {
            if(a[short_p].PT>a[i].PT && a[i].AT<=t && a[i].BT>0)
            {
                short_p=i;
            }
        }
        
        a[short_p].BT=a[short_p].BT-1;
        
        // if any process is completed
        if(a[short_p].BT==0)
        {
            // one process is completed
            // so count increases by 1
            count++;
            a[short_p].WT=t+1-a[short_p].AT-temp[short_p];
            a[short_p].TAT=t+1-a[short_p].AT;
            
            // total calculation
            total_WT=total_WT+a[short_p].WT;
            total_TAT=total_TAT+a[short_p].TAT;
            
        }
    }
    
    Avg_WT=total_WT/n;
    Avg_TAT=total_TAT/n;
    
    // printing of the answer
    printf("ID WT TAT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d %d\t%d\n",i+1,a[i].WT,a[i].TAT);
    }
    
    printf("Avg waiting time of the process  is %f\n",Avg_WT);
    printf("Avg turn around time of the process is %f\n",Avg_TAT);
    
    return 0;
}













#include <stdio.h>
  
int main() 
{
      int arrival_time[10], burst_time[10], temp[10];
      int i, smallest, count = 0, time, limit;
      double wait_time = 0, turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
      printf("nEnter the Total Number of Processes:t");
      scanf("%d", &limit); 
      printf("nEnter Details of %d Processesn", limit);
      for(i = 0; i < limit; i++)
      {
            printf("nEnter Arrival Time:t");
            scanf("%d", &arrival_time[i]);
            printf("Enter Burst Time:t");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
      }
      burst_time[9] = 9999;  
      for(time = 0; count != limit; time++)
      {
            smallest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                  turnaround_time = turnaround_time + end - arrival_time[smallest];
            }
      }
      average_waiting_time = wait_time / limit; 
      average_turnaround_time = turnaround_time / limit;
      printf("nnAverage Waiting Time:t%lfn", average_waiting_time);
      printf("Average Turnaround Time:t%lfn", average_turnaround_time);
      return 0;
}
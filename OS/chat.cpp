#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
};

int main() {
    int limit = 4; // Number of processes

    // Example data
    int arrival_time[] = {0, 2, 3, 4};
    int burst_time[] = {6, 8, 7, 3};
    int temp[] = {6, 8, 7, 3}; // Store burst time temporarily
    int end = 0;
    int time = 0;
    int count = 0;
    int smallest;
    int wait_time = 0;
    int turnaround_time = 0;

    // Vector to store processes
    vector<Process> processes;
    for (int i = 0; i < limit; ++i) {
        processes.push_back({i + 1, arrival_time[i], burst_time[i], 0});
    }

    cout << "Gantt Chart:\n";
    for (time = 0; count != limit; ++time) {
        smallest = 0;
        for (int i = 0; i < limit; ++i) {
            if (processes[i].arrivalTime <= time && processes[i].burstTime < processes[smallest].burstTime && processes[i].burstTime > 0) {
                smallest = i;
            }
        }

        cout << "P" << processes[smallest].id << " "; // Print current executing process in Gantt chart

        --processes[smallest].burstTime;

        if (processes[smallest].burstTime == 0) {
            ++count;
            end = time + 1;
            processes[smallest].waitingTime = end - processes[smallest].arrivalTime - temp[smallest];
            wait_time += processes[smallest].waitingTime;
            turnaround_time += end - processes[smallest].arrivalTime;
        }
    }

    cout << endl << endl;

    // Print waiting time for each process
    cout << "Process\tWaiting Time\n";
    for (int i = 0; i < limit; ++i) {
        cout << "P" << processes[i].id << "\t" << processes[i].waitingTime << endl;
    }

    // Calculate average turnaround time
    double avg_turnaround_time = static_cast<double>(turnaround_time) / limit;

    // Calculate average waiting time
    double avg_wait_time = static_cast<double>(wait_time) / limit;

    cout << "\nAverage Waiting Time: " << avg_wait_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;

    return 0;
}




#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
};

// Function to compare two processes based on burst time
bool compareArrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

// Function to implement Shortest Job First (SJF) scheduling algorithm
void SJF(vector<Process> &processes) {
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    int n = processes.size();
    int currentTime = 0;
    int totalWaitingTime = 0;
    int completedProcesses = 0;
    vector<int> waitingTime(n, 0);

    cout << "Gantt Chart:\n";
    while (completedProcesses < n) {
        int shortestIdx = -1;
        int shortestBurst = INT_MAX;

        // Find the shortest job available at current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    shortestIdx = i;
                }
            }
        }

        if (shortestIdx != -1) {
            cout << "P" << processes[shortestIdx].id << " "; // Print current executing process in Gantt chart

            // Execute the shortest job
            int executionTime = min(processes[shortestIdx].remainingTime, 1); // Execute one unit of time
            processes[shortestIdx].remainingTime -= executionTime;
            currentTime += executionTime;

            if (processes[shortestIdx].remainingTime == 0) {
                completedProcesses++;
                waitingTime[shortestIdx] = currentTime - processes[shortestIdx].arrivalTime - processes[shortestIdx].burstTime;
            }
        } else {
            currentTime++; // If no process is available, move to next time unit
        }
    }

    cout << endl << endl;

    // Print waiting time for each process
    cout << "Process\tWaiting Time\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].id << "\t" << waitingTime[i] << endl;
    }

    // Calculate average waiting time
    double avgWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
    }
    avgWaitingTime /= n;

   


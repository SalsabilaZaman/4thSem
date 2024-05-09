#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Process {
    string name;
    double arrival_time;
    double burst_time;
    double remaining_time;
    double waiting_time;
    double turnaround_time;
    bool is_completed;
    int priority;
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrival_time < b.arrival_time;
}

bool comparePriority(const Process &a, const Process &b) {
    if (a.arrival_time != b.arrival_time)
        return a.arrival_time < b.arrival_time;
    return a.priority < b.priority;
}

int main() {
    freopen("data.txt", "r", stdin);
    int num;
    cin >> num;
    vector<Process> P(num);

    for (int i = 0; i < num; i++) {
        cin >> P[i].name >> P[i].burst_time >> P[i].priority >> P[i].arrival_time;
        P[i].remaining_time = P[i].burst_time;
        P[i].is_completed = false;
    }

    sort(P.begin(), P.end(), compareArrival);

    vector<Process> ready;
    double time = 0;
    int running = -1;

    cout << "Gantt Chart:\n";

    while (true) {
        int next_process = -1;
        int max_priority = 89888;

        for (int i = 0; i < num; i++) {
            if (P[i].arrival_time <= time && !P[i].is_completed && P[i].priority < max_priority) {
                next_process = i;
                max_priority = P[i].priority;
            }
        }

        if (next_process != -1) {
            if (running != next_process) {
                if (running != -1) {
                    cout << "Time " << time << ": " << "P" << P[running].name << " ends" << endl;
                }
                cout << "Time " << time << ": " << "P" << P[next_process].name << " starts" << endl;
                running = next_process;
            }

            P[running].remaining_time -= 1;
            time += 1;

            if (P[running].remaining_time == 0) {
                P[running].is_completed = true;
                cout << "Time " << time << ": " << "P" << P[running].name << " ends" << endl;
                running = -1;
            }
        } else {
            bool all_completed = true;
            for (int i = 0; i < num; i++) {
                if (!P[i].is_completed) {
                    all_completed = false;
                    break;
                }
            }
            if (all_completed) break;
            time++;
        }
    }

    cout << endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Process {
    string id;
    int arrival;
    int burst;
    int priority;

    int completion;
    int waiting;
    int turnaround;
    int remaining;
};

void displayResult(vector<Process>& p) {
    float totalWaiting = 0;
    float totalTurnaround = 0;

    cout << "\n------------------------------------------------\n";
    cout << "Process\tAT\tBT\tCT\tWT\tTAT\n";
    cout << "------------------------------------------------\n";

    for (int i = 0; i < p.size(); i++) {
        cout << p[i].id << "\t"
             << p[i].arrival << "\t"
             << p[i].burst << "\t"
             << p[i].completion << "\t"
             << p[i].waiting << "\t"
             << p[i].turnaround << endl;

        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }

    cout << "------------------------------------------------\n";
    cout << "Average Waiting Time    : "
         << totalWaiting / p.size() << endl;

    cout << "Average Turnaround Time : "
         << totalTurnaround / p.size() << endl;
}

void fcfs(vector<Process> p) {
    cout << "\n========== FCFS ==========\n";

    int time = 0;

    cout << "\nGANTT CHART\n";
    cout << "|";

    for (int i = 0; i < p.size(); i++) {

        if (time < p[i].arrival) {
            time = p[i].arrival;
        }

        cout << " " << p[i].id << " |";

        time = time + p[i].burst;

        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    cout << "\n0";

    time = 0;

    for (int i = 0; i < p.size(); i++) {

        if (time < p[i].arrival) {
            time = p[i].arrival;
        }

        time = time + p[i].burst;

        cout << "\t" << time;
    }

    cout << endl;

    displayResult(p);
}

void sjf(vector<Process> p) {
    cout << "\n========== SJF ==========\n";

    int n = p.size();
    int time = 0;
    int completed = 0;

    vector<bool> done(n, false);

    cout << "\nGANTT CHART\n";
    cout << "|";

    while (completed < n) {

        int index = -1;
        int shortest = 999999;

        for (int i = 0; i < n; i++) {

            if (!done[i] &&
                p[i].arrival <= time &&
                p[i].burst < shortest) {

                shortest = p[i].burst;
                index = i;
            }
        }

        if (index == -1) {
            time++;
            continue;
        }

        cout << " " << p[index].id << " |";

        time = time + p[index].burst;

        p[index].completion = time;
        p[index].turnaround =
            p[index].completion - p[index].arrival;

        p[index].waiting =
            p[index].turnaround - p[index].burst;

        done[index] = true;
        completed++;
    }

    cout << endl;

    displayResult(p);
}

void priorityScheduling(vector<Process> p) {
    cout << "\n========== PRIORITY SCHEDULING ==========\n";
    cout << "(Lower number means higher priority)\n";

    int n = p.size();
    int time = 0;
    int completed = 0;

    vector<bool> done(n, false);

    cout << "\nGANTT CHART\n";
    cout << "|";

    while (completed < n) {

        int index = -1;
        int bestPriority = 999999;

        for (int i = 0; i < n; i++) {

            if (!done[i] &&
                p[i].arrival <= time &&
                p[i].priority < bestPriority) {

                bestPriority = p[i].priority;
                index = i;
            }
        }

        if (index == -1) {
            time++;
            continue;
        }

        cout << " " << p[index].id << " |";

        time = time + p[index].burst;

        p[index].completion = time;

        p[index].turnaround =
            p[index].completion - p[index].arrival;

        p[index].waiting =
            p[index].turnaround - p[index].burst;

        done[index] = true;
        completed++;
    }

    cout << endl;

    displayResult(p);
}

void roundRobin(vector<Process> p) {
    cout << "\n========== ROUND ROBIN ==========\n";

    int quantum;

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int n = p.size();
    int completed = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
    }

    vector<int> queue;
    vector<bool> added(n, false);

    cout << "\nGANTT CHART\n";
    cout << "|";

    while (completed < n) {

        for (int i = 0; i < n; i++) {

            if (!added[i] && p[i].arrival <= time) {
                queue.push_back(i);
                added[i] = true;
            }
        }

        if (queue.empty()) {
            time++;
            continue;
        }

        int index = queue[0];

        queue.erase(queue.begin());

        cout << " " << p[index].id << " |";

        int runTime;

        if (p[index].remaining > quantum) {
            runTime = quantum;
        }
        else {
            runTime = p[index].remaining;
        }

        time = time + runTime;

        p[index].remaining =
            p[index].remaining - runTime;

        for (int i = 0; i < n; i++) {

            if (!added[i] && p[i].arrival <= time) {
                queue.push_back(i);
                added[i] = true;
            }
        }

        if (p[index].remaining > 0) {
            queue.push_back(index);
        }
        else {
            p[index].completion = time;

            p[index].turnaround =
                p[index].completion - p[index].arrival;

            p[index].waiting =
                p[index].turnaround - p[index].burst;

            completed++;
        }
    }

    cout << endl;

    displayResult(p);
}

void displayProcesses(vector<Process>& p) {

    cout << "\n========== PROCESS DETAILS ==========\n";

    cout << "Process\tAT\tBT\tPriority\n";
    cout << "-------------------------------------\n";

    for (int i = 0; i < p.size(); i++) {

        cout << p[i].id << "\t"
             << p[i].arrival << "\t"
             << p[i].burst << "\t"
             << p[i].priority << endl;
    }
}

int main() {

    vector<Process> processes;

    int n;

    cout << "=====================================\n";
    cout << "       CPU SCHEDULING SIMULATOR\n";
    cout << "=====================================\n";

    cout << "\nEnter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {

        Process p;

        cout << "\nEnter details for Process " << i + 1 << endl;

        cout << "Process ID: ";
        cin >> p.id;

        cout << "Arrival Time: ";
        cin >> p.arrival;

        cout << "Burst Time: ";
        cin >> p.burst;

        cout << "Priority: ";
        cin >> p.priority;

        p.completion = 0;
        p.waiting = 0;
        p.turnaround = 0;
        p.remaining = p.burst;

        processes.push_back(p);
    }

    int choice;

    do {

        cout << "\n\n========== MENU ==========\n";
        cout << "1. FCFS\n";
        cout << "2. SJF\n";
        cout << "3. Priority Scheduling\n";
        cout << "4. Round Robin\n";
        cout << "5. Display Processes\n";
        cout << "6. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                fcfs(processes);
                break;

            case 2:
                sjf(processes);
                break;

            case 3:
                priorityScheduling(processes);
                break;

            case 4:
                roundRobin(processes);
                break;

            case 5:
                displayProcesses(processes);
                break;

            case 6:
                cout << "\nThank you!\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

struct Process {
    int id;
    int arrivaltime;
    int bursttime;
    int remainingtime;
    int waitingtime;
    int turnaroundtime;
    int completiontime;
    int queuelevel;
};

// Round Robin Scheduling
void roundRobin(struct Process processes[], int n, int timequantum, int starttime, int *endtime, int queuelevel) {
    int time = starttime;
    bool done;
    
    do {
        done = true;
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingtime > 0 && processes[i].queuelevel == queuelevel && processes[i].arrivaltime <= time) {
                done = false;
                
                if (processes[i].remainingtime > timequantum) {
                    time += timequantum;
                    processes[i].remainingtime -= timequantum;
                } else {
                    time += processes[i].remainingtime;
                    processes[i].completiontime = time;
                    processes[i].turnaroundtime = processes[i].completiontime - processes[i].arrivaltime;
                    processes[i].waitingtime = processes[i].turnaroundtime - processes[i].bursttime;
                    processes[i].remainingtime = 0;
                }
            }
        }
    } while (!done);
    
    *endtime = time;
}

// FCFS Scheduling
void fcfs(struct Process processes[], int n, int starttime) {
    int time = starttime;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].queuelevel == 3) {
            if (time < processes[i].arrivaltime)
                time = processes[i].arrivaltime;
            
            time += processes[i].bursttime;
            processes[i].completiontime = time;
            processes[i].turnaroundtime = processes[i].completiontime - processes[i].arrivaltime;
            processes[i].waitingtime = processes[i].turnaroundtime - processes[i].bursttime;
            processes[i].remainingtime = 0;
        }
    }
}

// Display output and calculate averages
void calculateTimes(struct Process processes[], int n) {
    int totalwaitingtime = 0;
    int totalturnaroundtime = 0;
    
    printf("\n\nProcess\tArrival\tBurst\tQueue\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalwaitingtime += processes[i].waitingtime;
        totalturnaroundtime += processes[i].turnaroundtime;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
            processes[i].id, processes[i].arrivaltime, processes[i].bursttime, 
            processes[i].queuelevel, processes[i].waitingtime, processes[i].turnaroundtime);
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)totalwaitingtime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalturnaroundtime / n);
}

// Main Function
int main() {
    int n;
    printf("Name: Akhand Pratap Shukla\nRoll No: 2301641540022\n\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[MAX_PROCESSES];
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time and queue level (1-3) for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivaltime, &processes[i].bursttime, &processes[i].queuelevel);
        processes[i].remainingtime = processes[i].bursttime;
        processes[i].completiontime = 0;
    }
    
    int endtime = 0;
    
    // Queue 1: Round Robin with time quantum 2
    roundRobin(processes, n, 2, 0, &endtime, 1);
    
    // Queue 2: Round Robin with time quantum 4
    roundRobin(processes, n, 4, 0, &endtime, 2);
    
    // Queue 3: FCFS
    fcfs(processes, n, 0);
    
    calculateTimes(processes, n);
    
    return 0;
}

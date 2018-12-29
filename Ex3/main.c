#include <stdio.h>
#include <stdlib.h>


struct process{
    int pid;
    int burstTime;
    int arrTime;
    int arrTimeUpdate;
    int waitingTime;
    int endTime; // for each quantum in RR
};

void FCFS (struct process* prcsArr, int numOfProc){
    int i;
    for (i=0; i<numOfProc; i++){
        prcsArr[i].waitingTime = prcsArr[i].arrTime;
        prcsArr[i].arrTimeUpdate=prcsArr[i].arrTime;
        if (i > 0) { //start checking from [1]
            if (prcsArr[i].arrTime < prcsArr[i - 1].arrTime + prcsArr[i - 1].burstTime) { //check that start time isn't before previous ends
                prcsArr[i].arrTimeUpdate = prcsArr[i - 1].arrTimeUpdate + prcsArr[i - 1].burstTime; //if it does, change start time
            }
        }
        printf("#%d:[%d]-[%d]\n",prcsArr[i].pid, prcsArr[i].arrTimeUpdate, prcsArr[i].arrTimeUpdate + prcsArr[i].burstTime); //print times
    }
    for (i=0; i<numOfProc; i++)
        printf("Process %d waiting time: %d\n", prcsArr[i].pid, prcsArr[i].arrTimeUpdate-prcsArr[i].arrTime); //print waiting time
}

void RR (struct process* prcsArr, int numOfProc, int timeQuantum){
    prcsArr[0].arrTimeUpdate=prcsArr[0].arrTime;
    int numEndedProc = 0;
    int i=0;
    while(numEndedProc != numOfProc) {
        for (i = 0; i < numOfProc; i++) {
            if (prcsArr[i].burstTime != 0) {
                if (prcsArr[i].burstTime <= timeQuantum) {
                    prcsArr[i].endTime = prcsArr[i].arrTimeUpdate + prcsArr[i].burstTime;
                    printf("#%d:[%d]-[%d]\n", prcsArr[i].pid, prcsArr[i].arrTimeUpdate, prcsArr[i].endTime);
                    prcsArr[i].burstTime = 0;
                    numEndedProc++;
                    if (prcsArr[i + 1].arrTime >= prcsArr[i].endTime)
                        prcsArr[i + 1].arrTimeUpdate = prcsArr[i + 1].arrTime;
                    else
                        prcsArr[i + 1].arrTimeUpdate = prcsArr[i].endTime;
                } else {
                    prcsArr[i].endTime = prcsArr[i].arrTimeUpdate + timeQuantum;
                    prcsArr[i].burstTime -= timeQuantum;
                    printf("#%d:[%d]-[%d]\n", prcsArr[i].pid, prcsArr[i].arrTimeUpdate, prcsArr[i].endTime);
                    if (prcsArr[i + 1].arrTime >= prcsArr[i].endTime)
                        prcsArr[i + 1].arrTimeUpdate = prcsArr[i + 1].arrTime;
                    else
                        prcsArr[i + 1].arrTimeUpdate = prcsArr[i].endTime;
                }
            }
        }
    }
}

int main() {
    printf("Enter amount of processes:\n");
    int timeQuantum;
    int numOfProc;
    int option;
    scanf("%d", &numOfProc);
    int i;
    struct process* processes = malloc(numOfProc*sizeof(struct process));
    for (i=0; i<numOfProc; i++) {
        printf("Enter arrival time and burst time\n");
        scanf("%d %d", &processes[i].arrTime, &processes[i].burstTime);
        processes[i].pid=i+1;
    }
    printf("Enter algorithm number:\n");
    scanf("%d", &option);
    if (option == 2){
        printf("Enter quantum:\n");
        scanf("%d", &timeQuantum);
    }
    FCFS(processes, numOfProc);
    return 0;
}
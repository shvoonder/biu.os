#include <stdio.h>
#include <stdlib.h>


struct process{
    int pid;
    int burstTime;
    int arrTime;
};

void FCFS (struct process prcsArr[]){
    int i;
    for (int i=0; i<sizeof(prcsArr); i++){
        if (i > 0) //start checking from [1]
            if (prcsArr[i].arrTime < prcsArr[i-1].arrTime + prcsArr[i-1].burstTime) //check that start time isn't before previous ends
                prcsArr[i].arrTime = prcsArr[i-1].arrTime + prcsArr[i-1].burstTime; //if it does, change start time
        printf("#%d:[%d] - [%d]\n",prcsArr->pid, prcsArr[i].arrTime, prcsArr[i].arrTime + prcsArr[i].burstTime);
    }
}

int main() {
    printf("Enter amount of processes:");
    int numOfProc;
    int option;
    scanf("%d", numOfProc);
    int i;
    struct process* processes = malloc(numOfProc*sizeof(int));
    for (i=0; i<numOfProc; i++) {
        printf("Enter arrival time and burst time");
        scanf("%d %d", processes[i].arrTime, processes[i].burstTime);
        processes[i].pid=i;
    }
    printf("Enter algorithm number:");
    scanf("%d", option);
    
    return 0;
}
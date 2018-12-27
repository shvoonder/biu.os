#include <stdio.h>
#include <stdlib.h>


struct process{
    int pid;
    int burstTime;
    int arrTime;
    int waitingTime;
};

void FCFS (struct process* prcsArr, int numOfProc){
    int i;
    prcsArr[0].waitingTime=prcsArr[0].arrTime;
    for (int i=0; i<numOfProc; i++){
        if (i > 0) { //start checking from [1]
            if (prcsArr[i].arrTime < prcsArr[i - 1].arrTime + prcsArr[i - 1].burstTime) //check that start time isn't before previous ends
                prcsArr[i].arrTime = prcsArr[i - 1].arrTime + prcsArr[i - 1].burstTime; //if it does, change start time
                prcsArr[i].waitingTime = prcsArr[i-1].arrTime+prcsArr[i-1].burstTime; //calculate waiting time for each process
        }
        printf("#%d:[%d]-[%d]\n",prcsArr[i].pid, prcsArr[i].arrTime, prcsArr[i].arrTime + prcsArr[i].burstTime); //print times
    }
    for (i=0; i<numOfProc; i++)
        printf("Process %d waiting time: %d\n", prcsArr[i].pid, prcsArr[i].waitingTime); //print waiting time
}

void RR (struct process prcsArr[]){

}

int main() {
    printf("Enter amount of processes:\n");
    int numOfProc;
    int option;
    scanf("%d", &numOfProc);
    int i;
    struct process* processes = malloc(numOfProc*sizeof(int));
    for (i=0; i<numOfProc; i++) {
        printf("Enter arrival time and burst time\n");
        scanf("%d %d", &processes[i].arrTime, &processes[i].burstTime);
        processes[i].pid=i+1;
    }
    printf("Enter algorithm number:\n");
    scanf("%d", &option);
    FCFS(processes, numOfProc);
    return 0;
}
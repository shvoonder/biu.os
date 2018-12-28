#include <stdio.h>
#include <stdlib.h>


struct process{
    int pid;
    int burstTime;
    int arrTime;
    int arrTimeUpdate;
    int waitingTime;
};

void Dequeue (int* prcsQueue, int currNumOfProc){ //delete first element in the queue
    int i;
    if (currNumOfProc>1) //check that there are at least 2 processes in the queue
        for (i=0; i < currNumOfProc-1; i++)
            prcsQueue[i] = prcsQueue[i+1];
    else
        prcsQueue[0]=0;
}

void Enqueue (int* prcsQueue, int currNumOfProc, int pid){
    prcsQueue[currNumOfProc] = pid;
}

void FCFS (struct process* prcsArr, int numOfProc){
    int i;
    for (i=0; i<numOfProc; i++){
        prcsArr[i].waitingTime = prcsArr[i].arrTime;
        prcsArr[i].arrTimeUpdate=prcsArr[i].arrTime;
        if (i > 0) { //start checking from [1]
            if (prcsArr[i].arrTime < prcsArr[i - 1].arrTime + prcsArr[i - 1].burstTime) { //check that start time isn't before previous ends
                prcsArr[i].arrTimeUpdate = prcsArr[i - 1].arrTimeUpdate + prcsArr[i - 1].burstTime; //if it does, change start time
                prcsArr[i].waitingTime = prcsArr[i].arrTime;//calculate waiting time for each process
            }
        }
        printf("#%d:[%d]-[%d]\n",prcsArr[i].pid, prcsArr[i].arrTimeUpdate, prcsArr[i].arrTimeUpdate + prcsArr[i].burstTime); //print times
    }
    for (i=0; i<numOfProc; i++)
        printf("Process %d waiting time: %d\n", prcsArr[i].pid, prcsArr[i].arrTimeUpdate-prcsArr[i].arrTime); //print waiting time
}

void RR (struct process* prcsArr, int numOfProc, int timeQuantum){
    int* prcsQueue = malloc(numOfProc* sizeof(int));
    int i, j;
    Enqueue(prcsQueue,1,1);
    int currNumOfProc=1;
    int timeElapsed = prcsArr[0].arrTime;
    for (i=0; i<numOfProc; i++){
        for (j=0; j<numOfProc; j++){ //find needed process
            if (prcsQueue[0] == prcsArr[i].pid){
                Dequeue(prcsQueue, currNumOfProc);
                currNumOfProc--;
                prcsArr[i].burstTime-=timeQuantum;
                if (prcsArr[i].burstTime<0)
                    timeElapsed = timeElapsed+timeQuantum+prcsArr[i].burstTime;
                else
                    timeElapsed = timeElapsed+timeQuantum;
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
#include <stdio.h>

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
    printf("");
    return 0;
}
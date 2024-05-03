#include <stdio.h>
#include <stdlib.h>
#define SORT_BY_ARRIVAL 0
#define SORT_BY_PID 1
#define SORT_BY_BURST 2
#define SORT_BY_START 3
#define SORT_BY_REMAINTIME 4
typedef struct{
    int iPID;
    int iArrival, iBurst;
    int runningTime;
    int remainTime;
    int iStart, iFinish, iWaiting, iResponse, iTaT;
} PCB;

void inputProcess(int n, PCB P[]) {
    for (int i = 0; i < n; i++) {
        P[i].iPID = i+1;
        printf("Input Arrival Time P%d: ", P[i].iPID);
        scanf("%d", &P[i].iArrival);
        printf("Input Burst Time P%d: ", P[i].iPID);
        scanf("%d", &P[i].iBurst);
    }
}
void printProcess(int n, PCB P[]) {
    printf("___________________________________________________________________________________________________________________\n");
    printf("| Process | Arrival Time | Burst Time | Start Time | Finish Time | Response Time | Waiting Time | Turnaround Time |\n");
    printf("|_________|______________|____________|____________|_____________|_______________|______________|_________________|\n");

    for(int i = 0; i < n; i++){
        printf("|   P%d    |", P[i].iPID);
        if (P[i].iArrival < 10) {
            printf("      %d       |", P[i].iArrival);
        } else {
            printf("      %d      |", P[i].iArrival);
        }
        
        if (P[i].iBurst < 10) {
            printf("     %d      |", P[i].iBurst);
        } else {
            printf("     %d     |", P[i].iBurst);
        }

        if (P[i].iStart < 10) {
            printf("     %d      |", P[i].iStart);
        } else {
            printf("     %d     |", P[i].iStart);
        }

        if (P[i].iFinish < 10) {
            printf("      %d      |", P[i].iFinish);
        } else {
            printf("      %d     |", P[i].iFinish);
        }

        if (P[i].iResponse < 10) {
            printf("      %d        |", P[i].iResponse);
        } else {
            printf("      %d       |", P[i].iResponse);
        }

        if (P[i].iWaiting < 10) {
            printf("      %d       |", P[i].iWaiting);
        } else {
            printf("      %d      |", P[i].iWaiting);
        }

        if (P[i].iTaT < 10) {
            printf("       %d         |\n", P[i].iTaT);
        } else {
            printf("       %d        |\n", P[i].iTaT);
        }

        if (i != n - 1) {
            printf("|_________|______________|____________|____________|_____________|_______________|______________|_________________|\n");
        }
    }

    printf("|_________|______________|____________|____________|_____________|_______________|______________|_________________|\n");

}

void exportGanttChart (int n, PCB P[]) {
    printf("Gantt Chart:\n");
    printf("__________");
    for (int i = 0; i < n; i++) {
        if (i == n - 1) continue;
        printf("_________");
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        if (i < 10) {
            printf("|   P%d   ", P[i].iPID);
        } else {
            printf("|   P%d  ", P[i].iPID);
        }   
    }
    printf("|\n");
    for (int i = 0; i < n; i++) {
        printf("|________");
    }
    printf("|\n0");
    for (int i = 0; i < n; i++) {
        if (P[i].iFinish < 10) {
            printf("        %d", P[i].iFinish);
        } else {
            printf("       %d", P[i].iFinish);
        }
        
    }
    printf("\n");
}

void pushProcess(int *n, PCB P[], PCB Q) {
    P[*n] = Q;
    *n = *n + 1;
}

void removeProcess(int *n, int index, PCB P[]) {
    for (int i = index; i < *n; i++) {
        if (i == *n - 1) break;
        P[i] = P[i+1];
    }
    *n = *n - 1;
}

int swapProcess(PCB *P, PCB *Q) {
    PCB tmp = *P;
    *P = *Q;
    *Q = tmp;
}

int partition (PCB P[], int low, int high, int iCriteria) {
    if (iCriteria == 0) {
        int pivot = P[high].iArrival;
        int i = (low-1);
    
        for(int j = low; j <= high; j++)
        {
            //If current element is smaller than the pivot
            if(P[j].iArrival < pivot)
            {
            //Increment index of smaller element
                i++;
                swapProcess(&P[i], &P[j]);
            }
        }
        swapProcess(&P[i+1], &P[high]);
        return (i+1);
    } else if (iCriteria == 1) {
        int pivot = P[high].iPID;
        int i = (low-1);
    
        for(int j = low; j <= high; j++)
        {
            //If current element is smaller than the pivot
            if(P[j].iPID < pivot)
            {
            //Increment index of smaller element
                i++;
                swapProcess(&P[i], &P[j]);
            }
        }
        swapProcess(&P[i+1], &P[high]);
        return (i+1);
    } else if (iCriteria == 2) {
        int pivot = P[high].iBurst;
        int i = (low-1);
    
        for(int j = low; j <= high; j++)
        {
            //If current element is smaller than the pivot
            if(P[j].iBurst < pivot)
            {
            //Increment index of smaller element
                i++;
                swapProcess(&P[i], &P[j]);
            }
        }
        swapProcess(&P[i+1], &P[high]);
        return (i+1);
    } else if (iCriteria == 3) {
        int pivot = P[high].iStart;
        int i = (low-1);
    
        for(int j = low; j <= high; j++)
        {
            //If current element is smaller than the pivot
            if(P[j].iStart < pivot)
            {
            //Increment index of smaller element
                i++;
                swapProcess(&P[i], &P[j]);
            }
        }
        swapProcess(&P[i+1], &P[high]);
        return (i+1);
    } else if (iCriteria == 4) {
        int pivot = P[high].remainTime;
        int i = (low-1);
    
        for(int j = low; j <= high; j++)
        {
            //If current element is smaller than the pivot
            if(P[j].remainTime < pivot)
            {
            //Increment index of smaller element
                i++;
                swapProcess(&P[i], &P[j]);
            }
        }
        swapProcess(&P[i+1], &P[high]);
        return (i+1);
    }
}

void quickSort(PCB P[], int low, int high, int iCriteria) {
    if (low < high) {
        int p = partition (P, low, high, iCriteria);
        quickSort (P, low, p - 1, iCriteria);
        quickSort (P, p + 1, high, iCriteria);
    }
}

void calculateAWT(int n, PCB P[]) {
    float sumWT = 0;
    for (int i = 0; i < n; i++) {
        sumWT += P[i].iWaiting;
    }
    printf("Average Waiting Time: %.2f\n", (float)(sumWT / n));
}

void calculateATaT(int n, PCB P[]) {
    float sumTaT = 0;
    for (int i = 0; i < n; i++) {
        sumTaT += P[i].iTaT;
    }
    printf("Average Turnaround Time: %.2f\n", (float)(sumTaT / n));
}

void sortSJFFirstTime(int n, PCB P[]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (P[j].iArrival == P[i].iArrival) {
                if (P[i].iBurst > P[j].iBurst) {
                    swapProcess(&P[i], &P[j]);
                }
            }
        }
    }
}

int main()
{
    PCB Input[10];
    PCB ReadyQueue[10];
    PCB Running[100];
    PCB TerminatedArray[10];
    int iNumberOfProcess;

    printf("Please input number of Process: ");
    scanf("%d", &iNumberOfProcess);

    int iRemain = iNumberOfProcess, iReady = 0, iTerminated = 0, iRunning = 0, time = 0;
    inputProcess(iNumberOfProcess, Input);
    for (int i = 0; i < iNumberOfProcess; i++) {
        Input[i].remainTime = Input[i].iBurst;
        Input[i].iStart = -1;
        Input[i].iFinish = 0;
    }
    quickSort(Input, 0, iNumberOfProcess - 1, SORT_BY_ARRIVAL);
    sortSJFFirstTime(iNumberOfProcess, Input);
    pushProcess(&iReady, ReadyQueue, Input[0]);
    removeProcess(&iRemain, 0, Input);
    //ReadyQueue[0].remainTime = ReadyQueue[0].iBurst;
    ReadyQueue[0].iStart = ReadyQueue[0].iArrival;
    //ReadyQueue[0].iFinish = ReadyQueue[0].iStart + ReadyQueue[0].iBurst;
    ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
    //ReadyQueue[0].iWaiting = ReadyQueue[0].iResponse;
    //ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;
    pushProcess(&iRunning, Running, ReadyQueue[0]);
    time = Running[0].iStart;
    
    printf("\nReady Queue:\n");
    printProcess(1, ReadyQueue);
    removeProcess(&iReady, 0, ReadyQueue);
    while (iRemain > 0) {
        time++;
        Running[iRunning-1].remainTime--;
        for (int i = 0; i < iRemain; i++) {
            
            if (Input[i].iArrival == time && Input[i].iBurst < Running[iRunning - 1].remainTime) {
                Running[iRunning-1].iFinish = time;
                pushProcess(&iReady, ReadyQueue, Running[iRunning - 1]);
                //ReadyQueue[iReady - 1].remainTime -= time;
                pushProcess(&iRunning, Running, Input[i]);
                //ReadyQueue[iReady - 1].iFinish = time;
                Running[iRunning - 1].iStart = time;
                Running[iRunning - 1].iResponse = Running[iRunning-1].iStart - Running[iRunning-1].iArrival;
                
                removeProcess(&iRemain, i, Input);
            } else if (Input[i].iArrival == time && Running[iRunning - 1].remainTime == 0) {
                Running[iRunning-1].iFinish = time;
                Running[iRunning-1].iTaT = time - Running[iRunning-1].iArrival;
                Running[iRunning-1].iWaiting = Running[iRunning-1].iTaT - Running[iRunning-1].iBurst;
                pushProcess(&iTerminated, TerminatedArray, Running[iRunning-1]);
                quickSort(ReadyQueue, 0, iReady - 1, SORT_BY_REMAINTIME);
                if (ReadyQueue[0].remainTime <= Input[i].iBurst) {
                    pushProcess(&iRunning, Running, ReadyQueue[0]);
                    removeProcess(&iReady, 0, ReadyQueue);
                    pushProcess(&iReady, ReadyQueue, Input[i]);
                    removeProcess(&iRemain, i, Input);
                } else {
                    pushProcess(&iRunning, Running, Input[i]);
                    removeProcess(&iRemain, i, Input);
                }
                Running[iRunning - 1].iStart = time;
                Running[iRunning - 1].iResponse = Running[iRunning-1].iStart - Running[iRunning-1].iArrival;
            } else if (Input[i].iArrival == time) {
                pushProcess(&iReady, ReadyQueue, Input[i]);
                removeProcess(&iRemain, i, Input);
            }
        }
    }

    while (iTerminated < iNumberOfProcess) {
        time++;
        Running[iRunning-1].remainTime--;
        if (Running[iRunning-1].remainTime == 0) {
            Running[iRunning-1].iFinish = time;
            Running[iRunning-1].iTaT = time - Running[iRunning-1].iArrival;
            Running[iRunning-1].iWaiting = Running[iRunning-1].iTaT - Running[iRunning-1].iBurst;
            pushProcess(&iTerminated, TerminatedArray, Running[iRunning-1]);
            if (iReady > 0) {
                quickSort(ReadyQueue, 0, iReady - 1, SORT_BY_REMAINTIME);
                if (ReadyQueue[0].iStart == -1) {
                    ReadyQueue[0].iStart = time;
                }
                ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
                pushProcess(&iRunning, Running, ReadyQueue[0]);
                removeProcess(&iReady, 0, ReadyQueue);
            }
        }
    }

    printf("\n===== SJF Scheduling =====\n");
    printProcess(iRunning, Running);
    exportGanttChart(iRunning, Running);
    quickSort(TerminatedArray, 0, iTerminated - 1, SORT_BY_PID);
    calculateAWT(iTerminated, TerminatedArray);
    calculateATaT(iTerminated, TerminatedArray);

    return 0;
}
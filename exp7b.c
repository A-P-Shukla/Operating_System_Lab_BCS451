#include <stdio.h>

// Function to perform Best-Fit allocation
void bestFit(int blocksizes[], int numblocks, int processsize) {
    int minidx = -1;
    
    for (int i = 0; i < numblocks; i++) {
        if (blocksizes[i] >= processsize) {
            if (minidx == -1 || blocksizes[i] < blocksizes[minidx]) {
                minidx = i;
            }
        }
    }
    
    if (minidx != -1) {
        printf("Allocated process of size %d to block %d\n", processsize, minidx);
        blocksizes[minidx] -= processsize;
    } else {
        printf("No block available for process of size %d\n", processsize);
    }
}

int main() {
    printf("Name: Akhand Pratap Shukla\nRoll No: 2301641540022\n\n");
    
    int numblocks, numprocesses;
    
    printf("Enter number of blocks: ");
    scanf("%d", &numblocks);
    
    int blocksizes[numblocks];
    printf("Enter block sizes:\n");
    for (int i = 0; i < numblocks; i++) {
        scanf("%d", &blocksizes[i]);
    }
    
    printf("Enter number of processes: ");
    scanf("%d", &numprocesses);
    
    int processsizes[numprocesses];
    printf("Enter process sizes:\n");
    for (int i = 0; i < numprocesses; i++) {
        scanf("%d", &processsizes[i]);
    }
    
    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < numprocesses; i++) {
        bestFit(blocksizes, numblocks, processsizes[i]);
    }
    
    return 0;
}

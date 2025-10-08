#include <stdio.h>

// Function to perform Worst-Fit allocation
void worstFit(int blocksizes[], int numblocks, int processsize) {
    int maxidx = -1;
    
    for (int i = 0; i < numblocks; i++) {
        if (blocksizes[i] >= processsize) {
            if (maxidx == -1 || blocksizes[i] > blocksizes[maxidx]) {
                maxidx = i;
            }
        }
    }
    
    if (maxidx != -1) {
        printf("Allocated process of size %d to block %d\n", processsize, maxidx);
        blocksizes[maxidx] -= processsize;
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
    
    printf("\nWorst-Fit Allocation:\n");
    for (int i = 0; i < numprocesses; i++) {
        worstFit(blocksizes, numblocks, processsizes[i]);
    }
    
    return 0;
}
